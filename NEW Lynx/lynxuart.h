#ifndef LYNX_UART
#define LYNX_UART

#include "lynxstructure.h"

namespace LynxLib
{ 
	enum E_SerialState
	{
		eFindHeader = 0,
		eFindStruct,
        eGetIndex,
        eGetLength,
        eGetDevice,
        eGetData
	};

	class LynxUartBaseClass
	{
	public:
		LynxUartBaseClass(LynxStructure & structure);
        virtual ~LynxUartBaseClass();

		virtual const LynxID & runSerial();
        virtual void sendSerial(int index = -1);
		virtual bool open(int port, int baudRate) = 0;
		virtual void close() = 0;
        virtual bool opened() { return _open; }

        virtual const LynxByteArray & readBuffer() const { return _readBuffer; }
        virtual const LynxByteArray & writeBuffer() const { return _writeBuffer; }

	protected:
		E_SerialState _state;
		LynxID _lastID;
		LynxStructure * _structure;
		int _transferLength;
        int _structIndex;
		bool _open;

        virtual int readSerial(int count = 1) = 0;
        // virtual void writeSerial(char * data, int size) = 0;
        virtual void writeSerial() = 0;
        // virtual void writeAll()  = 0;
		virtual int bytesAvailable() const = 0;

		LynxByteArray _readBuffer;
		LynxByteArray _writeBuffer;

        // bool _headerFound = false;
	};
}
#endif // !LYNX_UART
