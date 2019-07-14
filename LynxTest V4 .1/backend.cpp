#include "backend.h"

PortList::PortList(QObject * parent) : QObject (parent)
{

}

BackEnd::BackEnd(QObject *parent) :
    QObject(parent),
    _lynxHandler(DEVICE_ID, DEVICE_NAME),
    _uartHandler(&_lynxHandler)
{
    _sendID = _lynxHandler.addStructure(TEST_STRUCT, 1, testDefinition);
    _receiveID = _lynxHandler.addStructure(TEST_STRUCT, 2, testDefinition);
    _modeID = _lynxHandler.addStructure(ARDUINOTEST_STRUCT, 1, arduinoTestDefinition);

    _sendData.connect(&_lynxHandler, _sendID);
    _receiveData.connect(&_lynxHandler, _receiveID);
    _modeStruct.connect(&_lynxHandler, _modeID);

    _uartHandler.connectNewDataInterrupt(this);

    connect(&(this->_portListUpdateTimer), SIGNAL(timeout()), this, SLOT(portListUpdate()));
    _portListUpdateTimer.start(1000);

    set_errorCounter(0);

    _portConnected = false;
    _int8_returnVar = 0;
    _uint8_returnVar = 0;
    _int16_returnVar = 0;
    _uint16_returnVar = 0;
    _int32_returnVar = 0;
    _uint32_returnVar = 0;
    _int64_returnVar = 0;
    _uint64_returnVar = 0;
    _float_returnVar = 0;
    _double_returnVar = 0;

}

void BackEnd::varUpdated(E_TestContents_QML index)
{
    if(_sendMode == E_All)
        return;

    if(_uartHandler.opened())
    {
        _uartHandler.send(_sendID, index);
        this->dataSent(_sendID, index);
    }
}


void BackEnd::connectToPort(int index)
{
    if(index < 0)
    {
        if(_uartHandler.opened())
            _uartHandler.close();

        set_portConnected(false);
        return;
    }

    set_portConnected(_uartHandler.open(_portInfoList.at(index), _baudRate));
}

// int prevErrorCount = 0;

void BackEnd::portListUpdate()
{
    set_errorCounter(_errorCounter + _uartHandler.errorCount());  // _uartHandler.errorCount());

    if(_uartHandler.errorCount() > 0)
    {
        LynxList<int> tmpError = _uartHandler.getErrorList();

        // for (int i = 0; i < tmpError.count(); i++)
        // {
        //     qDebug() << "Error: " << tmpError.at(i) << "\n";
        // }
    }

    _portInfoList = QSerialPortInfo::availablePorts();

    bool changed = false;

    if(_portInfoList.count() != _portList.count())
        changed = true;

    QList<QString> tempList;
    for(int i = 0; i < _portInfoList.count(); i++)
    {
        tempList.append(_portInfoList.at(i).portName() + " - " + _portInfoList.at(i).description());
    }

    if(!changed)
    {
        for (int i = 0; i < _portList.count(); i++)
        {
            if(tempList.at(i) != _portList._list.at(i))
            {
                changed = true;
                break;
            }
        }
    }

    if(changed)
    {
        _portList._list = tempList;
        emit portListUpdated(&_portList);
    }
}

