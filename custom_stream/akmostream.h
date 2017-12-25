#pragma once
#include <ostream> // ostream
#include <ios> // stream flags

#include "akm_u_m.h" // macro header
#include "akm_basic_stringbuf.h" // derived stringbuf


_AKM_BEGIN

template<class _Elem,
	class _Traits>
	class basic_akm_ostream;

template <class _Elem, class _Traits>
static basic_akm_ostream <_Elem, _Traits>& __CLR_OR_THIS_CALL console(basic_akm_ostream <_Elem, _Traits>& stream);

template <class _Elem, class _Traits>
static basic_akm_ostream <_Elem, _Traits>& __CLR_OR_THIS_CALL trace(basic_akm_ostream <_Elem, _Traits>& stream);

template<class _Elem,
	class _Traits>
	class basic_akm_ostream : public std::basic_ostream<_Elem, _Traits> {

	public:

		// typedef manipulators
		typedef basic_akm_ostream<_Elem, _Traits> _AkmT;
		typedef std::basic_ios<_Elem, _Traits> _AkmiosT;
		typedef std::basic_ostream<_Elem, _Traits> _AkmostreamT;

		explicit basic_akm_ostream() : std::basic_ostream<_Elem, _Traits>(new basic_akm_stringbuf<_Elem, _Traits>())
		{
		}

		_AkmT& __CLR_OR_THIS_CALL operator<<(_AkmT& ( *_Pfn)(_AkmT&))
		{
			// custom manipulators
			return ((*_Pfn)(*this));
		}

		_AkmT& __CLR_OR_THIS_CALL operator<<(_AkmostreamT& ( *_Pfn)(_AkmostreamT&))
		{
			// custom manipulators
			(*_Pfn)(*static_cast<_AkmostreamT *>(this));
			return (*this);
		}

		_AkmT& __CLR_OR_THIS_CALL operator<<(std::ios_base&( * fp)(std::ios_base&))
		{
			(*fp)(*static_cast<std::ios_base *>(this));
			return (*this);
		}

		_AkmT& __CLR_OR_THIS_CALL operator<<(_AkmiosT&( * fp)(_AkmiosT&))
		{
			(*fp)(*static_cast<_AkmiosT *>(this));
			return (*this);
		}



		~basic_akm_ostream() noexcept override;
};


//template class _CRTIMP2_PURE basic_akm_ostream<char, std::char_traits<char> >;
//template class _CRTIMP2_PURE basic_akm_ostream<wchar_t, std::char_traits<wchar_t> >;

template <class _Elem, class _Traits>
basic_akm_ostream<_Elem, _Traits>::~basic_akm_ostream() noexcept
{
	this->flush();
}
template <class _Elem, class _Traits>
static basic_akm_ostream <_Elem, _Traits>& __CLR_OR_THIS_CALL clr_trace(basic_akm_ostream <_Elem, _Traits>& stream)
{
	// clear flag _os_trace
	static_cast<basic_akm_stringbuf <_Elem, _Traits> *>(stream.rdbuf())->ClearFlag(_os_trace);
	return stream;
}


template <class _Elem, class _Traits>
static basic_akm_ostream <_Elem, _Traits>& __CLR_OR_THIS_CALL clr_console(basic_akm_ostream <_Elem, _Traits>& stream)
{
	// clear flag _os_console
	static_cast<basic_akm_stringbuf <_Elem, _Traits> *>(stream.rdbuf())->ClearFlag(_os_console);
	return stream;
}

template <class _Elem, class _Traits>
static basic_akm_ostream <_Elem, _Traits>& __CLR_OR_THIS_CALL console(basic_akm_ostream <_Elem, _Traits>& stream)
{
	// sync buf
	stream.rdbuf()->pubsync();
	// set flag _os_console
	static_cast<basic_akm_stringbuf <_Elem, _Traits> *>(stream.rdbuf())->SetFlag(_os_console);
	return stream;
}


template <class _Elem, class _Traits>
static basic_akm_ostream <_Elem, _Traits>& __CLR_OR_THIS_CALL trace(basic_akm_ostream <_Elem, _Traits>& stream)
{
	// sync buf
	stream.rdbuf()->pubsync();
	// set flag _os_trace
	static_cast<basic_akm_stringbuf  <_Elem, _Traits>*>(stream.rdbuf())->SetFlag(_os_trace);
	return stream;
}

typedef basic_akm_ostream<char, std::char_traits<char> > akmostream;
typedef basic_akm_ostream<wchar_t, std::char_traits<wchar_t> > akmwostream;

_AKM_END
