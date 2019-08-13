#include "lynxiodevice.h"
namespace LynxLib
{
    LynxIoDevice::LynxIoDevice(LynxStructure & structure) :
        _state(eFindHeader),
        _lastID(),
        _structure(&structure),
		_open(false)
	{
	}


    LynxIoDevice::~LynxIoDevice()
	{
	}


    const LynxID & LynxIoDevice::runSerial()
    {
        _lastID.state = eNoChange;

		if (_state == eFindHeader)
		{
            // _lastID = LynxID();

            while (this->bytesAvailable() && (_state == eFindHeader))
			{
				_readBuffer.clear();
                this->readSerial();
				if (_readBuffer.at(0) == LYNX_STATIC_HEADER)
                    _state = eFindStructId;
			}
		}

        if(_state == eFindStructId)
        {
            if(this->bytesAvailable())
            {
                this->readSerial();

                _lastID.structId = uint8_t(_readBuffer.at(1));

                if (_lastID.structId == _structure->lynxID().structId)
                {
                    _state = eGetId;
                }
                else
                {
                    _state = eFindHeader;
                    _lastID.state = eStructIdNotFound;
                    return _lastID;
                }
            }
        }

        if (_state == eGetId)
		{
            if (this->bytesAvailable() >= (LYNX_HEADER_BYTES - 2))
			{
                this->readSerial();
                _lastID.index = int(_readBuffer.at(2)) - 1;
                if(_lastID.index > _structure->count())
                {
                    _state = eFindHeader;
                    _lastID.state = eIndexOutOfBounds;
                    return _lastID;
                }

                this->readSerial();
                _lastID.length = uint8_t(_readBuffer.at(3));
                if(_lastID.length > _structure->transferSize(_lastID.index))
                {
                    _state = eFindHeader;
                    _lastID.state = eWrongDataLength;
                    return _lastID;
                }

                this->readSerial();
                _lastID.deviceId = uint8_t(_readBuffer.at(4));

                _transferLength = _lastID.length + LYNX_CHECKSUM_BYTES;
                _state = eGetData;
			}
		}

        if (_state == eGetData)
		{
			if (this->bytesAvailable() >= _transferLength)
			{
				_readBuffer.resize(_readBuffer.count() + _transferLength);

                readSerial(_transferLength);

                _structure->fromArray(_readBuffer, _lastID);

				_state = eFindHeader;
			}
		}

		return _lastID;
	}

    void LynxIoDevice::sendSerial(int index)
	{
        _structure->toArray(_writeBuffer, index);
	
        this->writeSerial();
	}
}
