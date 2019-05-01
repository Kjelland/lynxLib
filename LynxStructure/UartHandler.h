//-------------------------------------------------------------------------------------------
//------------------------------------- Version 0.1.0.2 -------------------------------------
//-------------------------------------------------------------------------------------------

#pragma once
// #define QT_LYNX

#ifdef ARDUINO
#include <arduino.h>
#endif //ARDUINO

#ifdef QT_LYNX
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#endif //QT_LYNX

#ifdef TI
// TODO MAGNUS
// Write here if you need includes
#include "DSP28x_Project.h"
#include   "f2802x_common/include/sci_CPP.h"
#include   "f2802x_common/include/clk_CPP.h"
#endif // TI


#include "LynxStructure.h"
// #include "RingBuffer.h"

#define DATABUFFER_SIZE 64
#define REMOTE_ID 2

// #define LYNX_DEBUG

enum E_State
{
    eIdle = 0,
    eScanning,
    eReading,
};

class UartHandler
{
public:
    UartHandler();

    // Opens the serial connection. Returns true if it was opened successfully.
    bool open(int port, int baudRate);

    // Links between received data and lynx. Run this as often as possible
    void update(LynxStructureSpace::LynxHandler& lynxHandler, const LynxStructureSpace::LynxID& lynxID);

    // Sends content of the lynx id to the serial port
    int send(LynxStructureSpace::LynxHandler& lynxHandler, const LynxStructureSpace::LynxID& lynxID);

    // Returns true if new data has been received and added to lynx
    bool newData();

    // returns one character from the buffer at "index"
    char bufferAt(int index);

    // Returns number of communication errors since strtup
    int errorCount() { return _errorCounter; }


private:
    // Reads a single character from serial and returns it
    char read();

    // Reads "size" bytes from the serial port, and puts it in buffer
    int read(char* buffer, int size);

    // Writes "size" number of bytes from buffer to the serial port
    int write(const char* buffer, int size);

    // Returns number of bytes on port
    int bytesAvailable();

    E_State _state = eIdle;
    bool _newData = false;
    int _errorCounter = 0;
    int _port;
    int _bytesIn = 0;
    char _dataBuffer[DATABUFFER_SIZE];
    int _index = 0;

#ifdef QT_LYNX
private:
    QSerialPort serialPort;
#endif //QT_LYNX

#ifdef TI
public:
    RingBuffer <char>txBuffer;
    RingBuffer <char>rxBuffer;
    UartHandler(SCI_Handle _sciHandle,CLK_Handle _clkHandle);
private:
    SCI_Handle sciHandle;
    CLK_Handle clkHandle;
    // int writeBytes(const char* buffer, int size,SCI_Handle sciHandle);
#endif //TI
};
