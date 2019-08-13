#include "lynxuart.h"
namespace LynxLib
{
	LynxUartBaseClass::LynxUartBaseClass(LynxStructure & structure) :
        _state(eFindHeader),
        _lastID(),
        _structure(&structure),
		_open(false)
	{
	}


	LynxUartBaseClass::~LynxUartBaseClass()
	{
	}


	const LynxID & LynxUartBaseClass::runSerial()
	{
        // if(_readBuffer.count() < 50)
        // {
        //     this->readSerial(this->bytesAvailable());
        // }
        // return _lastID;

		if (_lastID.deviceId != 0)
			_lastID = LynxID();

		if (_state == eFindHeader)
		{
            while (this->bytesAvailable() && (_state == eFindHeader))
			{
				_readBuffer.clear();
                this->readSerial();
				if (_readBuffer.at(0) == LYNX_STATIC_HEADER)
					_state = eFindStruct;
			}
		}

		if (_state == eFindStruct)
		{
			if (this->bytesAvailable())
			{
                this->readSerial();

				if (_readBuffer.at(1) == _structure->lynxID().structId)
                    _state = eGetIndex;
				else
					_state = eFindHeader;
			}
		}

        if (_state == eGetIndex)
        {
            if (this->bytesAvailable())
            {
                this->readSerial();

                _structIndex = int(_readBuffer.at(2)) - 1;
                _state = eGetLength;
            }
        }

        if (_state == eGetLength)
		{
			if (this->bytesAvailable())
			{
                this->readSerial();

                if (_readBuffer.at(3) != _structure->transferSize(_structIndex))
				{
					_state = eFindHeader;
				}
				else
				{
                    _transferLength = _readBuffer.at(3) + LYNX_CHECKSUM_BYTES;
                    _state = eGetDevice;
				}
			}
		}

        if(_state == eGetDevice)
        {
            if(this->bytesAvailable())
            {
                this->readSerial();
                _state = eGetData;
            }
        }

        if (_state == eGetData)
		{
			if (this->bytesAvailable() >= _transferLength)
			{
				_readBuffer.resize(_readBuffer.count() + _transferLength);

                readSerial(_transferLength);

				_lastID = _structure->fromArray(_readBuffer);

				_state = eFindHeader;
			}
		}

		return _lastID;
	}

    void LynxUartBaseClass::sendSerial(int index)
	{
        _structure->toArray(_writeBuffer, index);
	
        this->writeSerial();
	}
}
