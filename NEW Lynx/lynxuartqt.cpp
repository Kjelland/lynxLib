#include "lynxuartqt.h"

LynxUartQt::LynxUartQt(LynxStructure & structure) : LynxIoDevice(structure)
{

}

bool LynxUartQt::open(int port, int baudRate)
{
    if(_open)
        this->close();

    QString portName = QString::asprintf("COM%i", port);

    _port.setPortName(portName);
    _port.setBaudRate(baudRate);

    _open = _port.open(QSerialPort::ReadWrite);

    return _open;
}

void LynxUartQt::close()
{
    _port.close();
    _open = false;
}

int LynxUartQt::readSerial(int count)
{
    if(!_open)
        return 0;


    QByteArray temp = _port.read(count);

    for (int i = 0; i < temp.count(); i++)
    {
        _readBuffer.append(temp.at(i));
    }

    return temp.count();
}

void LynxUartQt::writeSerial()
{
    if(!_open)
        return;

    _port.write(_writeBuffer.dataPointer(), _writeBuffer.count());

//    const LynxByteArray & temp = _uart.writeBuffer();

    QString tempStr = "";

    for (int i = 0; i < _writeBuffer.count(); i++)
    {
        tempStr += QString::number(_writeBuffer.at(i));
        if(i != (_writeBuffer.count() - 1))
            tempStr += " ";
    }

    qDebug() << tempStr;
}

//void LynxUartQt::writeAll()
//{
//    if(!_open)
//        return;

//    _port.write(_writeBuffer.dataPointer(), _writeBuffer.count());
//}

int LynxUartQt::bytesAvailable() const
{
    if(!_open)
        return 0;

    return static_cast<int>(_port.bytesAvailable());
}
