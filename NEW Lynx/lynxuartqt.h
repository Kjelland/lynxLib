#ifndef LYNXUARTQT_H
#define LYNXUARTQT_H

#include "lynxiodevice.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QIODevice>
#include <QtDebug>

using namespace LynxLib;

class LynxUartQt : public LynxIoDevice
{
public:
    LynxUartQt(LynxManager & lynx);
    ~LynxUartQt() {}

    bool open(int port, int baudRate);
    bool open(QSerialPortInfo port, int baudrate);
    void close();

    QSerialPort * portPointer() { return &_port; }

private:
    int read(int count = 1);
    void write();
    int bytesAvailable() const;

    QSerialPort _port;

};

#endif // LYNXUARTQT_H
