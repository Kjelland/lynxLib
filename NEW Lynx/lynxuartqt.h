#ifndef LYNXUARTQT_H
#define LYNXUARTQT_H

#include "lynxuart.h"
#include <QtSerialPort/QSerialPort>
#include <QIODevice>
#include <QtDebug>

using namespace LynxLib;

class LynxUartQt : public LynxUartBaseClass
{
public:
    LynxUartQt(LynxStructure &  structure);

    bool open(int port, int baudRate);
    void close();

    QSerialPort * portPointer() { return &_port; }

private:
    int readSerial(int count = 1);
    void writeSerial();
    // void writeAll();
    int bytesAvailable() const;

    QSerialPort _port;

};

#endif // LYNXUARTQT_H
