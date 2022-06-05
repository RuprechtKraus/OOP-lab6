#include "StringList.h"
#include <iostream>
#include <list>

int main()
{
	//StringList sl;
	//std::string str1("First string");
	//std::string str2("Second string");
	//std::string str3("Third string");
	//sl.PushBack(str1);
	//sl.PushBack(str2);
	////sl.PushBack(str3);
	//std::cout << std::endl;

	//auto it{ sl.cbegin() };
	//std::cout << "" << std::endl;

	//std::cout << std::endl;

	StringList list;
	std::string str1("First string");
	std::string str2("Second string");
	std::string str3("Third string");
	list.PushBack(str1);
	list.PushBack(str2);
	auto it{ list.Insert(++list.begin(), str3) };

	 /*std::cout << std::endl;

	 for (const auto& str : list)
	 {
		 std::cout << str << " ";
	 }
	 std::cout << std::endl;

	 std::cout << "" << std::endl;*/
}