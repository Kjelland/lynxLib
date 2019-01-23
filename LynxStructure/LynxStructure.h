#pragma once
#include <stdint.h>
#define LYNX_VERSION "1.1.0" 

namespace LynxStructureSpace
{
	//----------------------------------------------- Enums ------------------------------------------------------------

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

	enum LynxStructMode
	{
		eStructureMode = 1,
		eArrayMode
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

	enum SendMode
	{
		eAllVariables = 0,
		eSingleVariable,
		eSendModeEndOfList
	};

	//----------------------------------------------- Structures ------------------------------------------------------------

	struct LynxID
	{
		LynxID()
		{
			deviceID = 0;
			structTypeID = 0;
			structInstanceID = 0;
		};
		LynxID(uint8_t _deviceID, uint8_t _structTypeID, uint8_t _structInstanceID)
		{
			deviceID = _deviceID;
			structTypeID = _structTypeID;
			structInstanceID = _structInstanceID;
		};
		uint8_t deviceID;			// Identifies the current machine
		uint8_t structTypeID;		// Identifies the type of struct
		uint8_t structInstanceID;	// Identifies the instance of the struct
	};

	struct StructItem
	{
		StructItem(const char _name[], LynxDataType _dataType)
			: name( _name ), dataType( _dataType ) {};
		const char* name;
		LynxDataType dataType;
	};

	struct StructDefinition
	{
		StructDefinition(const char _structName[], const LynxStructMode _structMode, const StructItem* _structItems, int _size = 0) 
			: structName( _structName ), structMode( _structMode ), structItems( _structItems )
		{
			if ((_size > 0) || (_structMode == eArrayMode))
			{
				size = _size;
			}
			else
			{
				for (int i = 0; i < 256; i++)
				{
					if (_structItems[i].dataType == eEndOfList)
					{
						size = i;
						return;
					}
				}
				size = 0;
			}
		};

		const char* structName;
		const LynxStructMode structMode;
		const StructItem* structItems;
		int size;
	};

	union LynxIpAddress
	{
		LynxIpAddress() { address.ip_32 = 0; };

		LynxIpAddress(uint32_t ipAddress) { address.ip_32 = ipAddress; };

		LynxIpAddress(const unsigned char ipAddress[4])
		{
			for (int i = 0; i < 4; i++)
			{
				address.ip_8[i] = ipAddress[i];
			}
		};

		LynxIpAddress(char ip0, char ip1, char ip2, char ip3)
		{
			address.ip_32 = 1;

			if (address.ip_8[0] == 1)	// Little endian
			{
				address.ip_8[0] = ip3;
				address.ip_8[1] = ip2;
				address.ip_8[2] = ip1;
				address.ip_8[3] = ip0;
			}
			else						// Big endian
			{
				address.ip_8[0] = ip0;
				address.ip_8[1] = ip1;
				address.ip_8[2] = ip2;
				address.ip_8[3] = ip3;
			}
			
		};

		union Address
		{
			uint32_t ip_32;
			unsigned char ip_8[4];
		}address;
		
	};

	struct LynxDeviceInfo
	{
		LynxDeviceInfo()
		{
			// lynxVersion[0] = '\0';
			deviceName[0] = '\0';
			deviceID = 0;
			ipAddress = LynxIpAddress();
			newDevice = false;
		};

		// char lynxVersion[11];
		char deviceName[20];
		uint8_t deviceID;
		LynxIpAddress ipAddress;
		bool newDevice;
	};

	//----------------------------------------------- LynxList ------------------------------------------------------------

	template <class T>
	class LynxList
	{
	public:
		LynxList()
		{
			_list = nullptr;
			_size = 0;
			_reservedSize = 0;
		};

		LynxList(int size)
		{
			this->reserve(size);
		};

		LynxList(const LynxList<T>& list)
		{
			_list = nullptr;
			*this = list;
		};

		~LynxList()
		{
			if (_list)
			{
				delete[] _list;
				_list = nullptr;
			}
		};

		void operator = (const LynxList<T>& list)
		{
			this->reserve(list._size);

			for (int i = 0; i < this->_size; i++)
			{
				this->_list[i] = list._list[i];
			}

			this->_size = list._size;
		};

		void reserve(int size)
		{
			if (_list)
			{
				delete[] _list;
				_list = nullptr;
			}

			_size = 0;
			_reservedSize = size;
			_list = new T[size];
		};

