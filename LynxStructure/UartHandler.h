//-------------------------------------------------------------------------------------------
//------------------------------------- Version 1.0.0.1 -------------------------------------
//-------------------------------------------------------------------------------------------

#pragma once
//#define QT_LYNX

#ifdef ARDUINO
#undef QT_LYNX
#include <arduino.h>
#define ARDUINO_MEGA
#endif //ARDUINO

#ifdef QT_LYNX
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#endif //QT_LYNX

#ifdef TI
// TODO MAGNUS
// Write here if you need includes
#include "DSP28x_Project.h"
#include   "f2802x_common/include/sci.h"
#include   "f2802x_common/include/clk.h"
#endif // TI


#include "LynxStructure.h"
// #include "RingBuffer.h"

#define DATABUFFER_SIZE 32
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

    // Closes the serial connection
    void close();

    // Returns connection state of port
    bool opened();

    // Links between received data and lynx. Run this as often as possible
    void update(LynxLib::LynxHandler& lynxHandler);

    // Sends content of the lynx id to the serial port
    int send(LynxLib::LynxHandler& lynxHandler, const LynxLib::LynxID& lynxID);

    // Returns true if new data has been received and added to lynx
    bool newData();

    // returns one character from the buffer at "index"
    char bufferAt(int index);

    // Returns number of communication errors since strtup
    int errorCount() { return _errorCounter; }

    // Enables device pairing
//    void enableDevicePairing() { _devicePairing = true; }

    //Disables device pairing
//    void disableDevicePairing() { _devicePairing = false; }

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
    // int _index = 0;
    bool _open = false;
    LynxLib::LynxID _tempID;
    // bool _devicePairing = false;
    bool _shuffleBytes = false;

	LynxLib::LynxList<LynxLib::LynxID> _idList;
#ifdef QT_LYNX
public:
    bool open(QSerialPortInfo port, int baudRate);
private:
    QSerialPort serialPort;
#endif //QT_LYNX

#ifdef TI
public:
    LynxLib::LynxRingBuffer <char>txBuffer;
    LynxLib::LynxRingBuffer <char>rxBuffer;
    void init(SCI_Handle _sciHandle,CLK_Handle _clkHandle);
    //UartHandler(SCI_Handle _sciHandle,CLK_Handle _clkHandle);
private:
    SCI_Handle sciHandle;
    CLK_Handle clkHandle;
    // int writeBytes(const char* buffer, int size,SCI_Handle sciHandle);
#endif //TI
};
