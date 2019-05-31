//-------------------------------------------------------------------------------------------
//------------------------------------- Version 1.0.1.1 -------------------------------------
//-------------------------------------------------------------------------------------------

#include "UartHandler.h"

#ifdef ARDUINO
UartHandler::UartHandler()
{
    for (int i = 0; i < DATABUFFER_SIZE; i++)
    {
        _dataBuffer[i] = 0;
    }
}

UartHandler::UartHandler(LynxLib::LynxHandler* lynxHandler)
{
	for (int i = 0; i < DATABUFFER_SIZE; i++)
	{
		_dataBuffer[i] = 0;
	}

	_lynxHandler = lynxHandler;
}

bool UartHandler::open(int port, int baudRate)
{
    if (_open)
        return false;

    _port = port;
    _open = true;

    switch (this->_port)
    {
    case 0:
    {
        Serial.begin(baudRate);
        break;
    }
    case 1:
    {
        Serial1.begin(baudRate);
        break;
    }
#ifdef ARDUINO_MEGA
    case 2:
    {
        Serial2.begin(baudRate);
        break;
    }
    case 3:
    {
        Serial3.begin(baudRate);
        break;
    }
#endif // ARDUINO_MEGA
    default:
        return false;
    }

    return true;
}

void UartHandler::close()
{
    if (!_open)
        return;

    switch (this->_port)
    {
    case 0:
    {
        Serial.end();
        break;
    }
    case 1:
    {
        Serial1.end();
        break;
    }
#ifdef ARDUINO_MEGA
    case 2:
    {
        Serial2.end();
        break;
    }
    case 3:
    {
        Serial3.end();
        break;
    }
#endif // ARDUINO_MEGA
    }

    _open = false;
}

char UartHandler::read()
{
    if (!_open)
        return 0;

    switch (this->_port)
    {
    case 0:
    {
        return Serial.read();
    }
    case 1:
    {
        return Serial1.read();
    }
#ifdef ARDUINO_MEGA
    case 2:
    {
        return Serial2.read();
    }
    case 3:
    {
        return Serial3.read();
    }
#endif // ARDUINO_MEGA
    default:
        break;
    }

    return 0;
}

int UartHandler::read(char* buffer, int size)
{
    if (!_open)
        return -1;

    switch (this->_port)
    {
    case 0:
    {
        return Serial.readBytes(buffer, size);
    }
    case 1:
    {
        return Serial1.readBytes(buffer, size);
    }
#ifdef ARDUNO_MEGA
    case 2:
    {
        return Serial2.readBytes(buffer, size);
    }
    case 3:
    {
        return Serial3.readBytes(buffer, size);
    }
#endif // ARDUNO_MEGA
    default:
        break;
    }

    return -1;
}

int UartHandler::write(const char* buffer, int size)
{
    if (!_open)
        return -1;

    switch (this->_port)
    {
    case 0:
    {
        return Serial.write(reinterpret_cast<const uint8_t*>(buffer), size);
    }
    case 1:
    {
        return Serial1.write(reinterpret_cast<const uint8_t*>(buffer), size);
    }
#ifdef ARDUINO_MEGA
    case 2:
    {
        return Serial2.write(reinterpret_cast<const uint8_t*>(buffer), size);
    }
    case 3:
    {
        return Serial3.write(reinterpret_cast<const uint8_t*>(buffer), size);
    }
#endif // ARDUINO_MEGA
    default:
        break;
    }

    return -1;
}

int UartHandler::bytesAvailable()
{
    switch (this->_port)
    {
    case 0:
    {
        return Serial.available();
    }
    case 1:
    {
        return Serial1.available();
    }
#ifdef ARDUINO_MEGA
    case 2:
    {
        return Serial2.available();
    }
    case 3:
    {
        return Serial3.available();
    }
#endif // ARDUINO_MEGA
    default:
        break;
    }

    return -1;

}

void UartHandler::onNewData(const LynxLib::LynxID& id, int index)
{
	NewData::onNewUartData(id, index);
	_newData = false;
}

