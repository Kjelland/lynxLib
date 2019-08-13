#ifndef LYNX_UART_ARDUINO
#define LYNX_UART_ARDUINO

#include "lynxiodevice.h"
#include <Arduino.h>

using namespace LynxLib;

class LynxUartArduino :
	public LynxIoDevice
{
public:
	LynxUartArduino(LynxStructure & structure) : LynxIoDevice(structure) {};
	~LynxUartArduino() {};

	bool open(int port, int baudRate);
	void close();

private:
	int readSerial(int count = 1);
	void writeSerial();
	// void writeAll();
	int bytesAvailable() const;

	int _port;
};

#endif // !LYNX_UART_ARDUINO