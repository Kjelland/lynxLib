#include "lynxstructure.h"

namespace LynxLib
{ 
#ifdef LYNX_INCLUDE_EXCEPTIONS
    const char * LynxMessages::outOfBoundsMsg = "Index out of bounds";
#endif // LYNX_INCLUDE_EXCEPTIONS
	
	//-----------------------------------------------------------------------------------------------------------
	//------------------------------------------ LynxString -----------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------

	LynxString::LynxString()
	{
		_string = LYNX_NULL;
		_count = 0;
		_reservedCount = 0;
	}

	LynxString::LynxString(int size) : LynxString()
	{
		this->reserve(size + 1);
	}

	LynxString::LynxString(const char * const other, int maxLength) : LynxString()
	{
		int copySize = findTermChar(other, maxLength) + 1;

		if (copySize < 1)
			return;

		this->reserve(copySize);

		memcpy(_string, other, copySize);
		
		_count = copySize;
	}

	LynxString::LynxString(const LynxString & other) : LynxString()
	{
		*this = other;
	}

	LynxString::~LynxString()
	{
		if (_string != LYNX_NULL)
		{
			delete[] _string;
			_string = LYNX_NULL;
		}
	}

	const char & LynxString::at(int index) const
	{
		return _string[index];
	}

	char & LynxString::first()
	{
		return _string[0];
	}

	const char & LynxString::first() const
	{
		return _string[0];
	}

	char & LynxString::last()
	{
		return _string[_count - 2];
	}

	const char & LynxString::last() const
	{
		return _string[_count - 2];
	}

	int LynxString::count() const
	{
		if (_count < 1)
			return 0;

		return (_count - 1);
	}

	const LynxString & LynxString::operator=(const LynxString & other)
	{
		if ((&other == this) || (other._count < 2))
			return *this;
		
		this->reserve(other._count);
		memcpy(_string, other._string, other._count);
		_count = other._count;
		
		return *this;
	}

	const LynxString & LynxString::operator=(const char * const other)
	{
		int copySize = findTermChar(other) + 1;

		if (copySize < 1)
			return *this;

		this->reserve(copySize);

		memcpy(_string, other, copySize);

		_count = copySize;
	}

	void LynxString::operator+=(const char & other)
	{
		this->append(other);
	}

	void LynxString::operator+=(const LynxString & other)
	{
		this->append(other);
	}

	void LynxString::operator+=(const char * const other)
	{
		this->append(other);
	}

	LynxString LynxString::operator+(const char & other)
	{
		LynxString temp(*this);
		temp.append(other);
		return temp;
	}

	LynxString LynxString::operator+(const LynxString & other)
	{
		LynxString temp(*this);
		temp.append(other);
		return temp;
	}

	LynxString LynxString::operator+(const char * const other)
	{
		LynxString temp(*this);
		temp.append(other);
		return temp;
	}

	void LynxString::reserve(int size)
	{
		_count = 0;

		if (size <= _reservedCount)
			return;

		if (_string != LYNX_NULL)
		{ 
			delete[] _string;
			_string = LYNX_NULL;
		}

		_reservedCount = size;
		_string = new char[_reservedCount];
	}

	void LynxString::resize(int size)
	{
		if ((size + 1) <= _reservedCount)
			return;

		if (_count < 1)
		{
			this->reserve(size + 1);
			return;
		}

		char * oldString = _string;

		_reservedCount = size + 1;
		_string = new char[_reservedCount];

		memcpy(_string, oldString, _count);

		delete[] oldString;
		oldString = LYNX_NULL;
	}

	LynxString LynxString::subString(int startIndex, int endIndex)
	{
		if ((startIndex < 0) || (endIndex >= (_count - 1)) || (startIndex > endIndex))
			return LynxString();

		int copySize = endIndex - startIndex + 1;

		LynxString temp(copySize);
		memcpy(temp._string, &(_string[startIndex]), copySize);
		temp._string[copySize] = '\0';
		temp._count = copySize + 1;

		return temp;
	}