#endif //ARDUINO

#ifdef QT_LYNX


InterruptObject::InterruptObject(UartHandler* handler, QObject* parent) : QObject(parent)
{
    _handler = handler;
}

void InterruptObject::update()
{
    if(_handler == nullptr)
        return;

    _handler->update();
}

void InterruptObject::newData(const LynxLib::LynxID& id, int index)
{
    emit onNewData(id, index);
}

UartHandler::UartHandler() :
    _interruptObject(this)
{
    for(int i = 0; i < DATABUFFER_SIZE; i++)
    {
        _dataBuffer[i] = 0;
    }
}

UartHandler::UartHandler(LynxLib::LynxHandler* lynxHandler) :
    _interruptObject(this)
{
    for(int i = 0; i < DATABUFFER_SIZE; i++)
    {
        _dataBuffer[i] = 0;
    }

    QObject::connect(&serialPort, SIGNAL(readyRead()), &_interruptObject, SLOT(update()));

    this->connectToLynx(lynxHandler);
}

//void UartHandler::connecUpdatetInterrupt(QObject *targetObject)
//{
//    QObject::connect(&(this->serialPort), SIGNAL(readyRead()), targetObject, SLOT(updateUart()));
//}

void UartHandler::connectNewDataInterrupt(QObject* targetObject)
{
    QObject::connect(&(this->_interruptObject), SIGNAL(onNewData(const LynxLib::LynxID&, int)), targetObject, SLOT(onNewData(const LynxLib::LynxID&, int)));
}

bool UartHandler::open(int port, int baudRate)
{
    if(_open)
        return false;

    _port = port;

    QString temp = QString::asprintf("COM%d", _port);
    serialPort.setPortName(temp);

    if(!serialPort.setBaudRate(baudRate))
        return false;

    if(!serialPort.open(QIODevice::ReadWrite))
        return false;

    _open = true;
    serialPort.flush();
    return true;
}

bool UartHandler::open(QSerialPortInfo port, int baudRate)
{
    if(_open)
        return false;

    serialPort.setPort(port);

    if(!serialPort.setBaudRate(baudRate))
        return false;
    if(!serialPort.open(QIODevice::ReadWrite))
        return false;

    _open = true;

    return true;
}

void UartHandler::close()
{
    if(_open)
        serialPort.close();

    _open = false;
}

char UartHandler::read()
{
    QByteArray temp = serialPort.read(1);
    return temp.at(0);
}

int UartHandler::read(char* buffer, int size)
{
    return int(serialPort.read(buffer, size));
}

int UartHandler::write(const char* buffer, int size)
{
    // qDebug() << "Bytes to write: " << size;
    return(int(serialPort.write(buffer, size)));
}

int UartHandler::bytesAvailable()
{
    return(int(serialPort.bytesAvailable()));
}

void UartHandler::onNewData(const LynxLib::LynxID& id, int index)
{
    _interruptObject.newData(id, index);
}

#endif //QT_LYNX

