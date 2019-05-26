//-------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------- Version 1.3.0.1 ----------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

#pragma once
#include <stdint.h>
#define LYNX_VERSION { 1, 3, 0, 1 }

#ifndef NULL
#ifndef TI
#define NULL nullptr
#else
#define NULL 0
#endif // !TI
#endif // !NULL

#ifdef TI
#include "DSP28x_Project.h"
typedef int16_t int8_t;
#endif //TI

#define LYNX_INTERNAL_DATAGRAM char(255)

#define LYNX_ID_BYTES 3
#define LYNX_INDEXER_BYTES 2
#define LYNX_CHECKSUM_BYTES 1

namespace LynxLib
{
	//---------------------------------------------------------------------------------------------------------------------------
	//----------------------------------------------------- Enums ---------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------

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
		eSsEndOfList
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

	//---------------------------------------------------------------------------------------------------------------------------
	//--------------------------------------------------- Structures ------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------
	
	//struct Union_8_32
	//{

	//};

	//struct LynxVersion
	//{
	//	const char version[4] = LYNX_VERSION;
	//};

	struct LynxID
	{
		LynxID()
		{
			deviceID = 0;
			structTypeID = 0;
			structInstanceID = 0;
			// totalLength = 0;
        }

        LynxID(uint8_t _deviceID, uint8_t _structTypeID, uint8_t _structInstanceID)
		{
			deviceID = _deviceID;
			structTypeID = _structTypeID;
			structInstanceID = _structInstanceID;
        }

        bool operator == (const LynxID& other) const
        {
            if((this->structTypeID == other.structTypeID) && (this->structInstanceID == other.structInstanceID))
                return true;

            return false;
        }

		uint8_t deviceID;			// Identifies the current machine
		uint8_t structTypeID;		// Identifies the type of struct
		uint8_t structInstanceID;	// Identifies the instance of the struct
	};

	struct StructItem
	{
		StructItem(const char _name[], LynxDataType _dataType)
            : name( _name ), dataType( _dataType ) {}
		const char* name;
		LynxDataType dataType;
    };

	struct StructDefinition
	{
		StructDefinition(const char _structName[], const LynxStructMode _structMode, const StructItem* _structItems, int _size = 0);

		const char* structName;
		const LynxStructMode structMode;
		const StructItem* structItems;
		int size;							// Number of elements in the list
		int transferSize = 0;				// Total data transfer size in bytes (not including identifiers and checksum)
	};

	struct LynxIpAddress
	{
		union Data
		{
			uint32_t data_32;
			unsigned char data_8[4];
		}data;

        LynxIpAddress() { data.data_32 = 0; }

        LynxIpAddress(uint32_t _data) { data.data_32 = _data; }

		LynxIpAddress(const unsigned char _data[4])
		{
			for (int i = 0; i < 4; i++)
			{
				data.data_8[i] = _data[i];
			}
        }

        LynxIpAddress(unsigned char ip0, unsigned char ip1, unsigned char ip2, unsigned char ip3)
		{
			data.data_32 = 1;

			if (data.data_8[0] == 1)	// Little endian
			{
				data.data_8[0] = ip3;
				data.data_8[1] = ip2;
				data.data_8[2] = ip1;
				data.data_8[3] = ip0;
			}
			else						// Big endian
			{
				data.data_8[0] = ip0;
				data.data_8[1] = ip1;
				data.data_8[2] = ip2;
				data.data_8[3] = ip3;
			}

        }

	};

	struct LynxDeviceInfo
	{
		LynxDeviceInfo()
			// : lynxVersion { 0,0,0,0 }
		{
			deviceName[0] = '\0';
			deviceID = 0;
			for (int i = 0; i < 4; i++)
			{
				lynxVersion[i] = 0;
			}
			ipAddress = LynxIpAddress();
			newDevice = false;
        }

