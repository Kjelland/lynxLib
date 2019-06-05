//-------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------- Version 1.3.1.1 ----------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

#include"LynxStructure.h"


// #include <exception>
// #include <iostream>

namespace LynxLib
{
    //---------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------ LynxStructure ------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------------------------------

    void LynxStructure::init(const StructDefinition* structDefinition, LynxID lynxID)
    {
        this->_lynxID = lynxID;

        if (structDefinition != NULL)
        {
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
                delete[] _data;


            _data = new char[structDefinition->size*this->_indexingSize];
            this->_structDefinition = structDefinition;

            this->clear();
        }

    }

    int LynxStructure::toBuffer(LynxList<char>& dataBuffer, int subIndex) const
    {

        if (subIndex >= this->_structDefinition->size)
            return -4;

        dataBuffer.clear();
        // Check neccessary storage in the buffer to avoid repeating allocation
        if (this->getTransferSize(subIndex) > dataBuffer.reservedSize())
            dataBuffer.reserve(this->getTransferSize(subIndex));


        //  Write ID
        dataBuffer.append(char(this->_lynxID.deviceID));
        dataBuffer.append(char(this->_lynxID.structTypeID));
        dataBuffer.append(char(this->_lynxID.structInstanceID));

        // Shift subIndex by +1 for unsigned transmission. 0 if all elements
        int tempIndex;
        if (subIndex < 0)
            tempIndex = 0;
        else
            tempIndex = subIndex + 1;


        dataBuffer.append(char(tempIndex & 0xFF));
        dataBuffer.append(char((tempIndex >> 8) & 0xFF));

        int tempSize;

        // Write data
        if (subIndex < 0)
        {
            for (int i = 0; i < this->_structDefinition->size; i++)
            {
                tempSize = writeVarToBuffer(dataBuffer, i);

                if (tempSize <= 0)
                    return -1;
            }
        }
        else
        {
            tempSize = writeVarToBuffer(dataBuffer, subIndex);

            if (tempSize <= 0)
                return -1;

        }

        // Check data
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
        int lynxIndex = (int(dataBuffer.at(LYNX_ID_BYTES)) & int(0xFF)) | ((int(dataBuffer.at(LYNX_ID_BYTES + 1)) & int(0xFF)) << 8);

        int index = LYNX_ID_BYTES + LYNX_INDEXER_BYTES;

        int tempSize = 0;

        // Check data
        char remoteChecksum = dataBuffer.at(dataBuffer.count() - 1); //dataBuffer[index + _structDefinition->transferSize];
        char localChecksum = 0;

        for (int i = 0; i < (dataBuffer.count() - 1); i++)
        {
            localChecksum += dataBuffer.at(i);
        }

        if ((localChecksum & 0xff) != (remoteChecksum & 0xff)) // & with 0xff to ensure 8 bit overflow, even on higher storage bits platforms
            return -5; // Return error code -5 if checksum is wrong

        if (lynxIndex == 0) // Copy all data
        {
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
            lynxIndex--;

            if (lynxIndex > this->_structDefinition->size)
                return -1;

            tempSize = writeVarFromBuffer(dataBuffer, index, lynxIndex);
            if (tempSize > 0)
                index += tempSize;
            else
                return tempSize;
        }

        return index;

    }

    void LynxStructure::clear()
    {
        for (int i = 0; i < this->_structDefinition->size*this->_indexingSize; i++)
        {
            _data[i] = 0;
        }
    }

    int LynxStructure::getTransferSize(int subIndex) const
    {
        if(subIndex < 0)
            return (this->_structDefinition->transferSize + LYNX_ID_BYTES + LYNX_INDEXER_BYTES + LYNX_CHECKSUM_BYTES);
        else
        {
            int temp = this->checkTransferSize(_structDefinition->structItems[subIndex].dataType);
            if(temp < 1)
                return temp;

            temp += LYNX_ID_BYTES + LYNX_INDEXER_BYTES + LYNX_CHECKSUM_BYTES;
            return temp;
        }
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
            temp = -21;
            break;
        }

