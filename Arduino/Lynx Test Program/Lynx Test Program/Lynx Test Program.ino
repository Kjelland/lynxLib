/*
 Name:		Lynx_Test_Program.ino
 Created:	6/16/2019 9:18:47 PM
 Author:	teodo
*/

#include "LynxStructure.h"
#include "UartHandler.h"
#include "arduinoteststruct.h"
#include "teststruct.h"
// #include <sstream>
// #include <std::string>

#define DEVICE_ID 2
#define DEVICE_NAME "Arduino"

LynxHandler lynxHandler(DEVICE_ID, DEVICE_NAME, 3);
LynxID sendId;
LynxID receiveId;
LynxID modeId;

TestWrapper receiveStruct;
TestWrapper sendStruct;
ArduinoTestWrapper modeStruct;

UartHandler uartHandler(&lynxHandler);

class BlinkMode
{
public:
	BlinkMode(int pin) : _pin(pin) { _last = millis(); }

	void update()
	{
		if ((_interval > 0) && ((millis() - _last) > _interval))
		{
			_last = millis();
			_ledState = !_ledState;
			digitalWrite(_pin, _ledState);
		}
	}

	void on()
	{
		_interval = 0;
		_ledState = true;
		digitalWrite(_pin, _ledState);
	}

	void off()
	{
		_interval = 0;
		_ledState = false;
		digitalWrite(_pin, _ledState);
	}

	void toggle()
	{
		_interval = 0;
		_ledState = !_ledState;
		digitalWrite(_pin, _ledState);
	}

	void start(unsigned long interval)
	{
		_interval = interval;
	}

	void stop()
	{
		_interval = 0;
	}

private:
	bool _ledState = false;
	int _pin;
	unsigned long _last;
	unsigned long _interval = 0;
};

class Timer
{
public:
	Timer() {}
	Timer(unsigned long time) { start(time); }
	
	void start(unsigned long time)
	{
		_time = time;
		_last = millis();
	}

	void stop() { _time = 0; }

	void update() 
	{
		if (_time == 0)
			return;

		if ((millis() - _last) > _time)
		{
			_last = millis();
			_timeout = true;
		}
	}

	bool timeout() 
	{ 
		if (_timeout)
		{
			_timeout = false;
			return true;
		}

		return false;
	}

private:
	unsigned long _last;
	unsigned long _time = 0;
	bool _timeout = false;
};

Timer timer(1000);

// the setup function runs once when you press reset or power the board
void setup() 
{
	 receiveId = lynxHandler.addStructure(TEST_STRUCT, 1, testDefinition);
	 sendId = lynxHandler.addStructure(TEST_STRUCT, 2, testDefinition);
	 modeId = lynxHandler.addStructure(ARDUINOTEST_STRUCT, 1, arduinoTestDefinition);

	 uartHandler.open(0, 9600);
	 // Serial.begin(9600);

	 receiveStruct.connect(&lynxHandler, receiveId);
	 sendStruct.connect(&lynxHandler, sendId);
	 modeStruct.connect(&lynxHandler, modeId);

	 pinMode(LED_BUILTIN, OUTPUT);
	 // digitalWrite(LED_BUILTIN, HIGH);
}



// bool ledState = false;
BlinkMode internalLed(LED_BUILTIN);
LynxLib::LynxID prevID;
// the loop function runs over and over again until power down or reset
void loop() 
{
	internalLed.update();

	uartHandler.update();

	timer.update();

	if (timer.timeout())
	{
		// internalLed.toggle();
		// uartHandler.sendString("bump");
	}

	//if (uartHandler.lastReceivedId() != prevID)
	//{
	//	prevID = uartHandler.lastReceivedId();

	//	LynxString temp;

	//	temp += "Databuffer received: ";
	//	temp += LynxString::number(uartHandler.receiveBufferCount());
	//	temp += " bytes";
	//	for (int i = 0; i < uartHandler.receiveBufferCount(); i++)
	//	{
	//		temp += LynxString::number(static_cast<int>(uartHandler.receiveBufferAt(i)), 16);
	//		temp += ' ';
	//	}
	//	temp += '\n';
	//	uartHandler.sendString(temp);
	//}

	if (uartHandler.errorCount() > 0)
	{
		int error = uartHandler.getError();
		
		String temp = "\n----------------\nEncountered error: ";
		temp += String(error);
		uartHandler.sendString(temp.c_str());
	}
}

void NewData::onNewUartData(const LynxID& lynxID, int index)
{
	String temp = "\n----------------\nReceived:\n";

	//for (int i = 0; i < uartHandler.receiveBufferCount(); i++)
	//{
	//	temp += String(int(uartHandler.receiveBufferAt(i))) + " ";
	//}

	const uint8_t * tempVar = reinterpret_cast<const uint8_t*>(lynxHandler.getConstDataPointer(receiveId, test_int8));

	int localSize = lynxHandler.getLocalSize(receiveId, -1);
	int transferSize = lynxHandler.getTransferSize(receiveId, -1);

	temp += "Local size: ";
	temp += String(localSize);
	temp += " bytes\nTransfer size: ";
	temp += String(transferSize);
	temp += " bytes\n";

	uartHandler.sendString(temp.c_str());

	temp = "";
	for (int i = 0; i < localSize; i++)
	{
		temp += String(int(tempVar[i]));
		temp += " ";
	}

	// temp += "\n-----------------";

	uartHandler.sendString(temp.c_str());

	if (lynxID == modeId)
	{
		digitalWrite(LED_BUILTIN, modeStruct.var_mode);
	}
	else if ((lynxID == receiveId) && (modeStruct.var_mode == 0))
	{
		lynxHandler.copyData(lynxID, sendId, index);
		uartHandler.send(receiveId, index);

		String temp = "\n-----------------\n";
		temp +=	String(uartHandler.sendBufferCount());
		temp += " bytes in arduino send buffer";

		uartHandler.sendString(temp.c_str());
	}
}