		char deviceName[20];
		uint8_t deviceID;
		char lynxVersion[4];
		LynxIpAddress ipAddress;
		bool newDevice;
	};

	//---------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------- LynxRingBuffer ---------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------

	template <class T>
	class LynxRingBuffer
	{
	private:
		void writeElement(T element)
		{
			_buffer[_writeIndex] = element;

			_writeIndex++;

			if (_writeIndex >= _reservedSize)
				_writeIndex = 0;
		}

	public:
		enum E_RingBufferMode
		{
			eAllowOverflow = 0,
			ePreventOverflow,
			eRingBufferMode_EndOfList
		};

		LynxRingBuffer(E_RingBufferMode overflowMode = ePreventOverflow)
		{
			if (overflowMode < eRingBufferMode_EndOfList)
				_overflowMode = overflowMode;
			else
				_overflowMode = ePreventOverflow;

			_buffer = NULL;
			_reservedSize = 0;
			_writeIndex = 0;
			_readIndex = 0;
			_count = 0;
		}

		LynxRingBuffer(int size, E_RingBufferMode overflowMode = ePreventOverflow)
		{
			if (overflowMode < eRingBufferMode_EndOfList)
				_overflowMode = overflowMode;
			else
				_overflowMode = ePreventOverflow;

			_buffer = NULL;

			this->init(size);
		}

		~LynxRingBuffer()
		{
			if (_buffer)
			{
				delete[] _buffer;
				_buffer = NULL;
			}
		}

		// Initializer, reserves space for data. If init has been run before, previous data will be deleted. 
		// Returns number of elements reserved (should be the same as "size"), or -1 if error.
		int init(int size)
		{
			if (_buffer)
			{
				delete[] _buffer;
				_buffer = NULL;
			}

			_buffer = new T[size];

			if (_buffer)
			{
				_count = 0;
				_writeIndex = 0;
				_readIndex = 0;
				_reservedSize = size;

				return _reservedSize;
			}

			return -1;
		}

		bool setOverflowMode(E_RingBufferMode overflowMode)
		{
			if (overflowMode >= eRingBufferMode_EndOfList)
				return false;

			_overflowMode = overflowMode;
			return true;
		}

		E_RingBufferMode getOverflowMode()
		{
			return _overflowMode;
		}

		// Returns number of elements currently stored in buffer.
		int count()
		{
			return _count;
		}

		// Returns free space in buffer.
		int freeCount()
		{
			return (_reservedSize - _count);
		}

		int reservedSize()
		{
			return _reservedSize;
		}

		// Returns one element from the buffer. If there is nothing in the buffer, 0 is returned.
		T read()
		{
			if (_count <= 0)
				return T();

			T temp = _buffer[_readIndex];

			_count--;
			_readIndex++;
			if (_readIndex >= _reservedSize)
				_readIndex = 0;

			return temp;
		}

		// Reads "count" elements from the buffer and places it in "target".
		// If "count" is greater then number of elements in buffer, available elements will be read.
		// Returns number of elements read. 
		int read(T* target, int count)
		{
			int size;
			if (count > _count)
				size = _count;
			else
				size = count;

			for (int i = 0; i < size; i++)
			{
				target[i] = this->read();
			}

			return size;
		}

		// Writes one element "source" to the buffer
		// Overflow allowed:
		//		Returns true if the buffer is overflowing (data will be overwritten), otherwise false
		// Overflow prevented:
		//		Returns true if the buffer is full (data will not be written), otherwise false
		bool write(T source)
		{
			if (_count < _reservedSize)
			{
				writeElement(source);
				_count++;
				return false;
			}
			
			switch (_overflowMode)
			{
			case eAllowOverflow:
				writeElement(source);
				break;
			case ePreventOverflow:
				break;			
			}
			
			return true;

		}

