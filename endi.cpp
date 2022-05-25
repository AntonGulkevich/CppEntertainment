/*main.cpp*/

/*0*/ // comment lines below
/*0*/ #pragma once

#define NOMINMAX
#include <iterator>
#include <iso646.h>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <bitset>
#include <cassert>
#include <memory>
#include <functional>
#include <iomanip>
#include <chrono>
#include "Allocator.h"
#include <algorithm>
#include <deque>
#include <thread>
#include "Windows.h"
#include <locale>

/*1-3*/ // what is it?
/* 1*/extern "C" {	int x_extern_c; }
/* 2*/extern "C++" extern "C++" extern "C++" extern "C++" int x_extern;
/* 3*/extern "C++" extern "C++" extern "C++" extern "C++" extern int x_extern_storage;

/* 4*/ //is it ok (would it compile) ?
int& some_function() { auto x = 0;	return x; };

/*5-8*/ // tell the difference
/* 5*/int funct_with_some_struct(struct some_struct);
/* 6*/int funct_with_some_struct(some_struct(some_struct));
/* 7*/int funct_with_some_struct(some_struct((some_struct)));
/* 8*/int funct_with_some_struct2(some_struct some_struct);

struct some_struct {};

class c_class
{
	// what is 'who_am_i' ? 
	void foo(/*26*/struct who_am_i* s_ptr);
	c_class();
	// what does this mean ?
	/* 9*/compl c_class() = default;
};

class Base
{
public:
	// why do we need this d-tor? 
	virtual ~Base() = default;
	virtual void f() { b(); };
	virtual void b() { std::cout << "Base b()\n"; };
};

class FromBase final : public Base
{
public:
	void b() override { std::cout << "FromBase b()\n"; };
	void f() override { Base::f(); };
};


int setbits2(int destination, int source, int at, int numbits)
{
	int mask = ((~0u) >> (sizeof(int) * 8 - numbits)) << at;
	return (destination&~mask) | ((source << at)&mask);
}

void TestExtractApply()
{
	using bitset = std::bitset<32>;

	auto apply = [](int &value, int insert_value, int pos, int count)
	{
		for (auto i = 0u; i < count; ++i)
		{
			int _1_0 = (insert_value >> i) & 0x1;
			value ^= (-_1_0^ value) & (1UL << (pos + i));
		}
	};

	auto apply2 = [](int value, int insert_value, int pos, int count)->int
	{
		int mask = ((~0u) >> (sizeof(int) * 8 - count)) << pos;
		return (value&~mask) | ((insert_value << pos)&mask);
	};

	auto apply_cpp = [](bitset & bs_result, bitset bs_insert, int pos, int count)
	{
		for (auto i = pos; i < pos + count; ++i)
			bs_result.set(i, bs_insert[i - pos]);
	};

	int result = 0b1010101010;
	bitset bs_res(result);

	int pos = 1;
	int count = 4;
	int value = 0b1111;
	bitset bitset2(value);

	bitset2.all();

	//apply(result, value, pos, count);

	result = apply2(result, value, pos, count);

	apply_cpp(bs_res, bitset2, pos, count);

	std::cout << std::to_string(bs_res.to_ulong()) << " " << std::to_string(result) << std::endl;

	int a = 0;
	++a;
}


// Define a Function Pointer in a Container
class Storage
{
public:
	template <typename TemplateType>
	struct FunctionContainer {
		static std::function<void(std::shared_ptr<TemplateType>)> Function;
	};
};


class MyClass
{
public:

	template <typename TemplateType>
	void MyFunction(std::shared_ptr<TemplateType> parameter)
	{
		// Do something.
		// You can make this templated or non-templated.
	}
	MyClass()
	{
		// If you really want, you can templatize std::string in the following:
		Storage::FunctionContainer<std::string>::Function = std::bind(&MyClass::MyFunction<std::string>, this, std::placeholders::_1);
	}
};



template <class Elem>
using hsi_elem_string = std::basic_string < Elem, std::char_traits<Elem>, short_alloc<Elem, 256,
	alignof(Elem) < 8 ? 8 : alignof(Elem)>>;

using hsi_string = hsi_elem_string<char>;

using hsi_stringstream = std::basic_stringstream < char, std::char_traits<char>, short_alloc<char, 256,
	alignof(char) < 8 ? 8 : alignof(char)>>;

class StringContsainer
{
public:

	StringContsainer() = default;
	~StringContsainer() = default;


	// Create the stack-based arena from which to allocate
	hsi_string::allocator_type::arena_type _center_text_arena;
	// string representation
	hsi_string _center_text_caption{ _center_text_arena };
};

template<class _Ty> inline
void _Integral_to_string(const _Ty _Val, hsi_string & str)
{	// convert _Val to string
	static_assert(std::is_integral<_Ty>::value, "_Ty must be integral");
	using _UTy = std::make_unsigned_t<_Ty>;

	HSI_TCHAR _Buff[21]; // can hold -2^63 and 2^64 - 1, plus NUL
	HSI_TCHAR* const _Buff_end = _STD end(_Buff);
	HSI_TCHAR* _RNext = _Buff_end;
	auto _UVal = static_cast<_UTy>(_Val);
	if (_Val < 0)
	{
		_RNext = std::_UIntegral_to_buff(_RNext, 0 - _UVal);
		*--_RNext = '-';
	}
	else
		_RNext = std::_UIntegral_to_buff(_RNext, _UVal);

	str.append(_RNext, _Buff_end);
}

// to_string NARROW CONVERSIONS
inline void to_string(int _Val, hsi_string & str)
{	// convert int to string
	_Integral_to_string(_Val, str);
}

using uint32_hsi = unsigned int;

//template <class arithmetic_type/*, class = typename std::enable_if< std::is_arithmetic<arithmetic_type>::value >::type*/>

using arithmetic_type = float;
class СalibrationProvider
{
	// cache


	// _transpose_info
	struct _tr
	{
		// c-tor
		_tr() = delete;
		explicit _tr(arithmetic_type v) :value(v) {}
		explicit _tr(arithmetic_type v, arithmetic_type tr) :
			value(v),
			transposed_value(tr)
		{
		}

		//
		arithmetic_type value{};
		arithmetic_type transposed_value{};

		//
		void UpdateCoef(arithmetic_type v2, arithmetic_type tr2)
		{
			transpose_coef = (tr2 - transposed_value) / (v2 - value);
			offset = tr2 - transpose_coef * v2;
		}

		template <class It>
		inline static arithmetic_type Transpose(const It & it, arithmetic_type tr_v) noexcept
		{
			return it->transpose_coef * tr_v + it->offset;
		}

		// 
		float transpose_coef{ 1.0f };
		float offset{ 1.0f };
	};

	// arithmetic_type_comparator
	struct atc { bool operator() (const _tr &a, const _tr &b) const { return a.value < b.value; } };

	// transposed data
	std::set<_tr, atc> _transpose_infos;

	//
	inline arithmetic_type TransposeImp(arithmetic_type value) const
	{
		const auto lower_bound = std::lower_bound(_transpose_infos.begin(), _transpose_infos.end(), value,
			[](_tr tr, arithmetic_type inner_v)->bool {return tr.value < inner_v; });

		if (lower_bound != _transpose_infos.end())
			return _tr::Transpose(lower_bound, value);// lower_bound->transpose_coef * value + lower_bound->offset;

		// max 
		return _tr::Transpose(--_transpose_infos.end(), value);// max->transpose_coef * value + max->offset;
	}

public:

	// c-tor
	СalibrationProvider() = default;

	// d-tor
	~СalibrationProvider() = default;


	//
	arithmetic_type Transpose(arithmetic_type value) const
	{
		return _transpose_infos.size() > 1 ? TransposeImp(value) : value;
	}

	// load raw data
	void Load(arithmetic_type * pair_ptr[2], uint32_hsi pair_count)
	{
		// clear map
		_transpose_infos.clear();

		for (auto i = 0u; i < pair_count; ++i)
			Insert(pair_ptr[i][0], pair_ptr[i][1]);
	}

