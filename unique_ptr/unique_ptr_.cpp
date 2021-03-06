#pragma once

#include <memory> // unique_ptr
#include <iostream> // cout

/*
* One more way how to use the dynamically allocated
* memory without operator "new" either "delete".
*/

using BYTE = unsigned char;
using _UpByteArray = std::unique_ptr<BYTE[]>;

class Ut
{
	_UpByteArray _upBuffer;
	size_t _stBufferSize = 1024 * 1024 * 10;
	size_t _usedSize;

public:
	Ut() : _usedSize(0)
	{
	}

	~Ut()
	{
	}
	void Allocate10Mb() _NOEXCEPT
	{
		_upBuffer = std::make_unique<BYTE[]>(_stBufferSize);
	}

	void Reallocate(size_t _size)
	{
		auto _up_tmp = std::make_unique<BYTE[]>(_size);
		_upBuffer.swap(_up_tmp);
		memcpy_s(_upBuffer.get(), _size, _up_tmp.get(), _size);
	}

	void Deallocate() _NOEXCEPT
	{
		_upBuffer.reset(nullptr);
	}
	void Swap(_UpByteArray &_ex_buffer)
	{
		_ex_buffer.swap(_upBuffer);
	}

	auto GetBuffer() _NOEXCEPT
	{
		return std::ref(_upBuffer);
	}

	auto GetBufferPointer() _NOEXCEPT
	{
		return _upBuffer.get();
	}

	void Assign(const void * data, size_t _size, size_t _offset = 0) const
	{
		memcpy_s(_upBuffer.get() + _offset, _stBufferSize, data, _size);
	}
};


inline auto ExternalF(_UpByteArray & ref_external_buffer)
{
	/*
	* Use breakpoint here to profile the ut's buffer
	*/
	Ut ut;
	ut.Allocate10Mb();
	auto str = "Hello, this is string.";
	auto internalSize = strlen(str);
	ut.Assign(str, ++internalSize);
	ut.Reallocate(internalSize);
	ut.Swap(ref_external_buffer);
	ut.Deallocate();
	ut.Allocate10Mb();
	return internalSize;
}

int main(void)
{
	Ut ut;
	for (;;) {
		ExternalF(ut.GetBuffer());
		std::cout << ut.GetBufferPointer() << std::endl;
	}
	return 0;
}