		// Writes "count" elements from "source" to the buffer.
		// Overflow allowed:
		//		Returns -1 * elements written if the buffer is overflowing (data will be overwritten), otherwise it returns elements written.
		// Overflow prevented:
		//		Returns -1 * elements written if the buffer is full (data above max index will not be written), otherwise it returns elements written
		int write(const T* source, int count)
		{
			bool overflow;

			for (int i = 0; i < count; i++)
			{
				overflow = this->write(source[i]);

				if (overflow && (_overflowMode == ePreventOverflow))
					break;
			}

			if (overflow)
				return (~count + 1);

			return count;
		}

	private:
		T* _buffer;

		int _count;
		int _reservedSize;

		int _writeIndex;
		int _readIndex;

		E_RingBufferMode _overflowMode;
	};

	//---------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------- LynxList -------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------

	template <class T>
	class LynxList
	{
	public:
		LynxList()
		{
			_list = NULL;
			_size = 0;
			_reservedSize = 0;
        }

		LynxList(int size)
		{
			this->reserve(size);
        }

		LynxList(const LynxList<T>& list)
		{
			_list = NULL;
			*this = list;
        }

		~LynxList()
		{
			if (_list != NULL)
			{
				delete[] _list;
				_list = NULL;
			}
        }

		void operator = (const LynxList<T>& list)
		{
			this->reserve(list._size);

			for (int i = 0; i < this->_size; i++)
			{
				this->_list[i] = list._list[i];
			}

			this->_size = list._size;
        }

		void reserve(int size)
		{
			if (_list != NULL)
			{
				delete[] _list;
				_list = NULL;
			}

			_size = 0;
			_reservedSize = size;
			_list = new T[size];
        }

		int appendItem(const T& item) // Adds a new item at the end of the list and populates it with "item". Returns index of appended item if successful, -1 if unsuccessful
		{
			_size++;

			if (_size > _reservedSize)
			{
				_reservedSize++;

				T* tempList = new T[_reservedSize];

				if (_list != NULL)
				{
					for (int i = 0; i < _reservedSize - 1; i++)
					{
						tempList[i] = _list[i];
					}

					delete[] _list;
				}

				_list = tempList;
				tempList = NULL;
			}

			_list[_size - 1] = item;

			return (_size - 1);
		
        }
		
		// Adds a new empty instance at the end of the list. Returns index of appended item if successful, -1 if unsuccessful
		int appendItem()
		{
			return this->appendItem(T());
        }

		// Removes the indexed item and shifts the remaining items to fill
		// Returns number of remaining items if successful, -1 if failed
		int removeItem(int index)
		{
			if (index < this->_size)
			{
				_size--;
				if (_size <= 0)
				{
					return this->_size;
				}

				for (int i = index; i < _size; i++)
				{
					_list[i] = _list[i + 1];
				}
				return this->_size;
			}

			return -1;
        }

		// Clears the list and frees the allocated memory
		void deleteList()
		{
			_size = 0;
			_reservedSize = 0;
			if (_list != NULL)
			{
				delete[] _list;
				_list = NULL;
			}
        }

		void clear()
		{
			_size = 0;
		}

		T& at(int index)
		{
			return _list[index];
        }

        int getSize() { return _size; }

	protected:
		T* _list;

		// T emptyReference;
		int _size;
		int _reservedSize;
	};
	
	//---------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------ LynxStructure ------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------

	class LynxStructure
	{
	public:

		LynxID lynxID; // identifies current datagram

		LynxStructure()
		{
			_indexingSize = 0;
			_data = NULL;
			_structDefinition = NULL;
			_dataChanged = false;
        }

		~LynxStructure()
		{
			if (_data != NULL)
			{
				delete[] _data;
				_data = NULL;
			}
        }

		void init(const StructDefinition* structDefinition, LynxID _lynxID);

		int toBuffer(char *dataBuffer, SendMode sendMode = eAllVariables, int subindex = 0);			// Returns size of copied data if success, -1 if failure, -2 if checksum is wrong

		int fromBuffer(const char *dataBuffer); // Returns size of copied data if success, -1 if failure

