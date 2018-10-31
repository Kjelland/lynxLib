#pragma once
#include <stdint.h>

namespace LynxStructureSpace
{
	enum LynxDataType
	{
		eEndOfList = 0,
		eNoStorage,
		eInt8,
		eUint8,
		eInt16,
		eUint16,
		eInt32,
		eUint32,
		eInt64,
		eUint64,
		eFloat,
		eDouble,
		eIQ
	};

	struct LynxID
	{
		uint8_t deviceID;			// Identifies the current machine
		uint8_t structTypeID;		// Identifies the type of struct
		uint8_t structInstanceID;	// Identifies the instance of the struct
	};

	enum StandardStructIDs
	{
		eSsInvalidID = 0,
		eLynxRequest,
		eLynxResponse,
		eSsEndOfReserve
	};

	enum RequestIDs
	{
		eRqInvalidID = 0,
		eRqDeviceInfo,
		eRqStructInfo
	};

	struct StructItem
	{
		int identifier;
		LynxDataType dataType;
	};

	struct StructDefinition
	{
		const char structName[20];
		const StructItem* structItems;
	};

	union LynxIpAddress
	{
		LynxIpAddress() { ip_32 = 0; };
		LynxIpAddress(uint32_t ipAddress) { ip_32 = ipAddress; };
		LynxIpAddress(const unsigned char ipAddress[4])
		{
			for (int i = 0; i < 4; i++)
			{
				ip_8[i] = ipAddress[i];
			}
		};
		LynxIpAddress(char ip0, char ip1, char ip2, char ip3)
		{
			ip_32 = 1;
			if (ip_8[0] == 1)
			{
				ip_8[0] = ip3;
				ip_8[1] = ip2;
				ip_8[2] = ip1;
				ip_8[3] = ip0;
			}
			else
			{
				ip_8[0] = ip0;
				ip_8[1] = ip1;
				ip_8[2] = ip2;
				ip_8[3] = ip3;
			}
			
		};
		uint32_t ip_32;
		unsigned char ip_8[4];
	};

	struct LynxScanResponse
	{
		LynxScanResponse()
		{
			deviceName[0] = '\0';
			deviceID = 0;
			ipAddress = LynxIpAddress();
		};

		char deviceName[20];
		uint8_t deviceID;
		LynxIpAddress ipAddress;
	};

	class LynxStructure
	{
	public:

		LynxID lynxID; // identifies current datagram

		LynxStructure()
		{
			indexingSize = 0;
			size = 0;
			data = nullptr;
			_structDefinition = nullptr;
			// _structName = nullptr;
			_dataChanged = false;
		};

		~LynxStructure()
		{
			if (data)
			{
				delete[] data;
				data = nullptr;
			}
		};

		void init(const StructDefinition* structDefinition, LynxID _lynxID, int nElements = 0);

		int toBuffer(char *dataBuffer);			// Returns size of copied data if success, -1 if failure, -2 if checksum is wrong

		int fromBuffer(const char *dataBuffer); // Returns size of copied data if success, -1 if failure

		void clear();							// sets all elements to 0

		const StructDefinition* structDefinition() { return _structDefinition; };

		int getSize() { return this->size; };

		bool dataChanged();

		template <class T>
		T getData(int identifier)
		{	
			int offset = getOffset(identifier);
			if (offset < 0)
			{
				return 0;
			}

			this->_dataChanged = false;
			
			return *(T*)(data + offset);

		};

		template <class T>
		void setData(int identifier, T dataIn)
		{
			int offset = getOffset(identifier);
			if (offset < 0)
			{
				return;
			}

			T* temp = (T*)(data + offset);

			*temp = dataIn;

			this->_dataChanged = true;

		};

		template <class T>
		bool getBit(int identifier, T bitMask)
		{
			return ((getData<T>(identifier) & bitMask) != 0);
		};

		template <class T>
		void setBit(int identifier, T bitMask, bool state)
		{
			T temp = getData<T>(identifier);
			if (state)
			{
				setData(identifier, temp | bitMask);
			}
			else
			{
				setData(identifier, temp & ~bitMask);
			}
		};

	private:
		// const char* _structName;
		
		int getOffset(int identifier);

		int indexingSize;
		int size;

		char *data;

		bool _dataChanged;

		const StructDefinition* _structDefinition;

		int checkLocalSize(LynxDataType dataType);

		int checkTransferSize(LynxDataType dataType);


	};

	class LynxHandler
	{
	public:
		uint8_t deviceID;

		LynxHandler(uint8_t _deviceID, const char* _deviceName, int nStructs = 0)
		{
			for (int i = 0; i < 20; i++)
			{
				if ((_deviceName[i] == '\0') || (i == 19))
				{
					this->deviceName[i] = '\0';
					break;
				}
				this->deviceName[i] = _deviceName[i];
			}
			_size = 0;
			_reservedSize = 0;
			_structures = nullptr;
			_newScanResponse = false;
			_newScanRequest = false;
			this->init(_deviceID, nStructs);
		};

		~LynxHandler()
		{
			if (_structures)
			{
				delete[] _structures;
				_structures = nullptr;
			}
		};

		void init(uint8_t _deviceID, int nStructs = 0);

		LynxID addStructure(uint8_t _structType, uint8_t _structInstance, const StructDefinition* _structDefinition, int nElements = 0);

		int scanRequest(char* dataBuffer);

		template <class T>
		T getData(LynxID _lynxID, int _identifier)
		{
			int index = this->indexFromID(_lynxID);

			if (index >= 0)
			{
				return this->_structures[index].getData<T>(_identifier);
			}
	
			return 0;
		};

		template <class T>
		T setData(LynxID _lynxID, int _identifier, T data) // Returns 0 if _lynxID was not found
		{
			int index = this->indexFromID(_lynxID);

			if (index >= 0)
			{
				this->_structures[index].setData<T>(_identifier, data);
				return data;
			}

			return 0;
		};

		template <class T>
		bool getBit(LynxID _lynxID, int identifier, T bitMask)
		{
			int index = this->indexFromID(_lynxID);
			if (index < 0)
			{
				return false;
			}

			return this->_structures[index].getBit<T>(identifier, bitMask);
		};

		template <class T>
		void setBit(LynxID _lynxID, int identifier, T bitMask, bool state)
		{
			int index = this->indexFromID(_lynxID);
			if (index < 0)
			{
				return;
			}

			this->_structures[index].setBit<T>(identifier, bitMask, state);
		};

		int toBuffer(LynxID _lynxID, char* dataBuffer);

		int fromBuffer(const char* dataBuffer, LynxIpAddress ipAddress = LynxIpAddress());

		bool dataChanged(LynxID _lynxID);

		int size() { return _size; };

		bool newScanResponse() { return _newScanResponse; };

		LynxScanResponse getScanResponse();

		bool newScanRequest() { return _newScanRequest; };

		int sendScanResponse(char* dataBuffer);

	private:
		char deviceName[20];

		bool _newScanResponse;

		bool _newScanRequest;

		LynxScanResponse _scanResponse;

		LynxStructure* _structures;
		int _size;
		int _reservedSize;

		int indexFromID(LynxID _lynxID);

		int handleRequest(const char* dataBuffer, LynxIpAddress ipAddress);

		int handleResponse(const char* dataBuffer, LynxIpAddress ipAddress);

		LynxScanResponse receiveScanResponse(const char* dataBuffer, LynxIpAddress ipAddress);

		int datagramFromBuffer(const char* dataBuffer);
	};


 }