		int appendItem(const T& item) // Adds a new item at the end of the list and populates it with "item". Returns index of appended item if successful, -1 if unsuccessful
		{
			int index = this->appendItem();

			if (index < 0)
			{
				return index;
			}

			_list[index] = item;
			return (index);
		};

		int appendItem() // Adds a new empty instance at the end of the list. Returns index of appended item if successful, -1 if unsuccessful
		{
			_size++;

			if (_size > _reservedSize)
			{
				_reservedSize++;

				T* tempList = new T[_reservedSize];

				if (_list)
				{
					for (int i = 0; i < _reservedSize - 1; i++)
					{
						tempList[i] = _list[i];
					}

					delete[] _list;
				}

				_list = tempList;
				tempList = nullptr;
			}

			_list[_size - 1] = T();

			return (_size - 1);
		};

		int removeItem(int index)	// Removes the indexed item and shifts the remaining items to fill.
									// Returns number of remaining items if successful, -1 if failed
									// If there are no remaining items, the allocated memory is freed.
		{
			if (index < this->_size)
			{
				_size--;
				if (_size <= 0)
				{
					this->deleteList();
					return this->_size;
				}

				for (int i = index; i < _size; i++)
				{
					_list[i] = _list[i + 1];
				}
				return this->_size;
			}

			return -1;
		};

		void deleteList()
		{
			_size = 0;
			_reservedSize = 0;
			if (_list)
			{
				delete[] _list;
				_list = nullptr;
			}
		};

		T& at(int index)
		{
			return _list[index];
		};

		int getSize() { return _size; };

	protected:
		T* _list;

		// T emptyReference;
		int _size;
		int _reservedSize;
	};

	//----------------------------------------------- LynxStructure ------------------------------------------------------------

	class LynxStructure
	{
	public:

		LynxID lynxID; // identifies current datagram

		LynxStructure()
		{
			indexingSize = 0;
			// size = 0;
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

		void init(const StructDefinition* structDefinition, LynxID _lynxID);

		int toBuffer(char *dataBuffer, SendMode sendMode = eAllVariables, int subindex = 0);			// Returns size of copied data if success, -1 if failure, -2 if checksum is wrong

		int fromBuffer(const char *dataBuffer); // Returns size of copied data if success, -1 if failure

		void clear();							// sets all elements to 0

		const StructDefinition* structDefinition() { return _structDefinition; };

		int getSize() { return this->_structDefinition->size; };

		bool dataChanged();

		template <class T>
		int copyDataToTarget(void* target, int size = 0)
		{
			if (!(_structDefinition->structMode == eArrayMode))
			{
				return -2;
			}
			if (size == 0)
			{
				size = this->_structDefinition->size;
			}
			else
			{
				if (size > _structDefinition->size)
				{
					return -1;
				}
			}
			if (this->checkLocalSize(this->_structDefinition->structItems->dataType) != sizeof(T))
			{
				return -3;
			}

			T* pDest = (T*)(target);
			T* pSrc = (T*)(this->data);

			for (int i = 0; i < size; i++)
			{
				pDest[i] = pSrc[i];
			}

			this->_dataChanged = false;

			return size;
		}

		template <class T>
		int copyDataFromTarget(const void* target, int size = 0)
		{
			if (!(_structDefinition->structMode == eArrayMode))
			{
				return -2;
			}
			if (size == 0)
			{
				size = this->_structDefinition->size;
			}
			else
			{
				if (size > _structDefinition->size)
				{
					return -1;
				}
			}
			if (this->checkLocalSize(this->_structDefinition->structItems->dataType) != sizeof(T))
			{
				return -3;
			}

			T* pSrc = (T*)(target);
			T* pDest = (T*)(this->data);

			for (int i = 0; i < size; i++)
			{
				pDest[i] = pSrc[i];
			}

			this->_dataChanged = true;

			return size;
		}

		template <class T>
		T getData(int identifier)
		{	
			int offset = getOffset(identifier);
			if (offset < 0)
			{
				return T();
			}

			this->_dataChanged = false;
			
			return *(T*)(data + offset);

		}

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

		}

		template <class T>
		bool getBit(int identifier, T bitMask)
		{
			return ((getData<T>(identifier) & bitMask) != 0);
		}

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
		}

