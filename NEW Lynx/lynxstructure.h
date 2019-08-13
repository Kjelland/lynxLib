//-----------------------------------------------------------------------------------------------------------
//------------------------------------------ LynxStructure V2.0 ---------------------------------------------
//-----------------------------------------------------------------------------------------------------------

#ifndef LYNX_STRUCTURE
#define LYNX_STRUCTURE

#ifdef TI
typedef uint16_t uint8_t
typedef int16_t int8_t
#else
#include <stdint.h>
#endif // TI

#ifndef LYNX_NULL
#ifdef TI
#define LYNX_NULL 0
#else
#define LYNX_NULL nullptr
#endif // TI
#endif // !LYNX_NULL

#define SIZE_64 sizeof(int64_t)

#define LYNX_STATIC_HEADER 'A'

#define LYNX_HEADER_BYTES 5
// #define LYNX_INDEXER_BYTES 2
#define LYNX_CHECKSUM_BYTES 1

#if !defined(ARDUINO) && !defined(TI)
#define LYNX_INCLUDE_EXCEPTIONS
#endif // !ARDUINO && !TI

namespace LynxLib
{
#ifdef LYNX_INCLUDE_EXCEPTIONS
	struct LynxMessages
	{
        static const char * outOfBoundsMsg;
	};
#endif // LYNX_INCLUDE_EXCEPTIONS

	//-----------------------------------------------------------------------------------------------------------
	//-------------------------------------------- LynxList -----------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------

	template <class T>
	class LynxList
	{
	public:
		LynxList()
		{
			_data = LYNX_NULL;
			_count = 0;
			_reservedCount = 0;
		}

		LynxList(int size) : LynxList()
		{
			this->reserve(size);
		}

		LynxList(const LynxList & other) : LynxList()
		{
			*this = other;
		}

		~LynxList()
		{
			if (_data != LYNX_NULL)
			{
				delete[] _data;
				_data = LYNX_NULL;
			}
		}

		LynxList & operator = (const LynxList & other)
		{
			if (&other == this)
				return *this;

			this->clear();
			this->resize(other.count());

			for (int i = 0; i < other.count(); i++)
			{
				this->append(other.at(i));
			}

			return *this;
		}

		T & operator [] (int index)
		{
#ifdef LYNX_INCLUDE_EXCEPTIONS
			if (index >= _count)
				throw LynxMessages::outOfBoundsMsg;
#endif // LYNX_INCLUDE_EXCEPTIONS

			return _data[index];
		}

		void clear() { _count = 0; }

		int count() const { return _count; }

		void reserve(int size)
		{
			_count = 0;

			if (size <= _reservedCount)
				return;

			if (_data != LYNX_NULL)
			{
				delete[] _data;
				_data = LYNX_NULL;
			}

			_reservedCount = size;
			_data = new T[_reservedCount];
		}

		void resize(int size)
		{
			if (size <= _reservedCount)
				return;

			if (_data == LYNX_NULL)
			{
				this->reserve(size);
				return;
			}

			T * oldData = _data;

			_reservedCount = size;

			_data = new T[_reservedCount];

			for (int i = 0; i < _count; i++)
			{
				_data[i] = oldData[i];
			}

			delete[] oldData;
			oldData = LYNX_NULL;
		}

		void append(const T & other)
		{
			this->resize(_count + 1);
			_data[_count] = other;
			_count++;
		}

		void append(const LynxList<T> & other)
		{
			this->resize(other.count() + _count);
			
			for (int i = 0; i < other.count(); i++)
			{
				_data[_count + i] = other.at(i);
			}

			_count += other.count();
		}

		void remove(int index)
		{
			if ((index < 0) || (index >= _count))
				return;

			for (int i = index; i < (_count - 1); i++)
			{
				_data[i] = _data[i + 1];
			}

			_count--;
		}

		const T & at(int index) const
		{
#ifdef LYNX_INCLUDE_EXCEPTIONS
			if (index >= _count)
				throw LynxMessages::outOfBoundsMsg;
#endif // LYNX_INCLUDE_EXCEPTIONS

			return _data[index];
		}

		const T & first() const { return this->at(0); }

		const T & last() const { return this->at(_count - 1); }

	protected:
		T * _data;
		int _count;
		int _reservedCount;
	};

	class LynxByteArray : public LynxList<char>
	{
	public:
		LynxByteArray() : LynxList<char>() {}
		LynxByteArray(int size) : LynxList<char>(size) {}
		LynxByteArray(const char * charArray, int size);
		const char * data() const { return _data; }

		// !!Assumes that the target buffer is of sufficcient size!!
		void toCharArray(char * buffer) const;

        const char * dataPointer() const { return _data; }
	};

	//-----------------------------------------------------------------------------------------------------------
	//---------------------------------------------- Types ------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------

    enum E_LynxErrorCode
    {
        eNoChange = 0,
        eNewDataReceived,
        eOutOfSync,
        eStructIdNotFound,
        eIndexOutOfBounds,
        eBufferToSmall,
        eWrongChecksum,
        eWrongStaticHeader,
        eWrongDataLength
    };

	enum E_LynxDataType
	{
		eInvalidType = 0,
		eInt8,
		eUint8,
		eInt16,
		eUint16,
		eInt32,
		eUint32,
		eInt64,
		eUint64,
		eFloat,
		eDouble
	};

