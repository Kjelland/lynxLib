//-------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------- Version 1.2.0.3 ----------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

#include"LynxStructure.h"


// #include <exception>
// #include <iostream>

namespace LynxLib
{
	//---------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------ LynxStructure ------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------

	void LynxStructure::init(const StructDefinition* structDefinition, LynxID _lynxID)
	{
		this->lynxID = _lynxID;

		switch (structDefinition->structMode)
		{
		case LynxLib::eStructureMode:
			int tempSize;
			for (int i = 0; i < structDefinition->size; i++)
			{
				tempSize = checkLocalSize(structDefinition->structItems[i].dataType);

				if (tempSize > this->_indexingSize)
				{
					this->_indexingSize = tempSize;
				}

			}
			break;
		case LynxLib::eArrayMode:
			if (structDefinition->size <= 0)
			{
				return;
			}
			this->_indexingSize = checkLocalSize(structDefinition->structItems[0].dataType);
			break;
		default:
			return;
		}

		if (_data)
		{
			delete[] _data;
		}

		_data = new char[structDefinition->size*this->_indexingSize];
		this->_structDefinition = structDefinition;
		// _structName = structDefinition->structName;

		this->clear();

	}

	int LynxStructure::toBuffer(char *dataBuffer, SendMode sendMode, int subindex)
	{
		if (sendMode >= eSendModeEndOfList)
			return -3;

		if ((sendMode == eSingleVariable) && ((subindex < 0) || (subindex >= this->_structDefinition->size)))
		{
			return -4;
		}

		int index = 0;

		//  Write ID
		dataBuffer[index] = char(this->lynxID.deviceID);
		index++;
		dataBuffer[index] = char(this->lynxID.structTypeID);
		index++;
		dataBuffer[index] = char(this->lynxID.structInstanceID);
		index++;

		int tempIndex;
		if (sendMode == eAllVariables)
			tempIndex = 0;
		else if (sendMode == eSingleVariable)
			tempIndex = subindex + 1;
		else 
			return -1;

		dataBuffer[index] = char(tempIndex & 0xFF);
		index++;
		dataBuffer[index] = char((tempIndex >> 8) & 0xFF);
		index++;

		int tempSize;

		// Write data
		if (sendMode == eAllVariables)
		{
			for (int i = 0; i < this->_structDefinition->size; i++)
			{
				tempSize = writeVarToBuffer(dataBuffer, index, i);

				if (tempSize > 0)
					index += tempSize;
				else
					return -1;
			}
		}
		else if(sendMode == eSingleVariable)
		{
			tempSize = writeVarToBuffer(dataBuffer, index, subindex);

			if (tempSize > 0)
				index += tempSize;
			else
				return -1;
				
		}
		else
		{
			return -5;
		}

		// Check data
		char checksum = 0;
		for (int i = 0; i < index; i++)
		{
			checksum += dataBuffer[i];
		}
		dataBuffer[index] = checksum;

		return (index + 1);
	}

	int LynxStructure::fromBuffer(const char *dataBuffer)
	{
		int lynxIndex = (int(dataBuffer[LYNX_ID_BYTES]) & int(0xFF)) | ((int(dataBuffer[LYNX_ID_BYTES + 1]) & int(0xFF)) << 8);

		int index = LYNX_ID_BYTES + LYNX_INDEXER_BYTES;

        int tempSize = 0;


		if (lynxIndex == 0) // Copy all data
		{
			// Check data
			char remoteChecksum = dataBuffer[index + _structDefinition->transferSize];
			char localChecksum = 0;

			for (int i = 0; i < (index + _structDefinition->transferSize); i++)
			{
				localChecksum += dataBuffer[i];
			}

			if (localChecksum != remoteChecksum)
			{
				return -2; // Return error code -2 if checksum is wrong
			}

			// Copy data
			for (int i = 0; i < this->_structDefinition->size; i++)
			{
				tempSize = writeVarFromBuffer(dataBuffer, index, i);
				if (tempSize > 0)
					index += tempSize;
				else
					return tempSize;
			}
		}
		else if (lynxIndex > 0) // Copy specific item
		{
			if (lynxIndex > this->_structDefinition->size)
			{
				return -1;
			}

			// Check data
			int transferSize = checkTransferSize(_structDefinition->structItems[lynxIndex].dataType);
			
			char remoteChecksum = dataBuffer[index + transferSize];
			char localChecksum = 0;

			for (int i = 0; i < (index + transferSize); i++)
			{
				localChecksum += dataBuffer[i];
			}

			if (localChecksum != remoteChecksum)
			{
				return -2; // Return error code -2 if checksum is wrong
			}


			tempSize = writeVarFromBuffer(dataBuffer, index, lynxIndex - 1);
			if (tempSize > 0)
				index += tempSize;
			else
				return tempSize;
		}

        return tempSize;

	}


