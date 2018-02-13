#pragma once

#include <string>
#include <ostream>

class CustomStr
{
private:

	std::string _str{ "string" };
	unsigned int _ui{ 0 };

public:

	CustomStr(const std::string & str, const unsigned int _uint): _str(str), _ui(_uint){}
	
	CustomStr() = default;
	virtual ~CustomStr() = default;


	auto GetString() { return _str; }
	auto GetUnsignedInt() { return _ui; }

#pragma region 1. op operators

	/* 1
	 * +
	 */

	friend CustomStr operator+ (const CustomStr &left, const CustomStr & right)
	{
		return CustomStr { left._str +" + " + right._str,left._ui + right._ui };
	}

	/* 2
	 * -
	 */
	friend CustomStr operator- (const CustomStr &left, const CustomStr & right)
	{
		return CustomStr{ left._ui > right._ui ? (left._str + " - " + right._str,  left._ui - right._ui) : (right._ui - left._ui )};
	}

	/* 3
	* *
	*/
	friend CustomStr operator* (const CustomStr &left, const CustomStr & right)
	{
		return CustomStr{ left._str + " * " + right._str, left._ui * right._ui};
	}

	/* 4
	* /
	*/
	/* 5
	* %
	*/
	/* 6
	* ^
	*/
	/* 7
	* &
	*/
	/* 8
	* |
	*/
	/* 9
	* ~
	*/
	/* 10
	* !
	*/
	/* 11
	* =
	*/
	/* 12
	* <
	*/
	/* 13
	* >
	*/
	/* 14
	* +=
	*/
	/* 15
	* -=
	*/
	/* 16
	* *=
	*/
	/* 17
	* /=
	*/
	/* 18
	* %=
	*/
	/* 19
	* ^=
	*/
	/* 20
	* &=
	*/
	/* 21
	* |=
	*/
	/* 22
	* <<
	*/
	/* 23
	* >>
	*/
	/* 24
	* >>=
	*/
	/* 25
	* <<=
	*/
	/* 26
	* ==
	*/
	/* 27
	* !=
	*/
	/* 28
	* <=
	*/
	/* 29
	* >=
	*/
	/* 30
	* &&
	*/
	/* 31
	* ||
	*/
	/* 32
	* ++
	*/
	/* 33
	* --
	*/
	/* 34
	* ,
	*/
	/* 35
	* ->*
	*/
	/* 36
	* ->
	*/
	/* 37
	* ()
	*/
	/* 38
	* []
	*/

#pragma endregion 

#pragma region 2. user - defined conversion function

#pragma endregion 

#pragma region 3. allocation function

#pragma endregion 

#pragma region 4. deallocation function

#pragma endregion 

#pragma region 5. user-defined literal

#pragma endregion 

#pragma region 6. iostream operators

	friend std::ostream & operator<< (std::ostream & os, const CustomStr & str)
	{
		return os << str._str << ": " << str._ui;
	}

#pragma endregion 

};

