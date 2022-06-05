#include "StringList.h"
#include <iostream>
#include <list>

int main()
{
	StringList sl;
	std::string str1("First string");
	std::string str2("Second string");
	std::string str3("Third string");
	sl.PushBack(str1);
	sl.PushBack(str2);
	//sl.PushBack(str3);
	std::cout << std::endl;

	auto it{ sl.cbegin() };
	std::cout << "" << std::endl;

	std::cout << std::endl;

	std::list<std::string> lt;
	lt.push_back("First string in list");
	lt.push_back("Second string in list");
	auto lit{ lt.crbegin() };
	std::cout << *lit << std::endl;
}