	void LynxStructure::clear()
	{
		for (int i = 0; i < this->_structDefinition->size*this->_indexingSize; i++)
		{
			_data[i] = 0;
		}
	}

	// Returns the size of the datapackage in bytes (not including identifiers and checksum)
	int LynxStructure::getTransferSize()
	{
		return (this->_structDefinition->transferSize + LYNX_ID_BYTES + LYNX_INDEXER_BYTES + LYNX_CHECKSUM_BYTES);
	}

	bool LynxStructure::dataChanged()
	{
		bool temp = this->_dataChanged;
		this->_dataChanged = false;
		return temp;
	}

	
	int LynxStructure::checkLocalSize(LynxDataType dataType)
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
		case eFloat:
			temp = sizeof(float);
			break;
		case eDouble:
			temp = sizeof(double);
			break;
		case eIQ:
			temp = sizeof(uint32_t);
			break;
		default:
			temp = 0;
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
		case eFloat:
			temp = 4;
			break;
		case eDouble:
			temp = 8;
			break;
		case eIQ:
			temp = 4;
			break;
		default:
			temp = -1;
			break;
		}

		return temp;
	}

	int LynxStructure::writeVarToBuffer(char * dataBuffer, int bufferIndex, int lynxIndex)
	{
		if ((bufferIndex < 0) || (lynxIndex < 0) || (lynxIndex >= this->_structDefinition->size))
			return -1;

		int tempTransferSize;
		int index = bufferIndex;

		switch (this->_structDefinition->structMode)
		{
		case LynxLib::eStructureMode:
			tempTransferSize = checkTransferSize(this->_structDefinition->structItems[lynxIndex].dataType);
			break;
		case LynxLib::eArrayMode:
			tempTransferSize = checkTransferSize(this->_structDefinition->structItems[0].dataType);
			break;
		default:
			return -1;
		}

		switch (tempTransferSize)
		{
		case 1:
            dataBuffer[index] = char(getData<uint8_t>(lynxIndex));
			index++;
			break;
		case 2:
		{
			uint16_t temp = getData<uint16_t>(lynxIndex);
			for (int n = 0; n < 2; n++)
			{
                dataBuffer[index] = char((temp >> (n * 8)) & 0xFF);
				index++;
			}
		}
		break;
		case 4:
		{
			uint32_t temp = getData<uint32_t>(lynxIndex);
			for (int n = 0; n < 4; n++)
			{
                dataBuffer[index] = char((temp >> (n * 8)) & 0xFF);
				index++;
			}
		}
		break;
		case 8:
		{
			uint64_t temp = getData<uint64_t>(lynxIndex);
			for (int n = 0; n < 8; n++)
			{
                dataBuffer[index] = char((temp >> (n * 8)) & 0xFF);
				index++;
			}
		}
		break;
		default:
			return -1;
		}

		return tempTransferSize;
	}

	int LynxStructure::writeVarFromBuffer(const char * dataBuffer, int bufferIndex, int lynxIndex)
	{
		int tempTransferSize;
		int index = bufferIndex;

		// Read data

		switch (this->_structDefinition->structMode)
		{
		case LynxLib::eStructureMode:
			tempTransferSize = checkTransferSize(this->_structDefinition->structItems[lynxIndex].dataType);
			break;
		case LynxLib::eArrayMode:
			tempTransferSize = checkTransferSize(this->_structDefinition->structItems[0].dataType);
			break;
		default:
			return -1;
		}

		switch (tempTransferSize)
		{
		case 1:
			setData<uint8_t>(lynxIndex, uint8_t(dataBuffer[index]));
			index++;
			break;
		case 2:
		{
			uint16_t temp = 0;
			for (int n = 0; n < 2; n++)
			{
				temp |= ((uint16_t(dataBuffer[index]) << (n * 8)) & (uint16_t(0xFF) << (n * 8)));
				index++;
			}
			setData<uint16_t>(lynxIndex, temp);
		}
		break;
		case 4:
		{
			uint32_t temp = 0;
			for (int n = 0; n < 4; n++)
			{
				temp |= ((uint32_t(dataBuffer[index]) << (n * 8)) & (uint32_t(0xFF) << (n * 8)));
				index++;
			}
			setData<uint32_t>(lynxIndex, temp);
		}
		break;
		case 8:
		{
			uint64_t temp = 0;
			for (int n = 0; n < 4; n++)
			{
				temp |= ((uint64_t(dataBuffer[index]) << (n * 8)) & (uint64_t(0xFF) << (n * 8)));
				index++;
			}
			setData<uint64_t>(lynxIndex, temp);
		}
		break;
		default:
			return -1;
		}
		

		return tempTransferSize;
	}



	int LynxStructure::getOffset(int target)
	{
		if ((this->_structDefinition->size == 0) || (target >= this->_structDefinition->size))
		{
			return -1;
		}

		return (target * this->_indexingSize);

	}

	//---------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------- LynxHandler ------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------

	void LynxHandler::init(int nStructs)
	{
		// deviceID = _deviceID;

		if (nStructs > 0)
		{
			if (_structures)
			{
				delete[] _structures;
			}
			_structures = new LynxStructure[nStructs];
			_size = 0;
			_reservedSize = nStructs;
		}
	}

	LynxID LynxHandler::addStructure(uint8_t _structType, uint8_t _structInstance, const StructDefinition* _structDefinition)
	{
		if (_structDefinition->size <= 0)
		{
			return LynxID();
		}

		_size++;

		if (_size > _reservedSize )
		{
			_reservedSize++;

			LynxStructure* tempStructs = new LynxStructure[_reservedSize];
			
			if (this->_structures)
			{
				for (int i = 0; i < _reservedSize - 1; i++)
				{
					// StructDefinition temp = { this->_structures[i].structName(), }
					tempStructs[i].init(_structures[i].structDefinition(), _structures[i].lynxID);
				}
				
				delete[] _structures;
			}

			_structures = tempStructs;
			tempStructs = NULL;
		}

		LynxID tempID = LynxID( this->_deviceInfo.deviceID, _structType, _structInstance );
		_structures[_size - 1].init(_structDefinition, tempID);
		return tempID;
	

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

	int LynxHandler::copyData(LynxID source, LynxID target)
	{
		if (source.structTypeID != target.structTypeID)
			return -2;

		int sourceIndex = indexFromID(source);
		if (sourceIndex < 0)
			return -1;

		int targetIndex = indexFromID(target);
		if (targetIndex < 0)
			return -1;

		int copySize = _structures[targetIndex].getSize()*_structures[targetIndex].getIndexingSize();

        char* sourcePointer = (char*)(_structures[sourceIndex].getDataPointer());
		char* targetPointer = (char*)(_structures[targetIndex].getDataPointer());

		for (int i = 0; i < copySize; i++)
		{
			targetPointer[i] = sourcePointer[i];
		}

		return 0;
	}

	int LynxHandler::toBuffer(LynxID _lynxID, char * dataBuffer, SendMode sendMode, int subIndex)
	{
		int index = this->indexFromID(_lynxID);

		if (index >= 0)
		{
			return this->_structures[index].toBuffer(dataBuffer, sendMode, subIndex);
		}

		return -1;
	}

	int LynxHandler::fromBuffer(const char * dataBuffer, LynxIpAddress ipAddress)
	{
		if (dataBuffer[0] == char(LYNX_INTERNAL_DATAGRAM))
		{
			return handleInternalDatagram(dataBuffer, ipAddress);
		}
		else
		{
			return datagramFromBuffer(dataBuffer);
		}

	}

	bool LynxHandler::dataChanged(LynxID _lynxID)
	{
		int index = indexFromID(_lynxID);

		if (index < 0)
		{
			return false;
		}

		return this->_structures[index].dataChanged();
	}

	int LynxHandler::getTranferSize(LynxID _lynxID)
	{
		int index = indexFromID(_lynxID);

		return this->_structures[index].getTransferSize();
	}

	LynxList<LynxID> LynxHandler::getIDs()
	{
		if (!this->_size)
			return LynxList<LynxID>();

		LynxList<LynxID> list(this->_size);

		getIDs(list);

		return list;
	}

	void LynxHandler::getIDs(LynxList<LynxID>& list)
	{
		list.clear();

		for (int i = 0; i < this->_size; i++)
		{
			list.appendItem(this->_structures[i].lynxID);
		}
	}

	/*
	int LynxHandler::getTransferSize(StandardStructIDs internalDatagram)
	{
		switch (internalDatagram)
		{
		case LynxStructureSpace::eSsInvalidID:
			return -1;
		case LynxStructureSpace::eLynxRequest:
			break;
		case LynxStructureSpace::eLynxResponse:
			break;
		case LynxStructureSpace::eSsEndOfList:
			break;	
		}

		return -1;
	}
	*/

	int LynxHandler::newScanResponses()
	{
		int temp = 0;

		for (int i = 0; i < _availableDevices.getSize(); i++)
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

		for (int i = 0; i < _availableDevices.getSize(); i++)
		{
			if (_availableDevices.at(i).newDevice)
			{
				temp = _availableDevices.at(i);
				_availableDevices.at(i).newDevice = false;
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

    bool LynxHandler::isMember(LynxID _lynxID)
    {
        if(this->indexFromID(_lynxID) < 0)
            return false;

        return true;
    }

	int LynxHandler::indexFromID(LynxID& _lynxID)
	{
		for (int i = 0; i < this->_size; i++)
		{
			if ((this->_structures[i].lynxID.structTypeID == _lynxID.structTypeID)
				&& (this->_structures[i].lynxID.structInstanceID == _lynxID.structInstanceID))
			{
				return i;
			}
		}

		return -1;
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

	// Checks for matching device in list. 
	// If match is found: updates info and returns the index of device.
	// If match is not found: device is added to the list and the index is returned.
	// If failure: returns -1
	int LynxHandler::checkAvailableDevices(LynxDeviceInfo& lynxDevice) 
	{
		lynxDevice.newDevice = true;

		for (int i = 0; i < this->_availableDevices.getSize(); i++)
		{
			char* temp = _availableDevices.at(i).deviceName;

			for (int j = 0; j < 20; j++)
			{
				if (temp[j] != lynxDevice.deviceName[j])
					break;

				if (temp[j] == '\0') // Device is already in list, update info and return
				{	
					_availableDevices.at(i) = lynxDevice;
					return i;
				}
			}
		}

		int index = this->_availableDevices.appendItem(lynxDevice); // Device is not in list, add it
		if (index >= 0)
		{
			return index;
		}

		return -1;
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
				index ++;
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

	int LynxHandler::datagramFromBuffer(const char * dataBuffer)
	{
		LynxID tempID;

        tempID.deviceID = uint8_t(dataBuffer[0]);
        tempID.structTypeID = uint8_t(dataBuffer[1]);
        tempID.structInstanceID = uint8_t(dataBuffer[2]);

		int index = this->indexFromID(tempID);

		if (index >= 0)
		{
			this->_structures[index].lynxID = tempID;

			return this->_structures[index].fromBuffer(dataBuffer);
		}

		return -1;
	}

	StructDefinition::StructDefinition(const char _structName[], const LynxStructMode _structMode, const StructItem * _structItems, int _size)
		: structName(_structName), structMode(_structMode), structItems(_structItems)
	{
		if (_structMode == eArrayMode)
		{
			size = _size;
			transferSize = _size * LynxStructure::checkTransferSize(_structItems[0].dataType);
		}
		else if (_size > 0)
		{
			transferSize = 0;
			size = _size;
			for (int i = 0; i < size; i++)
			{
				transferSize += LynxStructure::checkTransferSize(_structItems[i].dataType);
			}
		}
		else
		{
			transferSize = 0;

			for (int i = 0; i < 256; i++)
			{
				if (_structItems[i].dataType == eEndOfList)
				{
					size = i;
					return;
				}

				transferSize += LynxStructure::checkTransferSize(_structItems[i].dataType);
			}

			transferSize = 0;
			size = 0;
		}
	}

}