void BackEnd::onNewData(const LynxID& id, int index)
{
//    qDebug() << "---------------------";
//    qDebug() << "Device ID: " << id.deviceID;
//    qDebug() << "Type ID: " << id.structTypeID;
//    qDebug() << "Instance ID: " << id.structInstanceID;
//    qDebug() << "Index: " << index;

    if((id == _receiveID) || (id == _sendID))
    {
//        qDebug() << "---------------------";
//        qDebug() << "Received " << _uartHandler.bytesRead() << " bytes.";

        switch(E_TestContents(index))
        {
        case test_int8:
            // emit int8_returnVarChanged();
            set_int8_returnVar(_lynxHandler.getData<int8_t>(id, index));
//            qDebug() << "---------------------";
//            qDebug() << _lynxHandler.getData<int8_t>(id, index);
            break;
        case test_uint8:
            set_uint8_returnVar(_lynxHandler.getData<uint8_t>(id, index));
//            qDebug() << "---------------------";
//            qDebug() << _lynxHandler.getData<uint8_t>(id, index);
            break;
        case test_int16:
            set_int16_returnVar(_lynxHandler.getData<int16_t>(id, index));
//            qDebug() << "---------------------";
//            qDebug() << _lynxHandler.getData<int16_t>(id, index);
            break;
        case test_uint16:
            set_uint16_returnVar(_lynxHandler.getData<uint16_t>(id, index));
//            qDebug() << "---------------------";
//            qDebug() << _lynxHandler.getData<uint16_t>(id, index);
            break;
        case test_int32:
            set_int32_returnVar(_lynxHandler.getData<int32_t>(id, index));
//            qDebug() << "---------------------";
//            qDebug() << _lynxHandler.getData<int32_t>(id, index);
            break;
        case test_uint32:
            set_uint32_returnVar(_lynxHandler.getData<uint32_t>(id, index));
//            qDebug() << "---------------------";
//            qDebug() << _lynxHandler.getData<uint32_t>(id, index);
            break;
        case test_int64:
            set_int64_returnVar(_lynxHandler.getData<int64_t>(id, index));
//            qDebug() << "---------------------";
//            qDebug() << _lynxHandler.getData<int64_t>(id, index);
            break;
        case test_uint64:
            set_uint64_returnVar(_lynxHandler.getData<uint64_t>(id, index));
//            qDebug() << "---------------------";
//            qDebug() << _lynxHandler.getData<uint64_t>(id, index);
            break;
        case test_float:
            set_float_returnVar(_lynxHandler.getData<float>(id, index));
//            qDebug() << "---------------------";
//            qDebug() << _lynxHandler.getData<float>(id, index);
            break;
        case test_double:
            set_double_returnVar(_lynxHandler.getData<double>(id, index));
//            qDebug() << "---------------------";
//            qDebug() << _lynxHandler.getData<double>(id, index);
            // qDebug() << "received: " << _lynxHandler.getData<double>(id, test_double);
            break;
        default:
        {
            if(index == -1)
            {
                // qDebug() << "received all vars";
                set_int8_returnVar(_lynxHandler.getData<int8_t>(id, test_int8));
                set_uint8_returnVar(_lynxHandler.getData<uint8_t>(id, test_uint8));
                set_int16_returnVar(_lynxHandler.getData<int16_t>(id, test_int16));
                set_uint16_returnVar(_lynxHandler.getData<uint16_t>(id, test_uint16));
                set_int32_returnVar(_lynxHandler.getData<int32_t>(id, test_int32));
                set_uint32_returnVar(_lynxHandler.getData<uint32_t>(id, test_uint32));
                set_int64_returnVar(_lynxHandler.getData<int64_t>(id, test_int64));
                set_uint64_returnVar(_lynxHandler.getData<uint64_t>(id, test_uint64));
                set_float_returnVar(_lynxHandler.getData<float>(id, test_float));
                set_double_returnVar(_lynxHandler.getData<double>(id, test_double));
            }
        }
            break;
        }

    }
    else if (id.deviceID == static_cast<uint8_t>(LYNX_INTERNAL_DATAGRAM))
    {
        if(id.structTypeID == LynxLib::eLynxString)
        {
//            qDebug() << "---------------------";
//            qDebug() << _lynxHandler.getReceivedString().toCstr();

            QString tmp(_lynxHandler.getReceivedString().toCstr());
            emit receivedString(tmp);
        }
    }

//    qDebug() << "---------------------";

//    qDebug() << QString::number(_uartHandler.receiveBufferCount()) << " bytes in receive buffer";

//    qDebug() << "---------------------";

    QString temp;
    for (int i = 0; i < _uartHandler.receiveBufferCount(); i++)
    {
        temp += QString::number(int(_uartHandler.receiveBufferAt(i))) + " ";
    }
//    qDebug() << temp;

//    qDebug() << "---------------------";
}

void BackEnd::sendAll()
{
    if(_uartHandler.opened() && (_sendMode == BackEnd::E_All))
    {
        _uartHandler.send(_sendID);
        this->dataSent(_sendID, -1);
    }
}

void BackEnd::changeMode(int desiredMode)
{
    if(!_uartHandler.opened())
        return;

    _modeStruct.var_mode = static_cast<uint8_t>(desiredMode);
    _uartHandler.send(_modeID, mode);
    this->dataSent(_modeID, mode);
}

void BackEnd::dataSent(const LynxID& id, int index)
{
//    qDebug() << "---------------------";
//    qDebug() << "Device ID: " << id.deviceID;
//    qDebug() << "Type ID: " << id.structTypeID;
//    qDebug() << "Instance ID: " << id.structInstanceID;
//    qDebug() << "Index: " << index;
//    qDebug() << "---------------------";
//    qDebug() << "Sent " << _uartHandler.bytesWritten() << " bytes.";
//    qDebug() << "---------------------";
//    QString temp;
//    for (int i = 0; i < _uartHandler.sendBufferCount(); i++)
//    {
//        temp += QString::number(int(_uartHandler.sendBufferAt(i))) + " ";
//    }
//    qDebug() << temp;
//    qDebug() << "---------------------";
}

void BackEnd::sendString(const QString& str)
{
    if(!_uartHandler.opened())
        return;

    _uartHandler.sendString(str.toLatin1().data(), str.count());
}