	enum E_Endianness
	{
		eNotSet = 0,
		eBigEndian,
		eLittleEndian
	};

	class LynxType
	{
	public:
		LynxType();
		LynxType(E_LynxDataType dataType);
        LynxType(const LynxType & other) { *this = other; }

        int8_t & var_i8() { return _data._var_i8; }
        uint8_t & var_u8() { return _data._var_u8; }
        int16_t & var_i16() { return _data._var_i16; }
        uint16_t & var_u16() { return _data._var_u16; }
        int32_t & var_i32() { return _data._var_i32; }
        uint32_t & var_u32() { return _data._var_u32; }
        float & var_float() { return _data._var_float; }
        int64_t & var_i64() { return _data._var_i64; }
        uint64_t & var_u64() { return _data._var_u64; }
        double & var_double() { return _data._var_double; }

        const int8_t & const_var_i8() const { return _data._var_i8; }
        const uint8_t & const_var_u8() const { return _data._var_u8; }
        const int16_t & const_var_i16() const { return _data._var_i16; }
        const uint16_t & const_var_u16() const { return _data._var_u16; }
        const int32_t & const_var_i32() const { return _data._var_i32; }
        const uint32_t & const_var_u32() const { return _data._var_u32; }
        const float & const_var_float() const { return _data._var_float; }
        const int64_t & const_var_i64() const { return _data._var_i64; }
        const uint64_t & const_var_u64() const { return _data._var_u64; }
        const double & const_var_double() const { return _data._var_double; }

		E_LynxDataType dataType() const { return _dataType; }
		static int localSize(E_LynxDataType dataType);
		int localSize() const { return localSize(_dataType); }
        static int transferSize(E_LynxDataType dataType);
        int transferSize() const { return transferSize(_dataType); }

		int toArray(LynxByteArray & buffer) const;
		int fromArray(const LynxByteArray & buffer, int startIndex);

		// If the program assumes the wrong endianness it can be set manually with this function
		static void setEndianness(E_Endianness endianness) { LynxType::_endianness = endianness; }

		static E_Endianness endianness() { return _endianness; }

		const LynxType & operator = (const LynxType & other) 
		{
			if (&other == this)
				return *this;

			_data._var_i64 = other._data._var_i64;
			_dataType = other._dataType;

			return *this;
        }

	private:
		union LynxUnion
		{
			char bytes[SIZE_64];
			int8_t _var_i8;
			uint8_t _var_u8;
			int16_t _var_i16;
			uint16_t _var_u16;
			int32_t _var_i32;
			uint32_t _var_u32;
			float _var_float;
			int64_t _var_i64;
			uint64_t _var_u64;
			double _var_double;
		}_data;

		E_LynxDataType _dataType;
		static E_Endianness _endianness;
	};

	struct LynxID
	{
        LynxID() : structId(0), deviceId(0), length(0), index(-1), state(eNoChange) {}
        LynxID(uint8_t _structId, uint8_t _deviceId, E_LynxErrorCode _state = eNoChange, uint8_t _length = 0) :
            structId(_structId),
            deviceId(_deviceId),
            length(_length),
            index(-1),
            state(_state)
        {}
        LynxID(const LynxID & other)
        { *this = other; }

		uint8_t structId;
		uint8_t deviceId;
		uint8_t length;
		int index;
        E_LynxErrorCode state;

        // bool operator == (const LynxID & other) const { return((structId == other.structId) && (length == other.length)); }
        // bool operator != (const LynxID & other) const { return(!(*this == other)); }

        const LynxID & operator = (const LynxID & other)
        {
            if (&other == this)
                return *this;

            index = other.index;
            state = other.state;
            length = other.length;
            deviceId = other.deviceId;
            structId = other.structId;

            return *this;
        }
	};

	//-----------------------------------------------------------------------------------------------------------
	//---------------------------------------- LynxStructure ----------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------

	class LynxStructure
	{
	public:
		LynxStructure(LynxID lynxID);
        LynxStructure(uint8_t structID, uint8_t deviceID) : LynxStructure(LynxID(structID, deviceID)) {}

        LynxType & operator [] (int index) { return _variables[index]; }

        const LynxType & at(int index) const { return _variables.at(index); }
		
		const LynxID & lynxID() const { return _lynxID; }

		// Creates a buffer with the desired information, and returns it
		LynxByteArray toArray(int index = -1) const;

		// Copies the desired information to the provided buffer
		void toArray(LynxByteArray & buffer, int index = -1) const;

		// Copies the required information to the char array, and returns number of bytes copied
		int toArray(char * buffer, int index = -1) const;

		// Copies information from the provided buffer
        void fromArray(const LynxByteArray & buffer, LynxID & lynxId);

		// Copies information from char array, and returns number of bytes copied
        void fromArray(const char * buffer, int size, LynxID & lynxId);

		// Manually add a variable to the variable list
		void addVariable(E_LynxDataType dataType);

		// Returns the transfersize of requested data (not including header and checksum)
		int transferSize(int index = -1) const;

		// Returns the local size of requested data (not including header and checksum)
		int localSize(int index = -1) const;

        // Returns number of variables in the struct
        int count() const { return _variables.count(); }

	private:
		LynxList<LynxType> _variables;
		LynxID _lynxID;
	};
}

#endif // !LYNX_STRUCTURE
