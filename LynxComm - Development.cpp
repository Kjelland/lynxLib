// LynxComm - Development.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

// #include "LynxComm.h"
#include "LynxStructure.h"
#include "controllerstruct.h"

#define LYNX_MACHINE_ID 0x12

using namespace LynxStructureSpace;

char dataBuffer[64];

int main()
{
	// StaticProperties::init();

	// E_Endianness endian = StaticProperties::localEndian;

	// LynxID lynxID { LYNX_MACHINE_ID, 1 };

	// LynxStructure structure;
	// structure.init(controllerDefinition, { 1, 1, 1 });

	LynxHandler lynx(LYNX_MACHINE_ID);

	LynxID contr_1 = lynx.addStructure(CONTROLLER_STRUCT, 0x1, controllerDefinition);

	LynxID contr_2 = lynx.addStructure(CONTROLLER_STRUCT, 0x2, controllerDefinition);

	lynx.setData<int16_t>(contr_1, joy_LX, 0x0123);
	lynx.setData<int16_t>(contr_1, joy_LY, 0x4567);
	lynx.setData<int16_t>(contr_1, joy_RX, 0x89AB);
	lynx.setData<int16_t>(contr_1, joy_RY, 0xCDEF);
	lynx.setData<int8_t>(contr_1, trigger_L, 0x01);
	lynx.setData<int8_t>(contr_1, trigger_R, 0x23);
	lynx.setData<uint32_t>(contr_1, buttons, 0x456789AB);

	int16_t testJoy_LX = lynx.getData<int16_t>(contr_1, joy_LX);
	int16_t testJoy_LY = lynx.getData<int16_t>(contr_1, joy_LY);
	int16_t testJoy_RX = lynx.getData<int16_t>(contr_1, joy_RX);
	int16_t testJoy_RY = lynx.getData<int16_t>(contr_1, joy_RY);
	int8_t testTrig_L = lynx.getData<int8_t>(contr_1, trigger_L);
	int8_t testTrig_R = lynx.getData<int8_t>(contr_1, trigger_R);
	uint32_t testButtons = lynx.getData<uint32_t>(contr_1, buttons);

	int sendtData = lynx.toBuffer(contr_1, dataBuffer);

	// data.clear();

	// int16_t test1 = data.getData<int16_t>(joy_LX);
	// int16_t test2 = data.getData<int16_t>(joy_RX);

	dataBuffer[2] = 0x2;

	int receivedData = lynx.fromBuffer(dataBuffer);

	testJoy_LX = lynx.getData<int16_t>(contr_2, joy_LX);
	testJoy_LY = lynx.getData<int16_t>(contr_2, joy_LY);
	testJoy_RX = lynx.getData<int16_t>(contr_2, joy_RX);
	testJoy_RY = lynx.getData<int16_t>(contr_2, joy_RY);
	testTrig_L = lynx.getData<int8_t>(contr_2, trigger_L);
	testTrig_R = lynx.getData<int8_t>(contr_2, trigger_R);
	testButtons = lynx.getData<uint32_t>(contr_2, buttons);


	// return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
