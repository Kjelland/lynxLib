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
		eUint64
	};

	struct LynxID
	{
		uint8_t deviceID;	// Identifies the current machine
		uint16_t structID;	// Must be the same on both sides
	};

	enum StandardStructIDs : uint16_t
	{
		invalidID = 0,
		structureRequest,
		structureResponse,
		scanRequest,
		scanResponse,
		endOfReserve
	};

	/*
	enum E_Endianness
	{
		eNotChecked,
		eLittle,
		eBig
	};
	*/
	/*
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
	*/

	class LynxStructure
	{
	public:
		struct StructDefinition
		{
			int identifier;
			LynxDataType dataType;
		};

		LynxID lynxID; // identifies current datagram

		LynxStructure()
		{
			indexingSize = 0;
			size = 0;
			data = nullptr;
			dataParams = nullptr;
		};

		~LynxStructure()
		{
			if (data)
			{
				delete data;
				data = nullptr;
			}
		}

		void init(const StructDefinition initParams[], LynxID _lynxID, int nElements = 0);

		int toBuffer(char *dataBuffer);			// Returns size of copied data if success, -1 if failure, -2 if checksum is wrong

		int fromBuffer(const char *dataBuffer); // Returns size of copied data if success, -1 if failure

		void clear();							// sets all elements to 0


		template <class T>
		T getData(int target)
		{	
			int offset = getOffset(target);
			if (offset < 0)
			{
				return 0;
			}

			return *(T*)(data + offset);

		};

		template <class T>
		void setData(int target, T dataIn)
		{
			int offset = getOffset(target);
			if (offset < 0)
			{
				return;
			}

			T* temp = (T*)(data + offset);

			*temp = dataIn;

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
		int getOffset(int target);

		int indexingSize;
		int size;

		char *data;

		const StructDefinition *dataParams;

		int checkSize(LynxDataType dataType);

		int checkTransferSize(LynxDataType dataType);


	};



 }