		void clear();							// sets all elements to 0

        const StructDefinition* structDefinition() { return _structDefinition; }

        int getSize() { return this->_structDefinition->size; } // Returns number of elements in struct

		int getIndexingSize() { return this->_indexingSize; } // Returns number of bytes per index 

        void* getDataPointer() { return _data; }

		// Returns the total size of the datapackage in bytes
        int getTransferSize(int subIndex = -1);

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

            T* pDest = static_cast<T*>(target);
            T* pSrc = static_cast<T*>(this->_data);

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
			if (!(this->_structDefinition->structMode == eArrayMode))
			{
				return -2;
			}
			if (size == 0)
			{
				size = this->_structDefinition->size;
			}
			else
			{
				if (size > this->_structDefinition->size)
				{
					return -1;
				}
			}
			if (this->checkLocalSize(this->_structDefinition->structItems->dataType) != sizeof(T))
			{
				return -3;
			}

            T* pSrc = static_cast<T*>(target);
            T* pDest = static_cast<T*>(this->_data);

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
			
            return *(reinterpret_cast<T*>(_data + offset));

		}

		template <class T>
		void setData(int identifier, T dataIn)
		{
			int offset = getOffset(identifier);
			if (offset < 0)
			{
				return;
			}

            T* temp = reinterpret_cast<T*>(_data + offset);

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

		static int checkLocalSize(LynxDataType dataType);

		static int checkTransferSize(LynxDataType dataType);

	private:
		int getOffset(int identifier);

		int writeVarToBuffer(char* dataBuffer, int bufferIndex, int lynxIndex);

		int writeVarFromBuffer(const char* dataBuffer, int bufferIndex, int lynxIndex);

		int _indexingSize;

		char* _data;

		bool _dataChanged;

		const StructDefinition* _structDefinition;

	};

	//---------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------- LynxHandler ------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------

	class LynxHandler
	{
	public:
		// uint8_t deviceID;

		LynxHandler(uint8_t _deviceID, const char* _deviceName, int nStructs = 0)
		{
			this->_deviceInfo.deviceID = _deviceID;
			
			char tempVersion[4] = LYNX_VERSION;
			for (int i = 0; i < 4; i++)
			{
				_deviceInfo.lynxVersion[i] = tempVersion[i];
			}

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
			_structures = NULL;
			// _newScanResponses = 0;
			_newScanRequest = false;
			this->init(nStructs);
        }

		~LynxHandler()
		{
			if (_structures)
			{
				delete[] _structures;
				_structures = NULL;
			}
        }

		void init(int nStructs = 0);

		LynxID addStructure(uint8_t _structType, uint8_t _structInstance, const StructDefinition* _structDefinition);

		int scanRequest(char* dataBuffer);

		int copyData(LynxID source, LynxID target);

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

        int getTranferSize(LynxID _lynxID, int subIndex = -1);

		LynxList<LynxID> getIDs();

		void getIDs(LynxList<LynxID>& list);

		// static int getTransferSize(StandardStructIDs internalDatagram);

        int size() { return _size; }

		int newScanResponses(); // returns number of remaining scan responses

		LynxDeviceInfo getScanResponse();

        bool newScanRequest() { return _newScanRequest; }

		int sendScanResponse(char* dataBuffer);

        // Returns true if "_lynxID" exists in the hendler, false if not
        bool isMember(LynxID _lynxID);

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

		int indexFromID(LynxID& _lynxID);

		int handleInternalDatagram(const char* dataBuffer, LynxIpAddress ipAddress);

		int handleRequest(const char* dataBuffer, LynxIpAddress ipAddress);

		int handleResponse(const char* dataBuffer, LynxIpAddress ipAddress);

		LynxDeviceInfo receiveScanResponse(const char* dataBuffer, LynxIpAddress ipAddress);

		int datagramFromBuffer(const char* dataBuffer);
	};


 }
