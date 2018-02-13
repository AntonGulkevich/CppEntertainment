#pragma once

#include  "CustomStr.h"
#include <iostream>

int main (void)
{
	CustomStr str1{ "Str1", 4 };
	CustomStr str2{ "Str2", 5 };

	std::cout << str1 << std::endl << str2 << std::endl;

	std::cout << "1. Str1 + Str2: " << str1 + str2 << std::endl;
	std::cout << "2. Str1 - Str2: " << str1 - str2 << std::endl;
	std::cout << "2. Str1 * Str2: " << str1 * str2 << std::endl;



	return 0;
}
