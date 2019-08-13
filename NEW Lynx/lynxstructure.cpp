#include "lynxstructure.h"

namespace LynxLib
{ 
#ifdef LYNX_INCLUDE_EXCEPTIONS
    const char * LynxMessages::outOfBoundsMsg = "Index out of bounds";
#endif // LYNX_INCLUDE_EXCEPTIONS

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

	int LynxType::localSize(E_LynxDataType dataType)
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

	int LynxType::transferSize(E_LynxDataType dataType)
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

	int LynxType::toArray(LynxByteArray & buffer) const
	{
		switch (LynxType::endianness())
		{
		case LynxLib::eBigEndian:
            for (int i = 0; i < this->transferSize(); i++)
			{
				buffer.append(_data.bytes[int(SIZE_64) - i - 1]);
			}
			break;
		case LynxLib::eLittleEndian:
            for (int i = 0; i < this->transferSize(); i++)
			{
				buffer.append(_data.bytes[i]);
			}
			break;
		default:
			return 0;
		}

        return this->transferSize();
	}

	int LynxType::fromArray(const LynxByteArray & buffer, int startIndex)
	{
		switch (LynxType::endianness())
		{
		case LynxLib::eBigEndian:
            for (int i = 0; i < this->transferSize(); i++)
			{
                _data.bytes[int(SIZE_64) - i - 1] = buffer.at(startIndex + i);
			}
			break;
		case LynxLib::eLittleEndian:
            for (int i = 0; i < this->transferSize(); i++)
			{
				_data.bytes[i] = buffer.at(startIndex + i);
			}
			break;
		default:
			return 0;
		}

        return this->transferSize();
	}

	LynxStructure::LynxStructure(LynxID lynxID) : _lynxID(lynxID)
	{
		_lynxID.length = 0;
		_lynxID.index = -1;
	}

	LynxByteArray LynxStructure::toArray(int index) const
	{
		LynxByteArray temp;
		this->toArray(temp, index);

		return temp;
	}

	void LynxStructure::toArray(LynxByteArray & buffer, int index) const
	{
		if ((_variables.count() < 1) || (index >= _variables.count()))
			return;

        buffer.reserve(this->transferSize(index) + LYNX_HEADER_BYTES + LYNX_CHECKSUM_BYTES);
		buffer.append(LYNX_STATIC_HEADER);
        buffer.append(static_cast<char>(_lynxID.structId));
        buffer.append(static_cast<char>(index + 1));

		if (index < 0)
            buffer.append(static_cast<char>(_lynxID.length));
		else
            buffer.append(static_cast<char>(_variables.at(index).transferSize()));

        buffer.append(static_cast<char>(_lynxID.deviceId));

		if (index < 0) // All variables
		{
			for (int i = 0; i < _variables.count(); i++)
			{
				_variables.at(i).toArray(buffer);
			}
		}
		else // Single variable
		{
			_variables.at(index).toArray(buffer);
		}

		char checksum = 0;
		for (int i = 0; i < buffer.count(); i++)
		{
			checksum += buffer.at(i);
		}

        buffer.append(checksum & char(0xff));
	}

	int LynxStructure::toArray(char * buffer, int index) const
	{
		LynxByteArray temp;
		this->toArray(temp, index);

		temp.toCharArray(buffer);

		return temp.count();
	}

    void LynxStructure::fromArray(const LynxByteArray & buffer, LynxID & lynxId)
	{
        int bufferIndex = LYNX_HEADER_BYTES;

        int totalSize = lynxId.length + LYNX_HEADER_BYTES + LYNX_CHECKSUM_BYTES;

		if (buffer.count() < totalSize)
		{
            lynxId.state = eBufferToSmall;
            return;
		}

		// Check the checksum
		int checksumIndex = totalSize - 1;
		char checksum = 0;
		for (int i = 0; i < checksumIndex; i++)
		{
			checksum += buffer.at(i);
		}

		if ((checksum & 0xff) != (buffer.at(checksumIndex) & 0xff))
		{
            lynxId.state = eWrongChecksum;
            return;
		}

        if (lynxId.index < 0) // All variables
		{
			for (int i = 0; i < _variables.count(); i++)
			{
				bufferIndex += _variables[i].fromArray(buffer, bufferIndex);
			}
		}
        else if (lynxId.index > _variables.count()) // Invalid index
		{
            lynxId.state = eIndexOutOfBounds;
            return;
		}
		else // Single variable
		{
            bufferIndex += _variables[lynxId.index].fromArray(buffer, bufferIndex);
		}

        lynxId.state = eNewDataReceived;
	}

    void LynxStructure::fromArray(const char * buffer, int size, LynxID & lynxId)
	{
        this->fromArray(LynxByteArray(buffer, size), lynxId);
	}

	void LynxStructure::addVariable(E_LynxDataType dataType)
	{
		_variables.append(LynxType(dataType));
		_lynxID.length += _variables.last().transferSize();
	}

	int LynxStructure::transferSize(int index) const
	{
		if (index < 0) // All variables
		{
            return _lynxID.length;
            // int totalSize = 0;
            // for (int i = 0; i < _variables.count(); i++)
            // {
            // 	totalSize += _variables.at(i).transferSize();
            // }
            // return totalSize;
		}
		else if (index >= _variables.count()) // Out of bounds
		{
			return 0;
		}
		else // Single variable
		{
			return _variables.at(index).transferSize();
		}
	}

	int LynxStructure::localSize(int index) const
	{
		if (index < 0) // All variables
		{
			int totalSize = 0;
			for (int i = 0; i < _variables.count(); i++)
			{
				totalSize += _variables.at(i).localSize();
			}
			return totalSize;
		}
		else if (index >= _variables.count()) // Out of bounds
		{
			return 0;
		}
		else // Single variable
		{
			return _variables.at(index).localSize();
		}
	}

	LynxByteArray::LynxByteArray(const char * charArray, int size) : LynxList<char>(size)
	{
		for (int i = 0; i < size; i++)
		{
			_data[i] = charArray[i];
		}

		_count = size;
	}

	void LynxByteArray::toCharArray(char * buffer) const
	{
		for (int i = 0; i < _count; i++)
		{
			buffer[i] = _data[i];
		}
	}
}