#ifdef TI
void UartHandler::onNewData(const LynxLib::LynxID &id,int index)
{

    NewData::onNewUartData(id,index);

}
UartHandler::UartHandler()
{
    // TODO MAGNUS
    // Write here if you need something in the constructor

    // Clear buffer
    for(int i = 0; i < DATABUFFER_SIZE; i++)
    {
        _dataBuffer[i] = 0;
    }
    rxBuffer.init(DATABUFFER_SIZE);
    txBuffer.init(DATABUFFER_SIZE);
}
void UartHandler::init(SCI_Handle _sciHandle,CLK_Handle _clkHandle)
{
    this->sciHandle = _sciHandle;
    this->clkHandle=_clkHandle;
}
bool UartHandler::open(int port, int baudRate)
{
    if(_open)
        return false;

    _port = port;

    // TODO MAGNUS
    // Open serial port "serPort" with baud-rate "baudRate" inclde switch case for baud
    // Return true if success, false if failure
    // enable the SCI-A clock
    CLK_enableSciaClock(clkHandle);
    //
    //    // 1 stop bit,  No loopback
    //    // No parity,8 char bits,
    //    // async mode, idle-line protocol
    SCI_disableParity(sciHandle);
    SCI_setNumStopBits(sciHandle, SCI_NumStopBits_One);
    SCI_setCharLength(sciHandle, SCI_CharLength_8_Bits);

    // enable TX, RX, internal SCICLK,
    // Disable RX ERR, SLEEP, TXWAKE
    SCI_enableTx(sciHandle);
    SCI_enableRx(sciHandle);
    SCI_enableTxInt(sciHandle);
    SCI_enableRxInt(sciHandle);

    //SCI_enableLoopBack(sciHandle);

    // SCI BRR = LSPCLK/(SCI BAUDx8) - 1
    SCI_setBaudRate(sciHandle, SCI_BaudRate_9_6_kBaud);

    SCI_enable(sciHandle);
    //
    //    return;
    //}
    //
    //void scia_fifo_init()
    //{
    SCI_enableFifoEnh(sciHandle);
    SCI_resetTxFifo(sciHandle);
    SCI_clearTxFifoInt(sciHandle);
    SCI_resetChannels(sciHandle);
    SCI_setTxFifoIntLevel(sciHandle, SCI_FifoLevel_2_Words);
    SCI_enableTxFifoInt(sciHandle);

    SCI_resetRxFifo(sciHandle);
    SCI_clearRxFifoInt(sciHandle);
    SCI_setRxFifoIntLevel(sciHandle, SCI_FifoLevel_2_Words);
    SCI_enableRxFifoInt(sciHandle);
    _open=true;
    return true;//success

}
void UartHandler::close()
{
    if(!_open)
        return;

    SCI_disableTx(sciHandle);
    SCI_disableRx(sciHandle);
    SCI_disableTxInt(sciHandle);
    SCI_disableRxInt(sciHandle);
    SCI_disable(sciHandle);
    _open=false;

}
char UartHandler::read()
{
    // TODO MAGNUS
    // Read a single byte from the serial port and return it
    if(!_open)
        return 0;
    return rxBuffer.read();
}

int UartHandler::read(char* buffer, int size)
{
    // TODO MAGNUS
    // Read "size" number of bytes from the serial port and put them in "buffer".
    // Return number of bytes read, or a negative number if error
    if(!_open)
           return -1;
    return rxBuffer.read(buffer,size);
}

int UartHandler::write(const char* buffer, int size)
{
    // TODO MAGNUS
    // Write "size" number of bytes from "buffer" to the serial port.
    // Return number of bytes written, or a negative number if error
    //for (int i = 0; i < size; ++i)
    if(!_open)
           return -1;

        txBuffer.write(buffer, size);

    return true;
}

int UartHandler::bytesAvailable()
{
    // TODO MAGNUS
    // Probe the serial port for incoming bytes.
    // Return number of incoming bytes
    return rxBuffer.count();
}

#endif //TI

bool UartHandler::opened()
{
    return _open;
}

void UartHandler::update(UartHandler* uartHandler)
{
    uartHandler->update();
}

// int iteration = 0;

