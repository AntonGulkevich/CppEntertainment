#pragma once
#include <ostream> // cout
#undef str
#include <sstream> // basic_stringbuf
#include <utility> // std move
#include "akm_u_m.h" // macros and etc
//#include "../../utilities/console.h" // Write, Trace
#include <string>
#include <iostream>

_AKM_BEGIN

template<class _Elem>
int Print(const _Elem * str, size_t _SrcSize, dest_flag flag) {
	// unhandled type
	return 1;
};

template<>
inline int Print<char>(const char * str, size_t _SrcSize, dest_flag flag) {
	std::cout << str;

	return 0; /*Console::Send(static_cast<unsigned int>(flag), str, _SrcSize);*/
};

template<>
inline int Print<wchar_t>(const wchar_t * str, size_t _SrcSize, dest_flag flag) {
	//std::wcout << str;

	return 0;
};

// return error code on failure, zero in success
template< class _Elem, class _Traits, class _Alloc>
int SendStr(const std::basic_string<_Elem, _Traits, _Alloc> &_Mystr, dest_flag flag)
{
	/* send to akm*/
	return Print(_Mystr.c_str(), _Mystr.size(), flag);
}

template<class _Elem,
	class _Traits>
	class basic_akm_stringbuf : public std::basic_stringbuf<_Elem, _Traits>
{

	fmtFlags _fmtfl; // format flags

public:

	void SetFlag(_Fmtflags flag)
	{
		_fmtfl |= flag;
	}

	void ClearFlag(_Fmtflags flag)
	{
		_fmtfl &= ~flag;
	}

	basic_akm_stringbuf() : _fmtfl(0)
	{
	}

	int sync() override
	{
		auto err_no = NULL;
		// send to akm
		auto tmp = this->str();

		if (_fmtfl & _os_console)
		{

			err_no = SendStr(tmp, _Dstflags::_dst_console);
		}
		if (_fmtfl & _os_trace)
		{
			err_no = SendStr(tmp, _Dstflags::_dst_trace);
		}
//		this->_Tidy();
		this->str({});
		return err_no;
	}
};

typedef basic_akm_stringbuf<wchar_t, std::char_traits<wchar_t>> akmwstringbuf;
typedef basic_akm_stringbuf<char, std::char_traits<char>> akmstringbuf;

//akmwstringbuf wcout;
//akmstringbuf cout;
_AKM_END