	void LynxString::append(const char & other)
	{
		this->resize(_count);
		_string[_count - 1] = other;
		_count++;
	}

	void LynxString::append(const LynxString & other)
	{
		if (other._count < 2) // nothing to copy
			return;

		this->resize(_count + other._count - 2);
		memcpy(&(_string[_count - 1]), other._string, other._count);
		_count = _count + other._count - 1;
	}

	void LynxString::append(const char * const other, int maxLength)
	{
		int copyCount = findTermChar(other, maxLength) + 1;

		if (copyCount < 2) // nothing to copy
			return;

		this->resize(_count + copyCount - 2);
		memcpy(&(_string[_count - 1]), other, copyCount);
		_count = _count + copyCount - 1;
	}

	const char * LynxString::toCharArray() const
	{
		if (_count < 1)
			return "";

		return _string;
	}

	int LynxString::findTermChar(const char * str, int maxLength)
	{
		for (int i = 0; i < maxLength; i++)
		{
			if (str[i] == '\0')
			{
				return i;
			}
		}

		return -1;
	}

	char & LynxString::operator[](int index)
	{
		return _string[index];
	}


	//LynxString::LynxString(const char * const other, int maxLength)
	//{
	//	int length = 0;
	//	for (int i = 0; i < maxLength; i++)
	//	{
	//		if (other[i] == '\0')
	//		{
	//			length = i;
	//			break;
	//		}
	//	}

	//	if (length < 1)
	//		return;

	//	this->reserve(length);

	//	for (int i = 0; i < length; i++)
	//	{
	//		_data[i] = other[i];
	//	}

	//	_data[length] = '\0';
	//	_count = length + 1;
	//}

	//LynxString LynxString::subString(int startIndex, int endIndex)
	//{	
	//	LynxString temp;
	//	if (endIndex >= (_count - 1))
	//		return temp;

	//	temp.reserve(endIndex - startIndex + 1);
	//	this->subList(temp, startIndex, endIndex);
	//	temp._data[temp._count] = '\0';
	//	temp._count++;

	//	return temp;	
	//}

	//void LynxString::append(const char & other)
	//{
	//	_data[_count - 1] = other;
	//	LynxList::append('\0');
	//}

	//void LynxString::append(const char * const other)
	//{
	//	LynxString temp(other);
	//	this->append(temp);
	//}

	//void LynxString::append(const LynxString & other)
	//{
	//	_count--;
	//	LynxList::append(other);
	//}

	//const char * LynxString::toCharArray() const
	//{
	//	if (_count < 1)
	//	{
	//		return '\0';
	//	}

	//	return _data;
	//}

	//-----------------------------------------------------------------------------------------------------------
	//-------------------------------------------- LynxType -----------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------

	E_Endianness LynxType::_endianness = eNotSet;

	LynxType::LynxType()
	{
		if (_endianness == eNotSet)
		{
			_data._var_i64 = 1;
			if (_data.bytes[0] == 1)
				_endianness = eLittleEndian;
			else
				_endianness = eBigEndian;
		}

		_dataType = eInvalidType;
		_data._var_i64 = 0;
	}

	LynxType::LynxType(E_LynxDataType dataType) : LynxType()
	{
		_dataType = dataType;
	}

    int LynxType::toArray(LynxByteArray & buffer, E_LynxState & state) const
	{
		int localSize = this->localSize();
        int transferSize = this->transferSize();

        LynxByteArray tempBuffer(transferSize);

		switch (LynxType::endianness())
		{
		case LynxLib::eBigEndian:
            for (int i = 0; i < localSize; i++)
			{
                tempBuffer.append(_data.bytes[int(SIZE_64) - i - 1]);
			}
			break;
		case LynxLib::eLittleEndian:
            for (int i = 0; i < localSize; i++)
			{
                tempBuffer.append(_data.bytes[i]);
			}
			break;
		default:
            state = eEndiannessNotSet;
            return 0;
		}

        splitArray(tempBuffer, transferSize);

        if(tempBuffer.count() != transferSize)
        {
            state = eSplitArrayFailed;
            return 0;
        }

        buffer.append(tempBuffer);

        return transferSize;
	}