	private:
		// const char* _structName;
		
		int getOffset(int identifier);

		int indexingSize;
		// int size;

		char *data;

		bool _dataChanged;

		const StructDefinition* _structDefinition;

		int checkLocalSize(LynxDataType dataType);

		int checkTransferSize(LynxDataType dataType);

		int writeVarToBuffer(char* dataBuffer, int bufferIndex, int lynxIndex);

		int writeVarFromBuffer(const char* dataBuffer, int bufferIndex, int lynxIndex);


	};

	//----------------------------------------------- LynxHandler ------------------------------------------------------------

	class LynxHandler
	{
	public:
		// uint8_t deviceID;

		LynxHandler(uint8_t _deviceID, const char* _deviceName, int nStructs = 0)
		{
			this->_deviceInfo.deviceID = _deviceID;

			for (int i = 0; i < 20; i++)
			{
				if ((_deviceName[i] == '\0') || (i == 19))
				{
					this->_deviceInfo.deviceName[i] = '\0';
					break;
				}
				this->_deviceInfo.deviceName[i] = _deviceName[i];
			}
			_size = 0;
			_reservedSize = 0;
			_structures = nullptr;
			// _newScanResponses = 0;
			_newScanRequest = false;
			this->init(nStructs);
		};

		~LynxHandler()
		{
			if (_structures)
			{
				delete[] _structures;
				_structures = nullptr;
			}
		};

		void init(int nStructs = 0);

		LynxID addStructure(uint8_t _structType, uint8_t _structInstance, const StructDefinition* _structDefinition);

		int scanRequest(char* dataBuffer);

		template <class T>
		int copyDataToTarget(LynxID _lynxID, void* target, int size = 0)
		{
			int index = this->indexFromID(_lynxID);

			if (index < 0)
			{
				return index;
			}

			return _structures[index].copyDataToTarget<T>(target, size);
		}

		template <class T>
		int copyDataFromTarget(LynxID _lynxID, const void* target, int size = 0)
		{
			int index = this->indexFromID(_lynxID);

			if (index < 0)
			{
				return index;
			}

			return _structures[index].copyDataFromTarget<T>(target, size);
		}

		template <class T>
		T getData(LynxID _lynxID, int _identifier)
		{
			int index = this->indexFromID(_lynxID);

			if (index >= 0)
			{
				return this->_structures[index].getData<T>(_identifier);
			}
	
			return 0;
		}

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
		}

		template <class T>
		bool getBit(LynxID _lynxID, int identifier, T bitMask)
		{
			int index = this->indexFromID(_lynxID);
			if (index < 0)
			{
				return false;
			}

			return this->_structures[index].getBit<T>(identifier, bitMask);
		}

		template <class T>
		void setBit(LynxID _lynxID, int identifier, T bitMask, bool state)
		{
			int index = this->indexFromID(_lynxID);
			if (index < 0)
			{
				return;
			}

			this->_structures[index].setBit<T>(identifier, bitMask, state);
		}

		int toBuffer(LynxID _lynxID, char* dataBuffer, SendMode sendMode = eAllVariables, int subIndex = 0 );

		int fromBuffer(const char* dataBuffer, LynxIpAddress ipAddress = LynxIpAddress());

		bool dataChanged(LynxID _lynxID);

		int size() { return _size; };

		int newScanResponses(); // returns number of remaining scan responses

		LynxDeviceInfo getScanResponse();

		bool newScanRequest() { return _newScanRequest; };

		int sendScanResponse(char* dataBuffer);

	private:
		LynxDeviceInfo _deviceInfo;

		// char deviceName[20];

		// bool _newScanResponse;

		bool _newScanRequest;

		LynxList<LynxDeviceInfo> _availableDevices;
		// int _newScanResponses;

		int checkAvailableDevices(LynxDeviceInfo& deviceName);

		LynxStructure* _structures;
		int _size;
		int _reservedSize;

		int indexFromID(LynxID _lynxID);

		int handleRequest(const char* dataBuffer, LynxIpAddress ipAddress);

		int handleResponse(const char* dataBuffer, LynxIpAddress ipAddress);

		LynxDeviceInfo receiveScanResponse(const char* dataBuffer, LynxIpAddress ipAddress);

		int datagramFromBuffer(const char* dataBuffer);
	};


 }