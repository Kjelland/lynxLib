#pragma once
#include <stdint.h>

namespace LynxStructure
{
	enum LynxDataType
	{
		eEndOfList = 0,
		eInt8,
		eUint8,
		eInt16,
		eUint16,
		eInt32,
		eUint32,
		eInt64,
		eUint64
	};

	struct LynxID
	{
		uint8_t deviceID;	// Identifies the current machine
		uint8_t structID;	// Must be the same on both sides
	};

	enum E_Endianness
	{
		eNotChecked,
		eLittle,
		eBig
	};

	static void memcpyEndian(const void* src, void* dst, int size, E_Endianness srcEndian, E_Endianness dstEndian)
	{
		const char* charSrc = (char*)src;
		char* charDst = (char*)dst;

		if (srcEndian == dstEndian)
		{
			for (int i = 0; i < size; i++)
			{
				charDst[i] = charSrc[i];
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				charDst[size - i - 1] = charSrc[i];
			}
		}
	}

	// template <class T>
	class LynxStructure
	{
	public:
		struct InitParam
		{
			int identifier;
			LynxDataType dataType;
		};

		LynxID lynxID; // identifies current datagram

		LynxStructure()
		{
			indexingSize = 0;
			size = 0;
			data = NULL;
			dataParams = NULL;
		};

		~LynxStructure()
		{
			if (dataParams)
			{
				delete dataParams;
				dataParams = NULL;
			}
			if (data)
			{
				delete data;
				data = NULL;
			}
		}

		void init(InitParam initParams[], LynxID _lynxID, int nElements = 0);

		int toBuffer(char *dataBuffer);			// Returns size of copied data if success, -1 if failure, -2 if checksum is wrong

		int fromBuffer(const char *dataBuffer); // Returns size of copied data if success, -1 if failure

		void clear(); // sets all elements to 0

		template <class T>
		T getData(int target)
		{
			int index = getOffset(target);

			T temp = 0;
			T temp2 = 0;

			if (index >= 0)
			{
				int dataDiff = sizeof(T) - sizeof(char);

				for (int i = 0; i <= dataDiff; i++)
				{
					temp2 = ((T)data[index + i] << (i * 8)) & (0xFF << (i*8));
					temp = temp | temp2;
				}
			}

			return temp;
		};

		template <class T>
		void setData(int target, T dataIn)
		{
			int index = getOffset(target);

			if (index >= 0)
			{
				int dataDiff = sizeof(T) - sizeof(char);

				T temp = dataIn;

				for (int i = 0; i <= dataDiff; i++)
				{
					data[index + i] = (char)(temp & 0xFF);
					temp >>= 8;
				}
			}
		};

		//template <class T>
		//T& getReference(int target)
		//{
		//	// T& temp = (T&)0;

		//	int index = getOffset(target);
		//	if (index > -1)
		//	{
		//		T& temp = (T&)*(data + index);
		//		return temp;
		//	}

		//	// return temp;
		//} does not work

	private:
		int getOffset(int target);

		int indexingSize;
		int size;

		char *data;

		InitParam *dataParams;

		int checkSize(LynxDataType dataType);

		int checkTransferSize(LynxDataType dataType);

		/*
		template <class T>
		static void toArray(const T srcValue, void* dstArray, E_Endianness srcEndian, E_Endianness dstEndian, int size = 0) // Use size to force copy sumber of chars, 8 bit char is then assumed
		{
			int copySize = 0;
			if (size == 0)
			{
				if (srcEndian == dstEndian)
				{
					*(T*)dstArray = srcValue;
					return;
				}
				else
				{
					copySize = sizeof(T) - sizeof(char) + 1;
				}
			}
			else if (size > 0)
			{
				copySize = size;
			}
			else
			{
				return;
			}

			memcpyEndian(&srcValue, dstArray, copySize, srcEndian, dstEndian);

		}
		*/
	};

	class StaticProperties
	{
	public:
		static E_Endianness localEndian;
		static E_Endianness init();
	private:
		StaticProperties() {};
		~StaticProperties() {};
	};

	E_Endianness StaticProperties::localEndian { eNotChecked };

	E_Endianness StaticProperties::init()
	{
		union
		{
			uint32_t testVar;
			char testArray[sizeof(testVar)];
		}test;

		test.testVar = 1;

		if (test.testArray[0] == 1)
		{
			StaticProperties::localEndian = eLittle;
			return eLittle;
		}
		else
		{
			StaticProperties::localEndian = eBig;
			return eBig;
		}

	}



	int LynxStructure::toBuffer(char *dataBuffer)
	{
		int tempTransferSize;
		int index = 0;

		//  Write ID
		dataBuffer[index] = (char)this->lynxID.deviceID;
		index++;
		dataBuffer[index] = (char)this->lynxID.structID;
		index++;

		// Write data
		for (int i = 0; i < this->size; i++)
		{
			tempTransferSize = checkTransferSize(this->dataParams[i].dataType);
			switch (tempTransferSize)
			{
			case 1:
				dataBuffer[index] = (char)getData<uint8_t>(i);
				index++;
				break;
			case 2:
			{
				uint16_t temp = getData<uint16_t>(i);
				for (int n = 0; n < 2; n++)
				{
					dataBuffer[index] = (char)((temp >> (n * 8)) & 0xFF);
					index++;
				}
			}
			break;
			case 4:
			{
				uint32_t temp = getData<uint32_t>(i);
				for (int n = 0; n < 4; n++)
				{
					dataBuffer[index] = (char)((temp >> (n * 8)) & 0xFF);
					index++;
				}
			}
			break;
			case 8:
			{
				uint64_t temp = getData<uint64_t>(i);
				for (int n = 0; n < 8; n++)
				{
					dataBuffer[index] = (char)((temp >> (n * 8)) & 0xFF);
					index++;
				}
			}
			break;
			default:
				break;
			}
		}

		// Check data
		char checksum = 0;
		for (int i = 0; i < index; i++)
		{
			checksum += data[i];
		}
		dataBuffer[index] = checksum;

		return (index + 1);
	}

