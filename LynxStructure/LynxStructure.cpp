#include "LynxStructure.h"

namespace LynxLib
{

	StructDefinition::StructDefinition(const char* _structName, const LynxStructMode _structMode, const StructItem * _structItems, int _size)
		: structName(_structName), structMode(_structMode)
	{
		if (_structMode == eArrayMode)
		{
			int tempTransferSize = LynxStructure::checkTransferSize(_structItems->dataType);
			int tempLocalSize = LynxStructure::checkLocalSize(_structItems->dataType);
			
			if ((_size > 0) && (tempTransferSize > 0) && (tempLocalSize > 0))
				size = _size;
			else
				size = 0;

			this->transferSize = tempTransferSize * size;
			this->localSize = tempLocalSize * size;
			this->structItems.append(*_structItems);
		}
		else if (_size > 0)
		{
			size = _size;
			structItems.reserve(size);

			for (int i = 0; i < size; i++)
			{
				structItems.append(_structItems[i]);
				this->transferSize += LynxStructure::checkTransferSize(_structItems[i].dataType);
				this->localSize += LynxStructure::checkLocalSize(_structItems[i].dataType);
			}
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

				structItems.append(_structItems[i]);
				this->transferSize += LynxStructure::checkTransferSize(_structItems[i].dataType);
				this->localSize += LynxStructure::checkLocalSize(_structItems[i].dataType);
			}

			transferSize = 0;
			localSize = 0;
			size = 0;
		}
	}

	//---------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------- LynxStructure v1.4 ---------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------

	void LynxStructure::init(const StructDefinition& structDefinition, const LynxID& lynxID)
	{
		_structDefinition = &structDefinition;
		if (_structDefinition == LYNX_NULL)
			return;

		_lynxID = lynxID;

		if (_data != LYNX_NULL)
		{
			delete[] _data;
			_data = LYNX_NULL;
		}

		_data = new char[_structDefinition->localSize];

		switch (_structDefinition->structMode)
		{
			case LynxStructMode::eArrayMode:
			{
				_dataPointerList.reserve(_structDefinition->size);

				char* localPointer = _data;
				for (int i = 0; i < _structDefinition->size; i++)
				{
					_dataPointerList.append(localPointer);
					localPointer += LynxStructure::checkLocalSize(_structDefinition->structItems.at(0).dataType);
				}
			}
				break;
			case LynxStructMode::eStructureMode:
			{
				_dataPointerList.reserve(_structDefinition->size);

				char* localPointer = _data;
				for (int i = 0; i < _structDefinition->size; i++)
				{
					_dataPointerList.append(localPointer);
					localPointer += LynxStructure::checkLocalSize(_structDefinition->structItems.at(i).dataType);
				}
			}
				break;
		}

		this->clear();
	}

	int LynxStructure::toBuffer(LynxList<char>& dataBuffer, int subIndex) const
	{
		// Clear buffer, and reserve space if neccessary
		dataBuffer.clear();
		dataBuffer.reserveAndCopy(this->getTransferSize(subIndex) + LYNX_ID_BYTES + LYNX_INDEXER_BYTES + LYNX_CHECKSUM_BYTES);
		
		// Add ID to the buffer
		dataBuffer.append(static_cast<char>(this->_lynxID.deviceID));
		dataBuffer.append(static_cast<char>(this->_lynxID.structTypeID));
		dataBuffer.append(static_cast<char>(this->_lynxID.structInstanceID));

		// Add index to the buffer
		int tempIndex = subIndex + 1;
		dataBuffer.append(static_cast<char>(tempIndex & 0xff));
		dataBuffer.append(static_cast<char>((tempIndex >> 8) & 0xff));

		// Add data to the buffer
		// All variables if subIndex < 0, otherwise only subIndex
		int temp;
		if(subIndex < 0)
		{
			for (int i = 0; i < this->_structDefinition->size; i++)
			{
				temp = this->writeVarToBuffer(dataBuffer, i);
				if (temp < 0)
					return temp;
			}
		}
		else
		{
			temp = this->writeVarToBuffer(dataBuffer, subIndex);
			if (temp < 0)
				return temp;
		}

		// Calculate checksum
		char checksum = 0;
		for (int i = 0; i < dataBuffer.count(); i++)
		{
			checksum += dataBuffer.at(i);
		}
		dataBuffer.append(checksum);

		return dataBuffer.count();
	}

	int LynxStructure::fromBuffer(const LynxList<char>& dataBuffer)
	{
		// Check buffer size
		if (dataBuffer.count() < LYNX_ID_BYTES + LYNX_INDEXER_BYTES)
			return -12;

		// Read ID
		LynxID remoteID
		(
			static_cast<uint8_t>(dataBuffer.at(0)) & 0xff, 
			static_cast<uint8_t>(dataBuffer.at(1)) & 0xff, 
			static_cast<uint8_t>(dataBuffer.at(2)) & 0xff
		);

		if (remoteID != this->_lynxID)
			return -11;

		// Read subIndex
		int subIndex = static_cast<int>((static_cast<uint16_t>(dataBuffer.at(LYNX_ID_BYTES)) & 0xff)
			| ((static_cast<uint16_t>(dataBuffer.at(LYNX_ID_BYTES + 1)) & 0xff) << 8)) 
			- 1;

		// Check subIndex
		if (subIndex > this->_structDefinition->size)
			return -13;

		// Check the buffer again (now that we know the size)
		int totalTransferSize = this->getTransferSize(subIndex) + LYNX_ID_BYTES + LYNX_INDEXER_BYTES + LYNX_CHECKSUM_BYTES;
		if (dataBuffer.count() < totalTransferSize)
			return -14;
		

		// Check checksum
		char localChecksum = 0;
		for (int i = 0; i < totalTransferSize - 1; i++)
		{
			localChecksum += dataBuffer.at(i);
		}

		char remoteChecksum = dataBuffer.at(totalTransferSize - 1);

		if ((localChecksum & 0xff) != (remoteChecksum & 0xff))
			return -15;

		// Now it's safe to copy data
		int temp;
		int index = LYNX_ID_BYTES + LYNX_INDEXER_BYTES;

		if(subIndex < 0)
		{ 	
			for (int i = 0; i < this->_structDefinition->size; i++)
			{
				temp = this->writeVarFromBuffer(dataBuffer, index, i);
				if (temp < 0)
					return temp;
				index += temp;
			}
		}
		else
		{
			temp = this->writeVarFromBuffer(dataBuffer, index, subIndex);
			if (temp < 0)
				return temp;
			index += temp;
		}

		return totalTransferSize;
	}

	void LynxStructure::clear()
	{
		for (int i = 0; i < _structDefinition->localSize; i++)
		{
			_data[i] = 0;
		}
	}

	int LynxStructure::getTransferSize(int subIndex) const
	{
		if (subIndex < 0)
			return _structDefinition->transferSize;
		else
			return LynxStructure::checkTransferSize(_structDefinition->structItems.at(subIndex).dataType);
	}

	int LynxStructure::getLocalSize(int subIndex) const
	{
		if (subIndex < 0)
			return _structDefinition->localSize;
		else
			return LynxStructure::checkLocalSize(_structDefinition->structItems.at(subIndex).dataType);
	}

	int LynxStructure::checkLocalSize(LynxDataType dataType)
	{
		switch (dataType)
		{
		case eInt8:
			return sizeof(int8_t);
		case eUint8:
			return sizeof(uint8_t);
		case eInt16:
			return sizeof(int16_t);
		case eUint16:
			return sizeof(uint16_t);
		case eInt32:
			return sizeof(int32_t);
		case eUint32:
			return sizeof(uint32_t);
		case eInt64:
			return sizeof(int64_t);
		case eUint64:
			return sizeof(uint64_t);
		case eFloat:
			return sizeof(float);
		case eDouble:
			return sizeof(double);
        default:
            break;
		}

		return -6;
	}


	int LynxStructure::checkTransferSize(LynxDataType dataType)
	{
		switch (dataType)
		{
		case eInt8:
			return 1;
		case eUint8:
			return 1;
		case eInt16:
			return 2;
		case eUint16:
			return 2;
		case eInt32:
			return 4;
		case eUint32:
			return 4;
		case eInt64:
			return 8;
		case eUint64:
			return 8;
		case eFloat:
			return 4;
		case eDouble:
			return 8;
        default:
            break;
		}

		return -7;
	}

	void* LynxStructure::getDataPointer(int subIndex)
	{
        if(_data == LYNX_NULL)
            return LYNX_NULL;

		if (subIndex < 0)
			return _data;
		else
			return _dataPointerList[subIndex];
	}

	const void* LynxStructure::getConstDataPointer(int subIndex) const
	{
        if(_data == LYNX_NULL)
            return LYNX_NULL;

		if (subIndex < 0)
			return _data;
		else
			return _dataPointerList.at(subIndex);
	}

	int LynxStructure::writeVarToBuffer(LynxList<char>& dataBuffer, int subIndex) const
	{
		switch (LynxStructure::checkTransferSize(_structDefinition->structItems.at(subIndex).dataType))
		{
			case 1:
			{
				dataBuffer.append(static_cast<char>(this->getData<uint8_t>(subIndex)));
			} return 1;
			case 2:
			{
				char tmp[2];
				for (int i = 0; i < 2; i++)
				{
					tmp[i] = static_cast<char>((this->getData<uint16_t>(subIndex) >> i * 8) & uint16_t(0xff));
				}
				dataBuffer.append(tmp, 2);
			} return 2;
			case 4:
			{
				char tmp[4];
				for (int i = 0; i < 4; i++)
				{
					tmp[i] = static_cast<char>((this->getData<uint32_t>(subIndex) >> i * 8) & uint32_t(0xff));
				}
				dataBuffer.append(tmp, 4);
			} return 4;
			case 8:
			{
				char tmp[8];
				for (int i = 0; i < 8; i++)
				{
					tmp[i] = static_cast<char>((this->getData<uint64_t>(subIndex) >> i * 8) & uint64_t(0xff));
				}
				dataBuffer.append(tmp, 8);
			} return 8;
			default:
				break;
		}

		return -10;
	}

	int LynxStructure::writeVarFromBuffer(const LynxList<char>& dataBuffer, int bufferIndex, int subIndex)
	{
		switch (LynxStructure::checkTransferSize(_structDefinition->structItems.at(subIndex).dataType))
		{
		case 1:
		{
			this->setData<uint8_t>(subIndex, static_cast<uint8_t>(dataBuffer.at(bufferIndex)) & 0xff);
		} return 1;
		case 2:
		{
			uint16_t temp = 0;
			for (int i = 0; i < 2; i++)
			{
				temp |= (static_cast<uint16_t>(dataBuffer.at(bufferIndex + i)) & 0xff) << (8 * i);
			}
			this->setData<uint16_t>(subIndex, temp);
		} return 2;
		case 4:
		{
			uint32_t temp = 0;
			for (int i = 0; i < 4; i++)
			{
				temp |= (static_cast<uint32_t>(dataBuffer.at(bufferIndex + i)) & 0xff) << (8 * i);
			}
			this->setData<uint32_t>(subIndex, temp);
		} return 4;
		case 8:
		{
			uint64_t temp = 0;
			for (int i = 0; i < 8; i++)
			{
				temp |= (static_cast<uint64_t>(dataBuffer.at(bufferIndex + i)) & 0xff) << (8 * i);
			}
			this->setData<uint64_t>(subIndex, temp);
		} return 8;
		default:
			break;
		}

		return -16;
	}

	//---------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------- LynxHandler ------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------

	void LynxHandler::init(int nStructs)
	{
		if (nStructs > 0)
		{
			_structures.reserve(nStructs);
		}
	}

	LynxID LynxHandler::addStructure(uint8_t _structType, uint8_t _structInstance, const StructDefinition& _structDefinition)
	{
		if (_structDefinition.size <= 0)
			return LynxID();

		LynxID temp(this->_deviceInfo.deviceID, _structType, _structInstance);

		if (this->indexFromID(temp) >= 0)
			return temp;

		_structures.append();
		_structures[_structures.count() - 1].init(_structDefinition, temp);
		return temp;
	}

	int LynxHandler::scanRequest(char* dataBuffer)
	{
		int index = 0;
		dataBuffer[index] = char(LYNX_INTERNAL_DATAGRAM);
		index++;
		dataBuffer[index] = char(eLynxRequest);
		index++;
		dataBuffer[index] = char(eRqDeviceInfo);
		index++;

		for (int i = 0; i < 20; i++)
		{
			if ((this->_deviceInfo.deviceName[i] == '\0') || (i == 19))
			{
				dataBuffer[index] = '\0';
				index++;
				break;
			}
			dataBuffer[index] = this->_deviceInfo.deviceName[i];
			index++;
		}

		dataBuffer[index] = char(this->_deviceInfo.deviceID);
		index++;

		char tempVersion[4] = LYNX_VERSION;
		for (int i = 0; i < 4; i++)
		{
			dataBuffer[index] = tempVersion[i];
			index++;
		}

		char checksum = 0;
		for (int i = 0; i < index; i++)
		{
			checksum += dataBuffer[i];
		}
		dataBuffer[index] = checksum;
		index++;

		return index;
	}

	int LynxHandler::copyData(const LynxID& source, const LynxID& target, int subIndex)
	{
		if (source.structTypeID != target.structTypeID)
			return -11;

		int sourceIndex = this->indexFromID(source);
		if (sourceIndex < 0)
			return sourceIndex;
		
		int targetIndex = this->indexFromID(target);
		if (targetIndex < 0)
			return targetIndex;
		
		int localSize = _structures.at(targetIndex).getLocalSize(subIndex);
		if (localSize <= 0)
			return localSize;

		const char* sourcePtr = reinterpret_cast<const char*>(_structures.at(sourceIndex).getConstDataPointer(subIndex));
		char* targetPtr = reinterpret_cast<char*>(_structures[targetIndex].getDataPointer(subIndex));

		for (int i = 0; i < localSize; i++)
		{
			targetPtr[i] = sourcePtr[i];
		}

		return localSize;
	}



	int LynxHandler::toBuffer(const LynxID& lynxID, LynxList<char>& dataBuffer, int subIndex) const
	{
		int index = this->indexFromID(lynxID);
		if (index < 0)
			return index;

		return this->_structures.at(index).toBuffer(dataBuffer, subIndex);
	}

	int LynxHandler::fromBuffer(const LynxList<char>& dataBuffer, LynxIpAddress ipAddress)
	{
		if (dataBuffer.at(0) == char(LYNX_INTERNAL_DATAGRAM))
		{
			return handleInternalDatagram(&dataBuffer.at(0), ipAddress);
		}
		else
		{
			return datagramFromBuffer(dataBuffer);
		}

	}

	int LynxHandler::getTranferSize(const LynxID& lynxID, int subIndex) const
	{
		int index = indexFromID(lynxID);
		if (index < 0)
			return index;

		return this->_structures.at(index).getTransferSize(subIndex);
	}

    int LynxHandler::getLocalSize(const LynxID& lynxID, int subIndex) const
    {
        int index = indexFromID(lynxID);
        if (index < 0)
            return index;

        return this->_structures.at(index).getLocalSize(subIndex);
    }

	void * LynxHandler::getDataPointer(const LynxID & lynxID, int subIndex)
	{
		int index = this->indexFromID(lynxID);
		if(index < 0)
			return LYNX_NULL;

		return _structures[index].getDataPointer(subIndex);
	}

	const void * LynxHandler::getConstDataPointer(const LynxID & lynxID, int subIndex) const
	{
		int index = this->indexFromID(lynxID);
		if (index < 0)
			return LYNX_NULL;

		return _structures.at(index).getConstDataPointer(subIndex);
	}

	LynxList<LynxID> LynxHandler::getIDs()
	{
		if (!this->_structures.count())
			return LynxList<LynxID>();

		LynxList<LynxID> list(this->_structures.count());

		getIDs(list);

		return list;
	}

	void LynxHandler::getIDs(LynxList<LynxID>& list)
	{
		list.clear();
        list.reserveAndCopy(this->_structures.count());

        for (int i = 0; i < _structures.count(); i++)
		{
			list.append(this->_structures.at(i).getID());
		}
	}

	int LynxHandler::newScanResponses()
	{
		int temp = 0;

		for (int i = 0; i < _availableDevices.count(); i++)
		{
			if (_availableDevices.at(i).newDevice)
			{
				temp++;
			}
		}

		return temp;
	}

	LynxDeviceInfo LynxHandler::getScanResponse()
	{
		LynxDeviceInfo temp = LynxDeviceInfo();

		for (int i = 0; i < _availableDevices.count(); i++)
		{
			if (_availableDevices.at(i).newDevice)
			{
				temp = _availableDevices.at(i);
				_availableDevices[i].newDevice = false;
				break;
			}
		}

		return temp;
	}

	int LynxHandler::sendScanResponse(char* dataBuffer)
	{
		_newScanRequest = false;

		int index = 0;
		dataBuffer[index] = LYNX_INTERNAL_DATAGRAM;
		index++;
		dataBuffer[index] = eLynxResponse;
		index++;
		dataBuffer[index] = eRqDeviceInfo;
		index++;

		for (int i = 0; i < 20; i++)
		{
			if ((this->_deviceInfo.deviceName[i] == '\0') || (i == 19))
			{
				dataBuffer[index] = '\0';
				index++;
				break;
			}
			dataBuffer[index] = this->_deviceInfo.deviceName[i];
			index++;
		}

		dataBuffer[index] = char(this->_deviceInfo.deviceID);
		index++;

		char tempVersion[4] = LYNX_VERSION;
		for (int i = 0; i < 4; i++)
		{
			dataBuffer[index] = tempVersion[i];
			index++;
		}

		char checksum = 0;
		for (int i = 0; i < index; i++)
		{
			checksum += dataBuffer[i];
		}

		dataBuffer[index] = checksum;
		index++;

		return index;
	}

	bool LynxHandler::isMember(const LynxID& lynxID)
	{
		if (this->indexFromID(lynxID) < 0)
			return false;

		return true;
	}

    int LynxHandler::clear(const LynxID & lynxID)
    {
        int index = this->indexFromID(lynxID);
        if(index < 0)
            return index;

        _structures[index].clear();

        return 0;
    }

	int LynxHandler::indexFromID(const LynxID& lynxID) const
	{
		for (int i = 0; i < _structures.count(); i++)
		{
			if (_structures.at(i).getID() == lynxID)
				return i;
		}

		return -17;
	}

	int LynxHandler::handleInternalDatagram(const char * dataBuffer, LynxIpAddress ipAddress)
	{
		switch (StandardStructIDs(dataBuffer[1]))
		{
		case LynxLib::eLynxRequest:
		{
			return this->handleRequest(dataBuffer, ipAddress);
		}
		case LynxLib::eLynxResponse:
		{
			return this->handleResponse(dataBuffer, ipAddress);
		}
		default:
			return -1;
		}
	}

	int LynxHandler::handleRequest(const char * dataBuffer, LynxIpAddress ipAddress)
	{
		if (dataBuffer[2] == eRqDeviceInfo)
		{
			LynxDeviceInfo tempInfo = receiveScanResponse(dataBuffer, ipAddress);

			int index = checkAvailableDevices(tempInfo);

			if (index >= 0)
			{
				_newScanRequest = true;
				return 0;
			}
		}
		return -1;
	}

	int LynxHandler::handleResponse(const char * dataBuffer, LynxIpAddress ipAddress)
	{
		if (dataBuffer[2] == eRqDeviceInfo)
		{
			LynxDeviceInfo tempInfo = receiveScanResponse(dataBuffer, ipAddress);

			int deviceIndex = checkAvailableDevices(tempInfo);
			return deviceIndex;
		}
		return -1;
	}

	int LynxHandler::checkAvailableDevices(LynxDeviceInfo& lynxDevice)
	{
		lynxDevice.newDevice = true;

		for (int i = 0; i < this->_availableDevices.count(); i++)
		{
			// char* temp = _availableDevices.at(i).deviceName;

			for (int j = 0; j < 20; j++)
			{
				if (_availableDevices.at(i).deviceName[j] != lynxDevice.deviceName[j])
					break;

				if (_availableDevices.at(i).deviceName[j] == '\0') // Device is already in list, update info and return
				{
					_availableDevices[i] = lynxDevice;
					return i;
				}
			}
		}

		this->_availableDevices.append(lynxDevice); // Device is not in list, add it
		return (_availableDevices.count() - 1);
	}

	LynxDeviceInfo LynxHandler::receiveScanResponse(const char * dataBuffer, LynxIpAddress ipAddress)
	{
		LynxDeviceInfo response;
		int index = 3;
		for (int i = 0; i < 20; i++)
		{
			if ((dataBuffer[index] == '\0') || (i == 19))
			{
				response.deviceName[i] = '\0';
				index++;
				break;
			}
			response.deviceName[i] = dataBuffer[index];
			index++;
		}

		response.deviceID = uint8_t(dataBuffer[index]);
		index++;

		for (int i = 0; i < 4; i++)
		{
			response.lynxVersion[i] = dataBuffer[index];
			index++;
		}

		response.ipAddress = ipAddress;

		char checksum = 0;
		for (int i = 0; i < index; i++)
		{
			checksum += dataBuffer[i];
		}

		if (checksum == dataBuffer[index])
		{
			return response;
		}

		return LynxDeviceInfo();

	}

	int LynxHandler::datagramFromBuffer(const LynxList<char>& dataBuffer)
	{
		LynxID tempID;

		tempID.deviceID = uint8_t(dataBuffer.at(0));
		tempID.structTypeID = uint8_t(dataBuffer.at(1));
		tempID.structInstanceID = uint8_t(dataBuffer.at(2));

		int index = this->indexFromID(tempID);
		if (index < 0)
			return index;
			
		return this->_structures[index].fromBuffer(dataBuffer);
	}
}