    int LynxType::fromArray(const LynxByteArray & buffer, int startIndex, E_LynxState & state)
	{
		int localSize = this->localSize();
        int transferSize = this->transferSize();

        LynxByteArray tempBuffer(transferSize);
        buffer.subList(tempBuffer, startIndex, (startIndex + transferSize - 1));

        int count = mergeArray(tempBuffer, localSize);

        if (count != localSize)
        {
            state = eMergeArrayFailed;
            return transferSize;
        }

		switch (LynxType::endianness())
		{
		case LynxLib::eBigEndian:
            for (int i = 0; i < localSize; i++)
			{
                _data.bytes[int(SIZE_64) - i - 1] = tempBuffer.at(i);
			}
			break;
		case LynxLib::eLittleEndian:
            for (int i = 0; i < localSize; i++)
			{
                _data.bytes[i] = tempBuffer.at(i);
			}
			break;
		default:
            state = eEndiannessNotSet;
			return 0;
		}

        return transferSize;
	}

	int LynxType::localSize() const { return LynxLib::localSize(_dataType); }

	int LynxType::transferSize() const { return LynxLib::transferSize(_dataType); }

	//-----------------------------------------------------------------------------------------------------------
	//-------------------------------------- Static Functions ---------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------

	int localSize(LynxLib::E_LynxDataType dataType)
	{
		switch (dataType)
		{
		case LynxLib::eInt8:
			return sizeof(int8_t);
		case LynxLib::eUint8:
			return sizeof(uint8_t);
		case LynxLib::eInt16:
			return sizeof(int16_t);
		case LynxLib::eUint16:
			return sizeof(uint16_t);
		case LynxLib::eInt32:
			return sizeof(int32_t);
		case LynxLib::eUint32:
			return sizeof(uint32_t);
		case LynxLib::eInt64:
			return sizeof(int64_t);
		case LynxLib::eUint64:
			return sizeof(uint64_t);
		case LynxLib::eFloat:
			return sizeof(float);
		case LynxLib::eDouble:
			return sizeof(double);
		default:
			break;
		}
	
		return 0;
	}
	
	int transferSize(LynxLib::E_LynxDataType dataType)
	{
		switch (dataType)
		{
		case LynxLib::eInt8:
			return 1;
		case LynxLib::eUint8:
			return 1;
		case LynxLib::eInt16:
			return 2;
		case LynxLib::eUint16:
			return 2;
		case LynxLib::eInt32:
			return 4;
		case LynxLib::eUint32:
			return 4;
		case LynxLib::eInt64:
			return 8;
		case LynxLib::eUint64:
			return 8;
		case LynxLib::eFloat:
			return 4;
		case LynxLib::eDouble:
			return 8;
		default:
			break;
		}
	
		return 0;
	}

	int splitArray(LynxByteArray & buffer, int desiredSize)
	{
		if (buffer.count() == desiredSize)
			return buffer.count();
		else if (buffer.count() > desiredSize)
			return -1;

		LynxByteArray temp(desiredSize);

		int shiftSize;
		char mask;

		while (temp.count() < desiredSize)
		{
			temp.clear();

			shiftSize = (desiredSize / buffer.count() / 2);
			mask = sizeMask(shiftSize);

			for (int i = 0; i < buffer.count(); i++)
			{
				temp.append(buffer.at(i) & mask);
				temp.append((buffer.at(i) >> (shiftSize * 8)) & mask);
			}

			buffer = temp;
		}

		return buffer.count();
	}

