#pragma once
#include "LynxStructure.h"

#define CONTROLLER_STRUCT 0x12

using namespace LynxStructureSpace;

enum ControllerContents
{
	joy_LX,
	joy_LY,
	joy_RX,
	joy_RY,
	trigger_L,
	trigger_R,
	buttons,
	endOfList
};

static const StructItem controllerItems[]
{
	{ "joy_LX", eInt16 },
	{ "joy_LY", eInt16 },
	{ "joy_RX", eInt16 },
	{ "joy_RY", eInt16 },
	{ "trigger_L", eInt8 },
	{ "trigger_R", eInt8 },
	{ "buttons", eUint32},
	{ "", eEndOfList }
};

static const StructDefinition controllerDefinition
{
	{ "Controller Struct" },
	{ eStructureMode },
	{ controllerItems }
};

// static const char controllerName[] = "Controller Struct";

#define CONTROLLER_ARRAY 0x13
static const StructItem controllerArrayItems[]
{
	{ "", eInt32 }
};

static const StructDefinition controllerArray
{
	{ "Controller Array" },
	{ eArrayMode },
	{ controllerArrayItems },
	{ 10 }
};