	// insert new calibration pair
	void Insert(arithmetic_type value_at, arithmetic_type value_transposed)
	{
		_tr tr_info{ value_at , value_transposed };

		// if point are empty - einser the first element and return
		if (_transpose_infos.empty())
		{
			_transpose_infos.emplace(tr_info);
			return;
		}

		// 
		auto up_it = _transpose_infos.upper_bound(tr_info);
		if (up_it != _transpose_infos.end())
		{
			// there is an element greater that the one pending insertion
			// change it
			auto info = *up_it;
			up_it = _transpose_infos.erase(up_it);
			info.UpdateCoef(tr_info.value, tr_info.transposed_value);
			up_it = _transpose_infos.emplace_hint(up_it, info);

			// check if there is item below
			if (up_it != _transpose_infos.begin())
			{
				--up_it;
				tr_info.UpdateCoef(up_it->value, up_it->transposed_value);
			}
			else
			{
				tr_info.transpose_coef = info.transpose_coef;
				tr_info.offset = info.offset;
			}
			//
			_transpose_infos.emplace(tr_info);
		}
		else
		{
			// this element is max
			// update only this element

			// previous iterator
			--up_it;
			tr_info.UpdateCoef(up_it->value, up_it->transposed_value);
			_transpose_infos.emplace(tr_info);

			// if prev is the first element
			if (up_it == _transpose_infos.begin())
			{
				// update it
				auto info = *up_it;
				_transpose_infos.erase(up_it);
				info.offset = tr_info.offset;
				info.transpose_coef = tr_info.transpose_coef;
				_transpose_infos.emplace(info);
			}
		}
	}
};

inline void transpose(const СalibrationProvider & pr, float value)
{
	std::cout << std::setw(8) << std::left << value << pr.Transpose(value) << std::endl;
}
/* 1st */
template<typename = void> int reversed_binary_value() { return 0; }
template <bool head, bool...digits>int reversed_binary_value() { return head + (reversed_binary_value<digits...>() << 1); }

template <int n, bool...digits>
struct CheckValues
{
	static void check(int x, int y)
	{
		CheckValues<n - 1, 0, digits...>::check(x, y);
		CheckValues<n - 1, 1, digits...>::check(x, y);
	}
};

template <bool...digits>
struct CheckValues<0, digits...>
{
	static void check(int x, int y)
	{
		int z = reversed_binary_value<digits...>();
		std::cout << (z + 64 * y == x);
	}
};

/* 2nd */
enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template<class T>
struct Traits
{
	static std::string name(int index)
	{
		return "";
	}
};

template<>
std::string Traits<Color>::name(int index)
{
	switch (static_cast<Color>(index))
	{
	case Color::red: return "red";
	case Color::green: return "green";
	case Color::orange: return "orange";
	default: return "unknown";
	}
}

template<>
std::string Traits<Fruit>::name(int index)
{
	switch (static_cast<Fruit>(index))
	{
	case Fruit::apple:return "apple";
	case Fruit::orange: return "orange";
	case Fruit::pear:return "pear";
	default: return "unknown";
	}
}

template <class function>
void do_cycle(function f, const unsigned count, int ms = 25)
{
	for (auto i = 0u; i < count; ++i)
	{
		f(i);
		std::this_thread::sleep_for(std::chrono::milliseconds{ ms });
	}
}

//#define SKIP



/**
 * 	bool inc{ false };
	ListNode* it;

	for (it = l1; it->next && l2->next; it = it->next, l2 = l2->next)
	{
		if (inc)
			++it->val;
		it->val += l2->val;
		inc = it->val > 9;
		if (inc)
			it->val -= 10;
	}

	// equal
	if (it->next == nullptr && l2->next == nullptr)
	{
		if (inc)
			++it->val;
		it->val += l2->val;
		inc = it->val > 9;
		if (inc)
		{
			it->val -= 10;
			it->next = l2;
			l2->val = 1;
			l2->next = nullptr;
		}
		return l1;
	}
	// differ
	if (it->next == nullptr)
	{
		if (inc)
			++it->val;
		it->val += l2->val;
		inc = it->val > 9;
		if (inc)
			it->val -= 10;
		it->next = l2->next;
		it = it->next;
	}
	else
	{
		if (inc)
			++it->val;
		it->val += l2->val;
		inc = it->val > 9;
		if (inc)
			it->val -= 10;
		it = it->next;
	}

	auto ls = it;

	for (; it && inc; it = it->next)
	{
		++it->val;
		inc = it->val > 9;
		if (inc)
			it->val -= 10;
		ls = it;
	}
	if (inc)
	{
		ls->next = l2;
		l2->val = 1;
		l2->next = nullptr;
	}

	return l1;
 */


