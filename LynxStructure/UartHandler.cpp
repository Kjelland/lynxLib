//-------------------------------------------------------------------------------------------
//------------------------------------- Version 0.1.0.2 -------------------------------------
//-------------------------------------------------------------------------------------------

#include "UartHandler.h"

#ifdef ARDUINO
UartHandler::UartHandler()
{
    for (int i = 0; i < DATABUFFER_SIZE; i++)
    {
        dataBuffer[i] = 0;
    }
}

bool UartHandler::open(int port, int baudRate)
{
    serPort = port;

    switch (this->serPort)
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
    default:
        return false;
    }

    return true;
}

char UartHandler::readByte()
{
    switch (this->serPort)
    {
    case 0:
    {
        return Serial.read();
    }
    case 1:
    {
        return Serial1.read();
    }
    case 2:
    {
        return Serial2.read();
    }
    case 3:
    {
        return Serial3.read();
    }
    default:
        break;
    }

    return 0;
}

int UartHandler::readBytes(char* buffer, int size)
{
    switch (this->serPort)
    {
    case 0:
    {
        return Serial.readBytes(buffer, size);
    }
    case 1:
    {
        return Serial1.readBytes(buffer, size);
    }
    case 2:
    {
        return Serial2.readBytes(buffer, size);
    }
    case 3:
    {
        return Serial3.readBytes(buffer, size);
    }
    default:
        break;
    }

    return -1;
}

int UartHandler::writeBytes(const char* buffer, int size)
{
    switch (this->serPort)
    {
    case 0:
    {
        return Serial.write(buffer, size);
    }
    case 1:
    {
        return Serial1.write(buffer, size);
    }
    case 2:
    {
        return Serial2.write(buffer, size);
    }
    case 3:
    {
        return Serial3.write(buffer, size);
    }
    default:
        break;
    }

    return -1;
}

int UartHandler::bytesAvailable()
{
    switch (this->serPort)
    {
    case 0:
    {
        return Serial.available();
    }
    case 1:
    {
        return Serial1.available();
    }
    case 2:
    {
        return Serial2.available();
    }
    case 3:
    {
        return Serial3.available();
    }
    default:
        break;
    }

    return -1;

}
#endif //ARDUINO

#ifdef QT_LYNX

UartHandler::UartHandler()
{
    for(int i = 0; i < DATABUFFER_SIZE; i++)
    {
        _dataBuffer[i] = 0;
    }
}

bool UartHandler::open(int port, int baudRate)
{
    _port = port;

    QString temp = QString::asprintf("COM%d", _port);
    serialPort.setPortName(temp);

    if(!serialPort.setBaudRate(baudRate))
        return false;

    if(!serialPort.open(QIODevice::ReadWrite))
        return false;

    return true;
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
    return(int(serialPort.write(buffer, size)));
}

int UartHandler::bytesAvailable()
{
    return(int(serialPort.bytesAvailable()));
}

#endif //QT_LYNX

#ifdef TI

UartHandler::UartHandler(SCI_Handle _sciHandle,CLK_Handle _clkHandle)
{
    // TODO MAGNUS
    // Write here if you need something in the constructor
    this->sciHandle = _sciHandle;
    this->clkHandle=_clkHandle;
    // Clear buffer
    for(int i = 0; i < DATABUFFER_SIZE; i++)
    {
        dataBuffer[i] = 0;
    }
    rxBuffer.init(100);
    txBuffer.init(100);
}

