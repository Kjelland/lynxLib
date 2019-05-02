#include "RingBuffer.h"

/*
template<class T>
RingBuffer<T>::RingBuffer()
{
	_buffer = nullptr;
	_reservedSize = 0;
	_writeIndex = 0;
	_readIndex = 0;
}

template<class T>
RingBuffer<T>::~RingBuffer()
{
	if (_buffer)
	{
		delete[] _buffer;
		_buffer = nullptr;
	}
}


template<class T>
int RingBuffer<T>::init(int size)
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


 template<class T>
int RingBuffer<T>::count()
{
	return _count;
}

template<class T>
int RingBuffer<T>::freeCount()
{
	return (_reservedSize - _count);
}

template<class T>
T RingBuffer<T>::read()
{
	if (!_count)
		return T();

	T temp = _buffer[_readIndex];
	
	_count--;
	_readIndex++;
	if (_readIndex >= _reservedSize)
		_readIndex = 0;

	return temp;
}

template<class T>
int RingBuffer<T>::read(T * target, int count)
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

template<class T>
void RingBuffer<T>::write(T source)
{
	_buffer[_writeIndex] = source;

	_count++;
	_writeIndex++;

	if (_writeIndex > _reservedSize)
		_writeIndex = 0;
}

template<class T>
int RingBuffer<T>::write(T * source, int count)
{
	for (int i = 0; i < count; i++)
	{
		this->write(source[i]);
	}

	return count;
}
*/