struct ListNode
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode * CreateList(std::vector<int>values)
{
	ListNode * list_f = new ListNode(values.front());

	auto * the_last = list_f;

	if (values.size() > 1)
	{
		for (auto i = 1; i < values.size(); ++i)
		{
			auto tmp = new ListNode(values[i]);
			the_last->next = tmp;
			the_last = tmp;
		}
	}
	return list_f;
}


ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	auto l1it = l1;
	auto l2it = l2;
	auto res = new ListNode(0);
	ListNode* resitprev = nullptr;
	auto resit = res;

	// equal
	while (l1it != nullptr && l2it != nullptr)
	{
		resit->val += l1it->val + l2it->val;
		resit->next = new ListNode(resit->val / 10);
		resit->val %= 10;
		resitprev = resit;
		resit = resit->next;
		l1it = l1it->next;
		l2it = l2it->next;
	}

	// l1it
	while (l1it != nullptr)
	{
		resit->val += l1it->val;
		resit->next = new ListNode(resit->val / 10);
		resit->val %= 10;
		resitprev = resit;
		resit = resit->next;
		l1it = l1it->next;
	}

	// l2it
	while (l2it != nullptr)
	{
		resit->val += l2it->val;
		resit->next = new ListNode(resit->val / 10);
		resit->val %= 10;
		resitprev = resit;
		resit = resit->next;
		l2it = l2it->next;
	}

	// 
	if (resit->val == 0)
	{
		delete resitprev->next;
		resitprev->next = nullptr;
	}
	return res;
}

enum class Metric
{
	angle,
	km,
	nm,
	percent
};




class StorageType
{


public:
	virtual ~StorageType() = default;
};

struct TypeMetadata
{
private:

	union ExValue32
	{
		struct Arinc32BitWord
		{
			unsigned int address : 8; // [0-7]
			unsigned int sdi : 2;  // [8-9]
			unsigned int raw_value : 19; // [10-28]
			unsigned int matrix : 2; // [29-30]
			unsigned int parity_bit : 1;// [31]
		}_arinc_429_value;

		unsigned char _raw_data[4];
		float _float_32_value;
		unsigned int _uint32_value;
		int _int_32_value;
	}_ex_v;

	const Metric _metric;

public:
	//
	explicit TypeMetadata(Metric  m) : _metric(m) {}

	//
	void Set(Metric from, void * ptr_data, unsigned size)
	{

		if (size <= 4)
		{
			memset(_ex_v._raw_data, 0, 4);
			memcpy(_ex_v._raw_data, ptr_data, size);
		}
	}

};


class HwDriverAnalog
{
	static const Metric _hw_metric{ Metric::angle };

	static  float _hw_register;

public:

	static void Update(TypeMetadata * to)
	{
	}
};

class Updating
{
public:
	virtual ~Updating() = default;
	virtual void Update() = 0;
};

class BaseRaf
{
public:
	BaseRaf() = default;

	virtual ~BaseRaf() = default;
	virtual std::string GetStr() = 0;
	virtual void SetStr(std::string str) = 0;
};

class Str1 : public BaseRaf
{

	std::string _str;
public:
	std::string GetStr() override
	{
		return _str;
	}
	void SetStr(std::string str) override
	{
		_str = str;
	}
};

class Str2 : public BaseRaf
{

	std::string _str;
public:
	std::string GetStr() override
	{
		return _str;
	}
	void SetStr(std::string str) override
	{
		_str = str;
		_str += " additional";
	}
};
class Str12 : public Str2, public Str1, public Updating
{

public:
	Str12() = default;

	void Update() override
	{
		Str1::SetStr({ "Str1" });
		Str2::SetStr({ "Str2" });
	}
};
#include <fstream>

std::string getLastLines(std::string const& filename, int lineCount)
{
	size_t const granularity = 100 * lineCount;
	std::ifstream source(filename.c_str(), std::ios_base::binary);
	source.seekg(0, std::ios_base::end);
	size_t size = static_cast<size_t>(source.tellg());
	std::vector<char> buffer;
	int newlineCount = 0;
	while (source
		&& buffer.size() != size
		&& newlineCount < lineCount) {
		buffer.resize(std::min(buffer.size() + granularity, size));
		source.seekg(-static_cast<std::streamoff>(buffer.size()),
			std::ios_base::end);
		source.read(buffer.data(), buffer.size());
		newlineCount = std::count(buffer.begin(), buffer.end(), '\n');
	}
	std::vector<char>::iterator start = buffer.begin();
	while (newlineCount > lineCount) {
		start = std::find(start, buffer.end(), '\n') + 1;
		--newlineCount;
	}
	std::vector<char>::iterator end = remove(start, buffer.end(), '\r');
	return std::string(start, end);
}