	int LynxStructure::fromBuffer(const char *dataBuffer)
	{
		int tempTransferSize;
		int index = 0;

		//  Read ID
		LynxID tempID;
		tempID.deviceID = (uint8_t)dataBuffer[index];
		index++;
		tempID.structID = (uint8_t)dataBuffer[index];
		index++;
		if (tempID.structID != this->lynxID.structID)
		{
			return -1;
		}

		// Read data
		for (int i = 0; i < this->size; i++)
		{
			tempTransferSize = checkTransferSize(this->dataParams[i].dataType);
			switch (tempTransferSize)
			{
			case 1:
				setData<uint8_t>(i, (uint8_t)dataBuffer[index]);
				index++;
				break;
			case 2:
			{
				uint16_t temp = 0;
				for (int n = 0; n < 2; n++)
				{
					temp |= (((uint16_t)dataBuffer[index] << (n * 8)) & (0xFF << (n * 8)));
					index++;
				}
				setData<uint16_t>(i, temp);
			}
			break;
			case 4:
			{
				uint32_t temp = 0; getData<uint32_t>(i);
				for (int n = 0; n < 4; n++)
				{
					temp |= (((uint32_t)dataBuffer[index] << (n * 8)) & (0xFF << (n * 8)));
					index++;
				}
				setData<uint32_t>(i, temp);
			}
				break;
			case 8:
			{
				uint64_t temp = 0; getData<uint64_t>(i);
				for (int n = 0; n < 4; n++)
				{
					temp |= (((uint64_t)dataBuffer[index] << (n * 8)) & (0xFF << (n * 8)));
					index++;
				}
				setData<uint64_t>(i, temp);
			}
				break;
			default:
				break;
			}
		}

		// Check data
		char checksum = 0;
		for (int i = 0; i < index; i++)
		{
			checksum += data[i];
		}

		if (checksum == dataBuffer[index])
		{
			return (index + 1);
		}
		else
		{
			return -2;
		}

	}


	void LynxStructure::clear()
	{
		for (int i = 0; i < this->size*this->indexingSize; i++)
		{
			data[i] = 0;
		}
	}

	int LynxStructure::checkSize(LynxDataType dataType)
	{
		int temp = 0;
		switch (dataType)
		{
		case eInt8:
			temp = sizeof(int8_t);
			break;
		case eUint8:
			temp = sizeof(uint8_t);
			break;
		case eInt16:
			temp = sizeof(int16_t);
			break;
		case eUint16:
			temp = sizeof(uint16_t);
			break;
		case eInt32:
			temp = sizeof(int32_t);
			break;
		case eUint32:
			temp = sizeof(uint32_t);
			break;
		case eInt64:
			temp = sizeof(int64_t);
			break;
		case eUint64:
			temp = sizeof(uint64_t);
			break;
		default:
			break;
		}

		return temp;
	}

	int LynxStructure::checkTransferSize(LynxDataType dataType)
	{
		int temp = 0;
		switch (dataType)
		{
		case eInt8:
			temp = 1;
			break;
		case eUint8:
			temp = 1;
			break;
		case eInt16:
			temp = 2;
			break;
		case eUint16:
			temp = 2;
			break;
		case eInt32:
			temp = 4;
			break;
		case eUint32:
			temp = 4;
			break;
		case eInt64:
			temp = 8;
			break;
		case eUint64:
			temp = 8;
			break;
		default:
			break;
		}

		return temp;
	}

	void LynxStructure::init(InitParam initParams[], LynxID _lynxID, int nElements)
	{
		this->lynxID = _lynxID;

		if (nElements == 0)
		{
			this->size = 255;
		}
		else
		{
			this->size = nElements;
		}

		int tempSize;
		for (int i = 0; i < this->size; i++)
		{
			if (initParams[i].dataType == eEndOfList)
			{
				this->size = i;
				break;
			}

			tempSize = checkSize(initParams[i].dataType);
		
			if ( tempSize > this->indexingSize )
			{
				this->indexingSize = tempSize;
			}

		}

		if (data)
		{
			delete data;
		}
		if (dataParams)
		{
			delete dataParams;
		}

		data = new char[this->size*this->indexingSize];
		dataParams = new InitParam[this->size];
	
		this->clear();

		for (int i = 0; i < this->size; i++)
		{
			dataParams[i] = initParams[i];
		}
	}

	int LynxStructure::getOffset(int target)
	{
		if (this->size == 0)
		{
			return -1;
		}

		return (target * this->indexingSize);

	

		//for (int i = 0; i < this->size; i++)
		//{
		//	if (this->dataParams[i].identifier == target)
		//	{
		//		index = i * this->indexingSize;
		//		break;
		//	}
		//}

		// return index;
	}

 }