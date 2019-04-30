#pragma once

template <class T>
class RingBuffer
{
public:
	RingBuffer()
	{
		_buffer = nullptr;
		_reservedSize = 0;
		_writeIndex = 0;
		_readIndex = 0;
	}

	RingBuffer(int size)
	{
		_buffer = nullptr;

		this->init(size);
	}

	~RingBuffer()
	{
		if (_buffer)
		{
			delete[] _buffer;
			_buffer = nullptr;
		}
	}

	// Initializer, reserves space for data. If init has been run before, previous data will be deleted. 
	// Returns number of elements reserved (should be the same as "size"), or -1 if error.
	int init(int size)
	{
		if (_buffer)
		{
			delete[] _buffer;
			_buffer = nullptr;
		}

		_buffer = new T[size];

		if (_buffer)
		{
			_writeIndex = 0;
			_readIndex = 0;
			_reservedSize = size;

			return _reservedSize;
		}

		return -1;
	}
	
	// Returns number of elements currently stored in buffer.
	int count()
	{
		return _count;
	}
	
	// Returns free space in buffer.
	int freeCount()
	{
		return (_reservedSize - _count);
	}

	// Returns one element from the buffer. If there is nothing in the buffer, 0 is returned.
	T read()
	{
		if (_count <= 0)
			return T();

		T temp = _buffer[_readIndex];

		_count--;
		_readIndex++;
		if (_readIndex >= _reservedSize)
			_readIndex = 0;

		return temp;
	}
	
	// Reads "count" elements from the buffer and places it in "target".
	// If "count" is greater then number of elements in buffer, available elements will be read.
	// Returns number of elements read. 
	int read(T* target, int count)
	{
		int size;
		if (count > _count)
			size = _count;
		else
			size = count;

		for (int i = 0; i < size; i++)
		{
			target[i] = this->read();
		}

		return size;
	}

	// Writes one element "source" to the buffer
	void write(T source)
	{
		_buffer[_writeIndex] = source;

		if (_count < _reservedSize)
			_count++;

		_writeIndex++;
		if (_writeIndex >= _reservedSize)
			_writeIndex = 0;
	}

	// Writes "count" elements from "source" to the buffer.
	// Returns elements written.
	int write(T* source, int count)
	{
		for (int i = 0; i < count; i++)
		{
			this->write(source[i]);
		}

		return count;
	}

private:
	T* _buffer;
	
	int _count;
	int _reservedSize;
	
	int _writeIndex;
	int _readIndex;
};