	int mergeArray(LynxByteArray & buffer, int desiredSize)
	{
		if (buffer.count() == desiredSize)
			return buffer.count();
		else if (buffer.count() < desiredSize)
			return -1;

		LynxByteArray temp(buffer.count() / 2);

		int maxSize = buffer.count();
		int shiftSize;
		char mask;
		char tempVar;

		while (buffer.count() > desiredSize)
		{
			temp.clear();

			shiftSize = maxSize / buffer.count();
			mask = sizeMask(shiftSize);

			for (int i = 0; i < buffer.count(); i += 2)
			{
				tempVar = 0;
				tempVar |= (buffer.at(i) & mask);
				tempVar |= ((buffer.at(i + 1) & mask) << (shiftSize * 8));

				temp.append(tempVar);
			}

			buffer = temp;
		}

		return buffer.count();
	}

	char sizeMask(int shiftSize)
	{
		char mask = 0;

		for (int i = 0; i < shiftSize; i++)
		{
			mask |= (char(0xff) << i * 8);
		}

		return mask;
	}

	//-----------------------------------------------------------------------------------------------------------
	//---------------------------------------- LynxStructure ----------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------

	LynxStructure::LynxStructure(int size) : LynxList(size)
	{
		_transferSize = 0;
		_localSize = 0;
		_structId = -1;
	}

	// LynxByteArray LynxStructure::toArray(int variableIndex) const
	// {
	// 	LynxByteArray temp;
	// 	this->toArray(temp, variableIndex);
	// 
	// 	return temp;
	// }

	E_LynxState LynxStructure::toArray(LynxByteArray & buffer, int variableIndex) const
	{
		if (_count < 1)
			return eNoStructuresInList;
		else if (variableIndex >= _count)
			return eVariableIndexOutOfBounds;

        E_LynxState state = eDataCopiedToBuffer;

		if (variableIndex < 0) // All variables
		{
			for (int i = 0; i < _count; i++)
			{
                _data[i].toArray(buffer, state);
			}
		}
		else // Single variable
		{
            _data[variableIndex].toArray(buffer, state);
		}

        return state;
	}

	E_LynxState LynxStructure::toArray(char * buffer, int maxSize, int & copiedSize, int variableIndex) const
	{
		LynxByteArray temp;
		E_LynxState state = this->toArray(temp, variableIndex);

		if (state != eDataCopiedToBuffer)
		{
			copiedSize = 0;
			return state;
		}

		copiedSize = temp.toCharArray(buffer, maxSize);
		if (copiedSize < 0)
		{
			copiedSize = 0;
			return eBufferTooSmall;
		}

		return state;
	}

    void LynxStructure::fromArray(const LynxByteArray & buffer, LynxInfo & lynxInfo)
	{
        int bufferIndex = LYNX_HEADER_BYTES;

        lynxInfo.state = eNewDataReceived;

        if (lynxInfo.lynxId.variableIndex < 0) // All variables
		{
			for (int i = 0; i < _count; i++)
			{
                bufferIndex += _data[i].fromArray(buffer, bufferIndex, lynxInfo.state);
			}
		}
        else if (lynxInfo.lynxId.variableIndex > _count) // Invalid index
		{
            lynxInfo.state = eVariableIndexOutOfBounds;
            return;
		}
		else // Single variable
		{
            bufferIndex += _data[lynxInfo.lynxId.variableIndex].fromArray(buffer, bufferIndex, lynxInfo.state);
		}
	}

    void LynxStructure::fromArray(const char * buffer, int size, LynxInfo & lynxInfo)
	{
        this->fromArray(LynxByteArray(buffer, size), lynxInfo);
	}

	LynxId LynxStructure::addVariable(int structIndex, E_LynxDataType dataType)
	{
		this->append(LynxType(dataType));

		_transferSize += this->last().transferSize();
		_localSize += this->last().localSize();

		return LynxId(structIndex, (_count - 1));
	}

	int LynxStructure::transferSize(int index) const
	{
		if (index < 0) // All variables
		{
            return _transferSize;
		}
		else if (index >= _count) // Out of bounds
		{
			return 0;
		}
		else // Single variable
		{
			return _data[index].transferSize();
		}
	}

