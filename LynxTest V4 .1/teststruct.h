#ifndef TEST_STRUCT
#define TEST_STRUCT 23

#include "LynxStructure.h"

using namespace LynxLib;

enum E_TestContents
{
	test_int8,
	test_uint8,
	test_int16,
	test_uint16,
	test_int32,
	test_uint32,
	test_int64,
	test_uint64,
	test_float,
	test_double,
	testContents_EndOfList
};

static const StructItem testItems[]
{
    StructItem( "test_int8", eInt8 ),
	StructItem( "test_uint8", eUint8 ),
	StructItem( "test_int16", eInt16 ),
	StructItem( "test_uint16", eUint16 ),
	StructItem( "test_int32", eInt32 ),
	StructItem( "test_uint32", eUint32 ),
	StructItem( "test_int64", eInt64 ),
	StructItem( "test_uint64", eUint64 ),
	StructItem( "test_float", eFloat ),
	StructItem( "test_double", eDouble ),
	StructItem( "", eEndOfList )
};

static const StructDefinition testDefinition
{
	"Test Struct",
	eStructureMode,
	testItems
};

struct TestWrapper
{
	TestWrapper() {} 
	TestWrapper(LynxHandler* lynxHandler, const LynxID& lynxID) { this->connect(lynxHandler, lynxID); } 

	void connect(LynxHandler* lynxHandler, const LynxID& lynxID)
	{
		var_test_int8.connect(lynxHandler, lynxID, test_int8);
		var_test_uint8.connect(lynxHandler, lynxID, test_uint8);
		var_test_int16.connect(lynxHandler, lynxID, test_int16);
		var_test_uint16.connect(lynxHandler, lynxID, test_uint16);
		var_test_int32.connect(lynxHandler, lynxID, test_int32);
		var_test_uint32.connect(lynxHandler, lynxID, test_uint32);
		var_test_int64.connect(lynxHandler, lynxID, test_int64);
		var_test_uint64.connect(lynxHandler, lynxID, test_uint64);
		var_test_float.connect(lynxHandler, lynxID, test_float);
		var_test_double.connect(lynxHandler, lynxID, test_double);
	}

    LynxWrapperElement<int8_t> var_test_int8;
	LynxWrapperElement<uint8_t> var_test_uint8;
	LynxWrapperElement<int16_t> var_test_int16;
	LynxWrapperElement<uint16_t> var_test_uint16;
	LynxWrapperElement<int32_t> var_test_int32;
	LynxWrapperElement<uint32_t> var_test_uint32;
	LynxWrapperElement<int64_t> var_test_int64;
	LynxWrapperElement<uint64_t> var_test_uint64;
	LynxWrapperElement<float> var_test_float;
	LynxWrapperElement<double> var_test_double;
};

#endif // TEST_STRUCT
