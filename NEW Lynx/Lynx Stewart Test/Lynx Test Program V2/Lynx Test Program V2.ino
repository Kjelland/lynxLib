/*
 Name:		Lynx_Test_Program_V2.ino
 Created:	8/7/2019 10:37:03 PM
 Author:	teodo
*/

#include "lynxstructure.h"
#include "lynxuartarduino.h"
#include "stewartcontrol.h"

using namespace LynxLib;

LynxManager lynx(0x02);

LynxUartArduino uart(lynx);

LynxInfo updateInfo;

StewartControl stewartControl(lynx, 0x22);
StewartFeedback stewartFeedback(lynx, 0x23);


// the setup function runs once when you press reset or power the board
void setup() 
{
	uart.open(0, 9600);

	pinMode(LED_BUILTIN, OUTPUT);
}


// the loop function runs over and over again until power down or reset
void loop() 
{
	updateInfo = uart.update();

	if (updateInfo.state != eNoChange)
		onNewData();

}

static bool onNewData()
{
	if (updateInfo.state == eNewDataReceived)
	{
		if (updateInfo.lynxId == stewartControl.setpointX.lynxId())
		{
			stewartFeedback.feedbackX = float(stewartControl.setpointX);
		}
		else if (updateInfo.lynxId == stewartControl.setpointY.lynxId())
		{
			stewartFeedback.feedbackY = float(stewartControl.setpointY);
		}
		else if (updateInfo.lynxId == stewartControl.setpointZ.lynxId())
		{
			stewartFeedback.feedbackZ = float(stewartControl.setpointZ);
		}
		else if (updateInfo.lynxId == stewartControl.setpointRoll.lynxId())
		{
			stewartFeedback.feedbackRoll = float(stewartControl.setpointRoll);
		}
		else if (updateInfo.lynxId == stewartControl.setpointPitch.lynxId())
		{
			stewartFeedback.feedbackPitch = float(stewartControl.setpointPitch);
		}
		else if (updateInfo.lynxId == stewartControl.setpointYaw.lynxId())
		{
			stewartFeedback.feedbackYaw = float(stewartControl.setpointYaw);
		}

		uart.send(stewartFeedback.lynxId);
	}
	else
	{
		digitalWrite(LED_BUILTIN, HIGH);
	}
}