	int LynxStructure::localSize(int variableIndex) const
	{
		if (variableIndex < 0) // All variables
		{
			return _localSize;
		}
		else if (variableIndex >= _count) // Out of bounds
		{
			return 0;
		}
		else // Single variable
		{
			return _data[variableIndex].localSize();
		}
	}

	//-----------------------------------------------------------------------------------------------------------
	//--------------------------------------- LynxByteArray -----------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------

	LynxByteArray::LynxByteArray(const char * charArray, int size) : LynxList<char>(size)
	{
		for (int i = 0; i < size; i++)
		{
			_data[i] = charArray[i];
		}

		_count = size;
	}

	int LynxByteArray::toCharArray(char * buffer, int maxSize) const
	{
		if (_count > maxSize)
			return -1;

		for (int i = 0; i < _count; i++)
		{
			buffer[i] = _data[i];
		}

		return _count;
	}

	//-----------------------------------------------------------------------------------------------------------
	//----------------------------------------- LynxManager -----------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------

	LynxManager::LynxManager(char deviceId, int size) : LynxList(size) { _deviceId = deviceId; }

    char LynxManager::structId(const LynxId & lynxId)
    {
        if((lynxId.structIndex < 0) || (lynxId.structIndex > _count))
            return char(0xff);

        return _data[lynxId.structIndex].structId();
    }

	LynxType & LynxManager::variable(const LynxId & lynxId)
	{
		if ((lynxId.variableIndex < 0) || (lynxId.structIndex < 0))
		{
			_dummyVariable.var_i64() = 0;
			return _dummyVariable;
		}

		return (*this)[lynxId.structIndex][lynxId.variableIndex];
	}

	const LynxType & LynxManager::variable(const LynxId & lynxId) const
	{
		if ((lynxId.variableIndex < 0) || (lynxId.structIndex < 0))
		{
			return _dummyVariable;
		}

		return this->at(lynxId.structIndex).at(lynxId.variableIndex);
	}

	void LynxManager::copy(const LynxId & source, const LynxId & target)
	{
		if ((source.variableIndex < 0) || (target.variableIndex < 0))
			return;
		
		_data[target.structIndex][target.variableIndex].var_i64() = _data[source.structIndex][source.variableIndex].var_i64();
	}

	// LynxByteArray LynxManager::toArray(const LynxId & lynxId) const
	// {
	// 	LynxByteArray temp;
	// 
	// 	this->toArray(temp, lynxId);
	// 
	// 	return temp;
	// }

	E_LynxState LynxManager::toArray(LynxByteArray & buffer, const LynxId & lynxId) const
	{
		if ((lynxId.structIndex < 0) || (lynxId.structIndex >= _count))
			return eStructIndexOutOfBounds;

		int dataLength = _data[lynxId.structIndex].transferSize(lynxId.variableIndex);

		if (dataLength < 1)
			return eDataLengthNotFound;

		buffer.reserve(dataLength + LYNX_HEADER_BYTES + LYNX_CHECKSUM_BYTES);
		buffer.append(LYNX_STATIC_HEADER);
		buffer.append(_data[lynxId.structIndex].structId());
		buffer.append(static_cast<char>(lynxId.variableIndex + 1));
		buffer.append(static_cast<char>(dataLength));
		buffer.append(_deviceId);

		E_LynxState state = _data[lynxId.structIndex].toArray(buffer, lynxId.variableIndex);

		if (state != eDataCopiedToBuffer)
			return state;

		char checksum = 0;
		for (int i = 0; i < buffer.count(); i++)
		{
			checksum += buffer.at(i);
		}

		buffer.append(checksum & char(0xff));

		return state;
	}

