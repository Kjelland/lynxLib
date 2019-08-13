#ifndef LYNX_UART_ARDUINO
#define LYNX_UART_ARDUINO

#include "lynxuart.h"
#include <Arduino.h>

using namespace LynxLib;

class LynxUartArduino :
	public LynxUartBaseClass
{
public:
	LynxUartArduino(LynxStructure & structure) : LynxUartBaseClass(structure) {};
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