// extracts bits_to_extract bits from position 
// return the extracted value as to 
template<class from, class to>
constexpr to Extract(from value, int position, int bits_to_extract) noexcept
{
	static_assert(!std::is_same<to, int>::value, "type can not be be signed int");
	return static_cast<to>(((1 << bits_to_extract) - 1) & (value >> (position)));
}

template<class from>
constexpr int ExtractToInt(from value, int position, int bits_to_extract) noexcept
{
	return static_cast<int>(value << (32 - bits_to_extract - position)) >> (32 - bits_to_extract);
}

// insert src value into dest from pos in bits with count in bits
// return result of insertion
static constexpr int Insert(int dest, int src, int pos, int count) noexcept
{
	return (dest&~(((~0u) >> (32 - count)) << pos)) | ((src << pos)&(((~0u) >> (32 - count)) << pos));
}

int main(int argc, char** argv)
{
	int src_value = -64;


	auto value = 0xDEADC0DE;

	int from = 12;
	int count_insert = 8;

	std::cout << std::bitset<32>(value).to_string() << "\n";
	std::cout << std::bitset<32>(src_value).to_string() << "\n";
	value = Insert(value, src_value, from, count_insert);
	std::cout << std::bitset<32>(value).to_string() << "\n";

	auto res = ExtractToInt<int>(value, from, count_insert);
	std::cout << res << "\n";
	res = Extract<int, unsigned int>(value, from, count_insert);
	std::cout << res << "\n";

	std::string filename;
	int row_count = reinterpret_cast<int>(argv[0]);
	int update_time_ms = reinterpret_cast<int>(argv[1]);
	
	if (argc != 4)
	{
		std::cout << "need 3 args: filename(ex:C:\tracker-server.log) row_count(ex:5) time_ms(ex:1000)";
		std::cout << "\nfilename:";
		std::cin >> filename;
		std::cout << "\nrow count:";
		std::cin >> row_count;
		std::cout << "\nms:";
		std::cin >> update_time_ms;
	}
	else
	{
		char* p;
		filename = std::string(argv[1]);
		row_count = strtol(argv[2], &p, 10);
		update_time_ms = strtol(argv[3], &p, 10);
	}

	while(true)
	{
		system("CLS");
		auto str = getLastLines("C:\\tracker-server.log", row_count);
		std::cout << str;
		std::this_thread::sleep_for(std::chrono::milliseconds{ update_time_ms });
	}

	return 0;

	//	Metric ma{ Metric::angle };
	//
	//	float f_v{ 34.23f };
	//	int i_v{ 34 };
	//	unsigned int ui_v{ 34u };
	//
	//
	//	Str12 str;
	//
	//	Str1* p_str1 = &str;
	//	Str2* p_str2= &str;
	//	str.Update();
	//
	//	std::cout << p_str1->GetStr()<<std::endl;
	//	std::cout << p_str2->GetStr() << std::endl;
	//
	//	BaseRaf* p_BaseRaf1 = p_str1;
	//	BaseRaf* p_BaseRaf2 = p_str2;
	//	str.Update();
	//
	//	std::cout << p_BaseRaf1->GetStr() << std::endl;
	//	std::cout << p_BaseRaf2->GetStr() << std::endl;
	//
	//	//auto l1 = CreateList({ 1, 2, 3 });
	//	//auto l2 = CreateList({ 1, 2,});
	//
	//	auto l1 = CreateList({ 2, 4, 9 });
	//	auto l2 = CreateList({ 5, 6, 4, 9 });
	//
	//	//auto l1 = CreateList({ 9,9,9,9,9,9,9 });
	//	//auto l2 = CreateList({ 9,9,9,9 });
	//
	//	for (auto it = l1; it != nullptr; it = it->next)
	//	{
	//		std::cout << it->val << " ";
	//	}
	//	std::cout << "\n";
	//	for (auto it = l2; it != nullptr; it = it->next)
	//	{
	//		std::cout << it->val << " ";
	//	}
	//
	//	l1 = addTwoNumbers(l1, l2);
	//	std::cout << "\n";
	//
	//	for (auto it = l1; it != nullptr; it = it->next)
	//	{
	//		std::cout << it->val << " ";
	//	}
	//
	//	return 0;
	//	std::string rst{ "Press F to YouTube\n" };
	//
	//	const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	//
	//	// direct pattern
	//	const auto count = 15;
	//	std::chrono::milliseconds from_ms = std::chrono::milliseconds{ 50 };
	//
	//	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	//	auto position_start = GetConsoleScreenBufferInfo(h, &cbsi) ? cbsi.dwCursorPosition : COORD{ 0,0 };
	//	SetConsoleCursorPosition(h, position_start);
	//
	//#ifndef SKIP
	//	// 
	//	do_cycle([&rst, &from_ms](int i)
	//	{
	//		for (auto it = rst.begin(); it != rst.end(); ++it)
	//		{
	//			std::cout << *it;
	//			std::this_thread::sleep_for(std::chrono::milliseconds{ from_ms });
	//		}
	//		from_ms -= std::chrono::milliseconds{ 10 };
	//	}, 3, 30);
	//
	//	do_cycle([&rst, &from_ms, &h, &cbsi](int i)
	//	{
	//		for (auto it = rst.begin(); it != (rst.end() - 1); ++it)
	//		{
	//			std::cout << *it;
	//			std::this_thread::sleep_for(std::chrono::milliseconds{ from_ms });
	//		}
	//		auto position_start = GetConsoleScreenBufferInfo(h, &cbsi) ? cbsi.dwCursorPosition : COORD{ 0,0 };
	//
	//		std::transform(rst.begin(), rst.end(), rst.begin(), ::toupper);
	//
	//		for (auto it = rst.end() - 1; it != rst.begin(); --it)
	//		{
	//			SetConsoleCursorPosition(h, position_start);
	//			--position_start.X;
	//			std::cout << *it;
	//			std::this_thread::sleep_for(std::chrono::milliseconds{ from_ms });
	//		}
	//		SetConsoleCursorPosition(h, position_start);
	//		std::cout << *rst.begin();
	//		std::transform(rst.begin() + 1, rst.end(), rst.begin() + 1, ::tolower);
	//		std::cout << "\n";
	//
	//	}, 3, 30);
	//#endif
	//
	//	while (true)
	//	{
	//#ifndef SKIP
	//
	//		do_cycle([&rst](int i) {std::cout << rst; }, count, 45);
	//		do_cycle([&rst](int i) {std::cout << std::setw(i + rst.size()) << rst; }, count, 40);
	//		do_cycle([&rst, &count](int i) {std::cout << std::setw(rst.size() + count - i) << rst; }, count, 30);
	//		//0
	//		do_cycle([&rst](int i) {std::cout << std::setw(i + rst.size()) << rst; }, count);
	//		do_cycle([&rst, &count](int i) {std::cout << std::setw(rst.size()) << std::setfill(' ') << " " << rst.substr(i); }, rst.size());
	//		do_cycle([&rst, &count](int i) {std::cout << std::setfill(' ') << " " << rst.substr(i); }, rst.size());
	//
	//		// 0
	//		do_cycle([&rst, &count](int i) {std::cout << std::setfill(' ') << " " << rst.substr(rst.size() - i); }, rst.size());
	//		do_cycle([&rst, &count](int i) {std::cout << std::setw(rst.size()) << std::setfill(' ') << " " << rst.substr(rst.size() - i); }, rst.size());
	//
	//#endif
	//
	//		auto ms_st = 15;
	//
	//		auto skipped = 0;
	//		for (auto st = 0; st < rst.size() - 2; ++st)
	//		{
	//			if (rst[st + 1] == ' ')
	//			{
	//				++skipped;
	//				continue;
	//			}
	//			const auto st_total = st + skipped;
	//			const auto dir_switch = (st_total) % 2;
	//
	//			if (dir_switch)
	//			{
	//				do_cycle([&rst, &st](int i)
	//				{
	//					if (i > 1)
	//					{
	//						std::cout << rst.substr(0, st + 1)
	//							<< std::setw(rst.size() - i) << " "
	//							<< rst[st + 1] << std::setw(i - 1) << " "
	//							<< rst.substr(st + 2, rst.size() - 2);
	//					}
	//
	//					if (i == (rst.size() - 1))
	//					{
	//
	//						for (auto df = 0; df < 5; ++df)
	//						{
	//							std::cout << rst.substr(0, st + 1)
	//								<< std::setw(rst.size() - i) << " "
	//								<< rst[st + 1] << std::setw(i - 1) << " "
	//								<< rst.substr(st + 2, rst.size() - 2);
	//							std::this_thread::sleep_for(std::chrono::milliseconds{ 15 });
	//						}
	//					}
	//
	//				}, rst.size(), ms_st);
	//			}
	//			else
	//			{
	//				do_cycle([&rst, &st](int i)
	//				{
	//					if (i > 1)
	//					{
	//						std::cout << rst.substr(0, st + 1)
	//							<< std::setw(i - 1) << " "
	//							<< rst[st + 1]
	//							<< std::setw(rst.size() - i) << " "
	//							<< rst.substr(st + 2, rst.size() - 2);
	//					}
	//					if (i == (rst.size() - 1))
	//					{
	//
	//						for (auto df = 0; df < 5; ++df)
	//						{
	//							std::cout << rst.substr(0, st + 1)
	//								<< std::setw(i - 1) << " "
	//								<< rst[st + 1]
	//								<< std::setw(rst.size() - i) << " "
	//								<< rst.substr(st + 2, rst.size() - 2);
	//							std::this_thread::sleep_for(std::chrono::milliseconds{ 15 });
	//						}
	//					}
	//
	//				}, rst.size(), ms_st);
	//			}
	//		}
	//
	//#ifndef SKIP
	//		do_cycle([&rst, &count](int i) {std::cout << std::setw(rst.size()) << std::setfill(' ') << " " << rst.substr(i); }, rst.size());
	//		do_cycle([&rst, &count](int i) {std::cout << std::setfill(' ') << " " << rst.substr(i); }, rst.size());
	//		do_cycle([&rst, &count](int i) {std::cout << std::setfill(' ') << " " << rst.substr(rst.size() - i); }, rst.size());
	//#endif
	//	}
	//
	//
	//
	//
	//	//СalibrationProvider pr;
	//
	//	//pr.Insert(4, 2);
	//	//pr.Insert(8, 6);
	//	//pr.Insert(-3, -1);
	//	//pr.Insert(2, -2);
	//	//pr.Insert(13, 2);
	//	//for (auto i = -2; i < 15; ++i)
	//	//{
	//	//	transpose(pr, i);
	//	//}


	return 0;
	////Invocation
	//auto parameter = std::make_shared<std::string>();

	//Storage::FunctionContainer<std::string>::Function(parameter);


	//for (uint8_t matrix = 0; matrix < 0b11; ++matrix)
	//{
	//	auto matrix_ok = (matrix << 1) & 0x1;
	//	if (matrix_ok == 1)
	//	{
	//		// ok
	//		int a = 0;
	//		++a;
	//	}
	//	else
	//	{
	//		// error
	//		int a = 0;
	//		++a;
	//	}

	//}




	//TestExtractApply();


	//FromBase sdf;
	//// what would be printed ? 
	//sdf.f();
	//// what would be printed ? 
	//static_cast<Base*>(&sdf)->f();

	///*10-19*/
	//// write comment for each line
	//std::map<uint32_t, std::string> _map_int_string;
	///*10*/auto ret = _map_int_string.emplace(42ui32, "string");
	//int uno_0(1);
	//int uno_1{ 1 };
	//int uno_2[1];
	//int uno_3[1]{ 1 };
	///*13*/int(*functor)();
	///*14*/auto(*functor_d)() -> int;
	int& (&&fr)() = some_function;
	///*16*/auto(*functor_d_i)() -> int(&);
	///*17*/fr();
	///*18*/[]() {}();
	///*19*/auto strange_name = []()->bool {};

	///* 21 will it compile? write why
	//some_struct some_struct;
	//struct some_struct some_struct_1;
	//auto strange_name_2 = []()->bool {return false; }();
	//auto strange_name_3 = []()->bool {}();
	//*/

	///*22-26*/
	//// comment this
	///*22*/struct some_struct some_struct_2;
	///*23*/class std::vector<struct some_struct> some_structs;
	///*24*/class std::vector<class some_struct> some_classes;
	///*25*/void s_foo(struct  S* s_ptr);
	///*26*/who_am_i * who_am_i;

	///*27-30*/
	//// what is going on here? comment each line
	//int int_value;
	///*27*/using nice_foo = int;
	///*28*/int_value.~nice_foo();
	///*29*/~int();
	///*30*/auto sss = ~int();

	//return 0;
}
