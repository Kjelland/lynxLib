//-------------------------------------------------------------------------------------------
//------------------------------------- Version 0.1.0.0 -------------------------------------
//-------------------------------------------------------------------------------------------

#pragma once
//#define QT_LYNX

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
#include "RingBuffer.h"

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
private:
	int serPort;
	E_State state = eIdle;

	int bytesIn = 0;

	char dataBuffer[DATABUFFER_SIZE];
	int index = 0;

#ifdef QT_LYNX
    QSerialPort serialPort;
#endif //QT_LYNX

#ifdef TI
	// TODO MAGNUS
	// Write here if you need stuff in the class
    SCI_Handle sciHandle;
    CLK_Handle clkHandle;
public:
    RingBuffer <char>txBuffer;
    RingBuffer <char>rxBuffer;
    UartHandler(SCI_Handle _sciHandle,CLK_Handle _clkHandle);
#endif //TI

public:
    UartHandler();

	bool open(int port, int baudRate);

	void update(LynxStructureSpace::LynxHandler& lynxHandler, const LynxStructureSpace::LynxID& _lynxID);
    int send(LynxStructureSpace::LynxHandler& lynxHandler, const LynxStructureSpace::LynxID& _lynxID);

    bool newData();

    char bufferAt(int index);

    int errorCount() { return errorCounter; }
private:
    char readByte();
    int readBytes(char* buffer, int size);
    int writeBytes(const char* buffer, int size);
    int writeBytes(const char* buffer, int size,SCI_Handle sciHandle);

    int bytesAvailable();
    bool _newData = false;
    int errorCounter = 0;
};