        return temp;
    }

    int LynxStructure::writeVarToBuffer(LynxList<char>& dataBuffer, int subIndex) const
    {
        if ((subIndex < 0) || (subIndex >= this->_structDefinition->size))
            return -1;

        int tempTransferSize;
        // int index = bufferIndex;

        switch (this->_structDefinition->structMode)
        {
        case LynxLib::eStructureMode:
            tempTransferSize = LynxStructure::checkTransferSize(this->_structDefinition->structItems[subIndex].dataType);
            break;
        case LynxLib::eArrayMode:
            tempTransferSize = LynxStructure::checkTransferSize(this->_structDefinition->structItems[0].dataType);
            break;
        default:
            return -1;
        }

        switch (tempTransferSize)
        {
        case 1:
            dataBuffer.append(char(getData<uint8_t>(subIndex)));
            break;
        case 2:
        {
            uint16_t temp = getData<uint16_t>(subIndex);
            for (int n = 0; n < 2; n++)
            {
                dataBuffer.append(char((temp >> (n * 8)) & 0xFF));
            }
        }
        break;
        case 4:
        {
            uint32_t temp = getData<uint32_t>(subIndex);
            for (int n = 0; n < 4; n++)
            {
                dataBuffer.append(char((temp >> (n * 8)) & 0xFF));
            }
        }
        break;
        case 8:
        {
            uint64_t temp = getData<uint64_t>(subIndex);
            for (int n = 0; n < 8; n++)
            {
                dataBuffer.append(char((temp >> (n * 8)) & 0xFF));
            }
        }
        break;
        default:
            return -1;
        }

        return tempTransferSize;
    }

    int LynxStructure::writeVarFromBuffer(const LynxList<char>& dataBuffer, int bufferIndex, int subIndex)
    {
        int tempTransferSize;

        // Read data

        switch (this->_structDefinition->structMode)
        {
        case LynxLib::eStructureMode:
            tempTransferSize = LynxStructure::checkTransferSize(this->_structDefinition->structItems[subIndex].dataType);
            break;
        case LynxLib::eArrayMode:
            tempTransferSize = LynxStructure::checkTransferSize(this->_structDefinition->structItems[0].dataType);
            break;
        default:
            return -1;
        }

        switch (tempTransferSize)
        {
        case 1:
            setData<uint8_t>(subIndex, uint8_t(dataBuffer.at(bufferIndex)));
            break;
        case 2:
        {
            uint16_t temp = 0;
            for (int n = 0; n < 2; n++)
            {
                temp |= ((uint16_t(dataBuffer.at(bufferIndex + n)) << (n * 8)) & (uint16_t(0xFF) << (n * 8)));
            }
            setData<uint16_t>(subIndex, temp);
        }
        break;
        case 4:
        {
            uint32_t temp = 0;
            for (int n = 0; n < 4; n++)
            {
                temp |= ((uint32_t(dataBuffer.at(bufferIndex + n)) << (n * 8)) & (uint32_t(0xFF) << (n * 8)));
            }
            setData<uint32_t>(subIndex, temp);
        }
        break;
        case 8:
        {
            uint64_t temp = 0;
            for (int n = 0; n < 8; n++)
            {
                temp |= ((uint64_t(dataBuffer.at(bufferIndex + n)) << (n * 8)) & (uint64_t(0xFF) << (n * 8)));
            }
            setData<uint64_t>(subIndex, temp);
        }
        break;
        default:
            return -1;
        }


        return tempTransferSize;
    }

    int LynxStructure::getOffset(int target) const
    {
        if ((this->_structDefinition->size == 0) || (target >= this->_structDefinition->size))
            return -1;

        return (target * this->_indexingSize);

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

    LynxID LynxHandler::addStructure(uint8_t _structType, uint8_t _structInstance, const StructDefinition* _structDefinition)
    {
        if (_structDefinition->size <= 0)
        {
            return LynxID();
        }

        LynxID temp(this->_deviceInfo.deviceID, _structType, _structInstance);

        if(this->indexFromID(temp) >= 0)
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

    int LynxHandler::copyData(LynxID source, LynxID target, int index)
    {
        if (source.structTypeID != target.structTypeID)
            return -2;

        int sourceIndex = indexFromID(source);
        if (sourceIndex < 0)
            return -1;

        int targetIndex = indexFromID(target);
        if (targetIndex < 0)
            return -1;

        if (index < 0)
        {
            int copySize = _structures.at(targetIndex).getSize()*_structures.at(targetIndex).getIndexingSize();

            char* sourcePointer = static_cast<char*>(_structures[sourceIndex].getDataPointer());
            char* targetPointer = static_cast<char*>(_structures[targetIndex].getDataPointer());

            for (int i = 0; i < copySize; i++)
            {
                targetPointer[i] = sourcePointer[i];
            }
        }
        else
        {
            switch (_structures.at(sourceIndex).getStructDefinition()->structItems[index].dataType)
            {
            case LynxLib::eInt8:
                _structures[targetIndex].setData(index, _structures.at(sourceIndex).getData<int8_t>(index));
                break;
            case LynxLib::eUint8:
                _structures[targetIndex].setData(index, _structures.at(sourceIndex).getData<uint8_t>(index));
                break;
            case LynxLib::eInt16:
                _structures[targetIndex].setData(index, _structures.at(sourceIndex).getData<int16_t>(index));
                break;
            case LynxLib::eUint16:
                _structures[targetIndex].setData(index, _structures.at(sourceIndex).getData<uint16_t>(index));
                break;
            case LynxLib::eInt32:
                _structures[targetIndex].setData(index, _structures.at(sourceIndex).getData<int32_t>(index));
                break;
            case LynxLib::eUint32:
                _structures[targetIndex].setData(index, _structures.at(sourceIndex).getData<uint32_t>(index));
                break;
            case LynxLib::eInt64:
                _structures[targetIndex].setData(index, _structures.at(sourceIndex).getData<int64_t>(index));
                break;
            case LynxLib::eUint64:
                _structures[targetIndex].setData(index, _structures.at(sourceIndex).getData<uint64_t>(index));
                break;
            case LynxLib::eFloat:
                _structures[targetIndex].setData(index, _structures.at(sourceIndex).getData<float>(index));
                break;
            case LynxLib::eDouble:
                _structures[targetIndex].setData(index, _structures.at(sourceIndex).getData<double>(index));
                break;
            default:
                return -1;
            }
        }

        return 0;
    }

//	int LynxHandler::toBuffer(LynxID _lynxID, char * dataBuffer, SendMode sendMode, int subIndex)
//	{
//		int index = this->indexFromID(_lynxID);

//		if (index >= 0)
//		{
//			return this->_structures[index].toBuffer(dataBuffer, sendMode, subIndex);
//		}

//		return -1;
//	}

    int LynxHandler::toBuffer(LynxID _lynxID, LynxList<char>& dataBuffer, int subIndex) const
    {
        int index = this->indexFromID(_lynxID);

        return this->_structures.at(index).toBuffer(dataBuffer, subIndex);
    }

//	int LynxHandler::fromBuffer(const char * dataBuffer, LynxIpAddress ipAddress)
//	{
//		if (dataBuffer[0] == char(LYNX_INTERNAL_DATAGRAM))
//		{
//			return handleInternalDatagram(dataBuffer, ipAddress);
//		}
//		else
//		{
//			return datagramFromBuffer(dataBuffer);
//		}

//	}

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

//	bool LynxHandler::dataChanged(LynxID _lynxID)
//	{
//		int index = indexFromID(_lynxID);

//		if (index < 0)
//		{
//			return false;
//		}

//		return this->_structures[index].dataChanged();
//	}

    int LynxHandler::getTranferSize(LynxID _lynxID, int subIndex) const
    {
        int index = indexFromID(_lynxID);
        if(index < 0)
            return -10;

        return this->_structures.at(index).getTransferSize(subIndex);
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

        for (int i = 0; i < list.count(); i++)
        {
            list.append(this->_structures.at(i).getID());
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

    bool LynxHandler::isMember(LynxID _lynxID)
    {
        if(this->indexFromID(_lynxID) < 0)
            return false;

        return true;
    }

    int LynxHandler::indexFromID(LynxID& _lynxID) const
    {
        for (int i = 0; i < _structures.count(); i++)
        {
            if(_structures.at(i).getID() == _lynxID)
                return i;
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

//	int LynxHandler::datagramFromBuffer(const char * dataBuffer)
//	{
//		LynxID tempID;

//        tempID.deviceID = uint8_t(dataBuffer[0]);
//        tempID.structTypeID = uint8_t(dataBuffer[1]);
//        tempID.structInstanceID = uint8_t(dataBuffer[2]);

//		int index = this->indexFromID(tempID);

//		if (index >= 0)
//		{
//			this->_structures[index].lynxID = tempID;

//			return this->_structures[index].fromBuffer(dataBuffer);
//		}

//		return -1;
//	}

    int LynxHandler::datagramFromBuffer(const LynxList<char>& dataBuffer)
    {
        LynxID tempID;

        tempID.deviceID = uint8_t(dataBuffer.at(0));
        tempID.structTypeID = uint8_t(dataBuffer.at(1));
        tempID.structInstanceID = uint8_t(dataBuffer.at(2));

        int index = this->indexFromID(tempID);

        if (index >= 0)
        {
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
