#ifndef ARDUINOTEST_STRUCT
#define ARDUINOTEST_STRUCT 25

#include "LynxStructure.h"

using namespace LynxLib;

enum E_ArduinoTestContents
{
	mode,
	arduinoTestContents_EndOfList
};

static const StructItem arduinoTestItems[]
{
	StructItem( "mode", eUint8 ),
	StructItem( "", eEndOfList )
};

static const StructDefinition arduinoTestDefinition
{
	"ArduinoTest Struct",
	eStructureMode,
	arduinoTestItems
};

struct ArduinoTestWrapper
{
	ArduinoTestWrapper() {} 
	ArduinoTestWrapper(LynxHandler* lynxHandler, const LynxID& lynxID) { this->connect(lynxHandler, lynxID); } 

	void connect(LynxHandler* lynxHandler, const LynxID& lynxID)
	{
		var_mode.connect(lynxHandler, lynxID, mode);
	}

	LynxWrapperElement<uint8_t> var_mode;
};

#endif // ARDUINOTEST_STRUCT