	E_LynxState LynxManager::toArray(char * buffer, int maxSize, int & copiedSize, const LynxId & lynxId) const
	{
		LynxByteArray temp;
		E_LynxState state = this->toArray(temp, lynxId);

		if (state != eDataCopiedToBuffer)
		{
			copiedSize = 0;
			return state;
		}

		copiedSize = temp.toCharArray(buffer, maxSize);
		if (copiedSize < 0)
		{
			copiedSize = 0;
			return eBufferTooSmall;
		}

		return state;
	}

	void LynxManager::fromArray(const LynxByteArray & buffer, LynxInfo & lynxInfo)
	{
		lynxInfo.lynxId.structIndex = this->findId(buffer.at(1));
		lynxInfo.lynxId.variableIndex = buffer.at(2) - 1;
		lynxInfo.dataLength = buffer.at(3);
		lynxInfo.deviceId = buffer.at(4);

		// Check the struct ID
		if (lynxInfo.lynxId.structIndex < 0)
		{
			lynxInfo.state = eStructIdNotFound;
			return;
		}

		// Check the variable index
		if (lynxInfo.lynxId.variableIndex > _data[lynxInfo.lynxId.structIndex].count())
		{
			lynxInfo.state = eVariableIndexOutOfBounds;
			return;
		}

		// Check the total size
		int totalSize = lynxInfo.dataLength + LYNX_HEADER_BYTES + LYNX_CHECKSUM_BYTES;
		if (buffer.count() < totalSize)
		{
			lynxInfo.state = eBufferTooSmall;
			return;
		}

		// Calculate the checksum
		int checksumIndex = totalSize - 1;
		char checksum = 0;
		for (int i = 0; i < checksumIndex; i++)
		{
			checksum += buffer.at(i);
		}
		// Check the checksum
		if ((checksum & 0xff) != (buffer.at(checksumIndex) & 0xff))
		{
			lynxInfo.state = eWrongChecksum;
			return;
		}

		// Make a temporary buffer and extract the data
        // LynxByteArray temp;
        // buffer.subList(temp, LYNX_HEADER_BYTES, LYNX_HEADER_BYTES + lynxInfo.dataLength - 1);

		// Merge the databuffer if the local size is different from the transfersize
        // int count = mergeArray(temp, _data[lynxInfo.lynxId.structIndex].localSize(lynxInfo.lynxId.variableIndex));

		// Check if the merge was successful
        // if (count < 0)
        // {
        // 	lynxInfo.state = eMergeArrayFailed;
        // 	return;
        // }

		// Copy the data
        _data[lynxInfo.lynxId.structIndex].fromArray(buffer, lynxInfo);
	}

	void LynxManager::fromArray(const char * buffer, int size, LynxInfo & lynxInfo)
	{
		LynxByteArray temp(buffer, size);

		this->fromArray(temp, lynxInfo);
	}

	int LynxManager::transferSize(const LynxId & lynxId) const
	{
		return _data[lynxId.structIndex].transferSize(lynxId.variableIndex);
	}

	int LynxManager::localSize(const LynxId & lynxId) const
	{
		return _data[lynxId.structIndex].localSize(lynxId.variableIndex);
	}

	LynxId LynxManager::addStructure(char structId, int size)
	{
		LynxId temp;
		temp.structIndex = this->append();
		this->last().reserve(size);
		this->last().setStructId(structId);

		return temp;
	}

	LynxVar LynxManager::addVariable(const LynxId & lynxId, E_LynxDataType dataType)
	{
		 if ((lynxId.structIndex < 0) || (lynxId.structIndex > _count))
		 	return LynxVar(this, LynxId(-1, -1));
		 	
		 return LynxVar(this, _data[lynxId.structIndex].addVariable(lynxId.structIndex, dataType));
	}

	int LynxManager::structVariableCount(int structIndex)
	{
		if ((structIndex < 0) || (structIndex >= _count))
			return 0;

		return _data[structIndex].count();
	}

	int LynxManager::findId(char structId)
	{
		for (int i = 0; i < _count; i++)
		{
			if (_data[i].structId() == structId)
				return i;
		}
		return -1;
	}
	// LynxManager Lynx;
}