void UartHandler::update()
{
//    iteration++;
//    qDebug() << "iteration: " << iteration;

//    qDebug() << "state: " << _state;

    if (!_open || (_lynxHandler == nullptr))
    {
//        qDebug() << "lynxHandler: " << _lynxHandler;
//        qDebug() << "open: " << _open;
        return;
    }

    if (this->bytesAvailable() < 0)
    {
        _errorCounter++;
        return;
    }

//    qDebug() << "state: " << _state;

    if(_state == eIdle)
    {
        if (this->bytesAvailable() > 0)
        {
            _receivedBytes = 0;
            _state = eScanning;
        }

     }

//    qDebug() << "state: " << _state;

    if(_state == eScanning)
    {
        int shuffleCount = 0;
        do
        {
            // qDebug() << "while";
            if(_shuffleBytes)
            {
                shuffleCount++;
                _dataBuffer[0] = _dataBuffer[1];
                _dataBuffer[1] = _dataBuffer[2];
                _dataBuffer[2] = read();
                _receivedBytes++;
                _shuffleBytes = false;
            }
            else
            {
                if(this->bytesAvailable() < LYNX_ID_BYTES)
                    return;

                _receivedBytes += this->read(_dataBuffer, LYNX_ID_BYTES);
            }

            _tempID.deviceID = static_cast<uint8_t>(_dataBuffer[0]);
            _tempID.structTypeID = static_cast<uint8_t>(_dataBuffer[1]);
            _tempID.structInstanceID = static_cast<uint8_t>(_dataBuffer[2]);

            // qDebug() << (lynxHandler.isMember(_tempID) ? "true" : "false");

            if(!_lynxHandler->isMember(_tempID))
            {
                _shuffleBytes = true;
                _errorCounter++;
                _state = eIdle;
                return;
            }

            _state = eIndexing;
        }while ((this->bytesAvailable() > 0) && _shuffleBytes);

        // qDebug() << QString::number(shuffleCount);
    }

//    qDebug() << "state: " << _state;

    if(_state == eIndexing)
    {
        if(this->bytesAvailable() < LYNX_INDEXER_BYTES)
            return;

        _receivedBytes += this->read(&(_dataBuffer[LYNX_ID_BYTES]), LYNX_INDEXER_BYTES);

        _lynxIndex = (int(_dataBuffer[LYNX_ID_BYTES]) & int(0xFF)) | ((int(_dataBuffer[LYNX_ID_BYTES + 1]) & int(0xFF)) << 8);

        _readSize = _lynxHandler->getTranferSize(_tempID, _lynxIndex - 1) - LYNX_ID_BYTES - LYNX_INDEXER_BYTES;

        if(_readSize <= 0)
        {
            _errorCounter++;
            _state = eIdle;
            return;
        }

        _state = eReading;
    }

//    qDebug() << "state: " << _state;

    if(_state == eReading)
    {

        if (this->bytesAvailable() >= _readSize)
        {
            _receivedBytes += this->read(&(_dataBuffer[LYNX_ID_BYTES + LYNX_INDEXER_BYTES]), _readSize);
            int bytesTransferred = _lynxHandler->fromBuffer(_dataBuffer);

            _state = eIdle;
            if (bytesTransferred < 1)
            {
                _errorCounter++;
                return;
            }

            _newData = true;
            this->onNewData(_tempID, (_lynxIndex - 1));
        }
    }

//    qDebug() << "state: " << _state;
}

//int UartHandler::send(const LynxLib::LynxID & _lynxID)
//{
//    if(!_open || (_lynxHandler == nullptr))
//        return -1;

//    int size = _lynxHandler->toBuffer(_lynxID, _dataBuffer);

//    return this->write(_dataBuffer, size);
//}

int UartHandler::send(const LynxLib::LynxID & _lynxID, int subIndex)
{
//    qDebug() << "open begin send: " << _open;

    if(!_open || (_lynxHandler == nullptr))
        return -1;

    int size;

    if(subIndex < 0)
        size = _lynxHandler->toBuffer(_lynxID, _dataBuffer, LynxLib::eAllVariables);
    else
        size = _lynxHandler->toBuffer(_lynxID, _dataBuffer, LynxLib::eSingleVariable, subIndex);

    if(size > 0)
    {
        _sentBytes = this->write(_dataBuffer, size);

//        qDebug() << "open end send success: " << _open;
        return  _sentBytes;
    }

//    qDebug() << "open end send failure: " << _open;
    return -1;
}

bool UartHandler::newData()
{
    bool temp = this->_newData;
    _newData = false;
    return temp;
}

char UartHandler::bufferAt(int index)
{
    if(index >= DATABUFFER_SIZE)
    {
        return 0;
    }

    return _dataBuffer[index];
}