bool UartHandler::open(int port, int baudRate)
{
    serPort = port;

    // TODO MAGNUS
    // Open serial port "serPort" with baud-rate "baudRate" inclde switch case for baud
    // Return true if success, false if failure
    // enable the SCI-A clock
        CLK_enableSciaClock(clkHandle);

        // disable parity
        SCI_disableParity(sciHandle);

        // 1 stop bit
        SCI_setNumStopBits(sciHandle, SCI_NumStopBits_One);

        // 8 data bits
        SCI_setCharLength(sciHandle, SCI_CharLength_8_Bits);

        // 9600 baud rate
        SCI_setBaudRate(sciHandle, SCI_BaudRate_9_6_kBaud);

        // enable free run - continue SCI operation regardless of emulation suspend
        SCI_setPriority(sciHandle, SCI_Priority_FreeRun);

        // enable TX and RX
        SCI_enableTx(sciHandle);
        SCI_enableRx(sciHandle);

        SCI_enableTxInt(sciHandle);
        SCI_enableRxInt(sciHandle);

        // enable the SCI interface
        SCI_enable(sciHandle);

        // init FIFO
        SCI_enableFifoEnh(sciHandle);
        SCI_resetTxFifo(sciHandle);
        SCI_clearTxFifoInt(sciHandle);
        SCI_resetChannels(sciHandle);
        SCI_setTxFifoIntLevel(sciHandle, SCI_FifoLevel_2_Words);
        SCI_enableTxFifoInt(sciHandle);


        SCI_resetRxFifo(sciHandle);
        SCI_clearRxFifoInt(sciHandle);
        SCI_setRxFifoIntLevel(sciHandle, SCI_FifoLevel_4_Words);
        SCI_enableRxFifoInt(sciHandle);

        return true;//success

}

char UartHandler::readByte()
{
    // TODO MAGNUS
    // Read a single byte from the serial port and return it
    return rxBuffer.read();
}

int UartHandler::readBytes(char* buffer, int size)
{
    // TODO MAGNUS
    // Read "size" number of bytes from the serial port and put them in "buffer".
    // Return number of bytes read, or a negative number if error
    return rxBuffer.read(buffer,size);
}

int UartHandler::writeBytes(const char* buffer, int size)
{
    // TODO MAGNUS
    // Write "size" number of bytes from "buffer" to the serial port.
    // Return number of bytes written, or a negative number if error
    //for (int i = 0; i < size; ++i)
    {
        txBuffer.write(buffer, size);
    }
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

void UartHandler::update(LynxStructureSpace::LynxHandler& lynxHandler, const LynxStructureSpace::LynxID& _lynxID)
{
    _bytesIn = bytesAvailable();

    if(_bytesIn < 0)
    {
        _errorCounter++;
        return;
    }

    switch (_state)
    {
    case eIdle:
    {
        if (_bytesIn > 0)
        {
            _index = 0;
            _state = eScanning;
        }

        break;
    }
    case eScanning:
    {
        if (_bytesIn)
        {
            switch (_index)
            {
            case 0:
            {
                _dataBuffer[_index] = this->read();

                if (_dataBuffer[_index] == REMOTE_ID)
                    _index++;
                else
                {
                    _state = eIdle;
                    _errorCounter++;
                }
                break;
            }
            case 1:
            {
                _dataBuffer[_index] = this->read();

                if (_dataBuffer[_index] == _lynxID.structTypeID)
                    _index++;
                else
                {
                    _state = eIdle;
                    _errorCounter++;
                }
                break;
            }
            case 2:
            {
                _dataBuffer[_index] = this->read();

                if (true)//dataBuffer[index] == _lynxID.structInstanceID)
                {
                    _index++;
                    _state = eReading;
                }
                else
                {
                    _state = eIdle;
                    _errorCounter++;
                }
                break;
            }
            default:
            {
                _state = eIdle;
                _errorCounter++;

                break;
            }
            }
        }

        break;
    }
    case eReading:
    {
        if (_bytesIn >= (lynxHandler.getTranferSize(_lynxID) - _index))
        {
            this->read(&(_dataBuffer[_index]), (lynxHandler.getTranferSize(_lynxID) - _index));
            int bytesReceived = lynxHandler.fromBuffer(_dataBuffer);

            if(bytesReceived < 0)
                _errorCounter++;

            _state = eIdle;
            _newData = true;
        }

        break;
    }
    default:
    {
        _state = eIdle;
        _errorCounter++;
        break;
    }
    }
}



int UartHandler::send(LynxStructureSpace::LynxHandler & lynxHandler, const LynxStructureSpace::LynxID & _lynxID)
{
    int size = lynxHandler.toBuffer(_lynxID, _dataBuffer);

    return this->write(_dataBuffer, size);
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
