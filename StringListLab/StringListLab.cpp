#include "StringList.h"
#include <iostream>
#include <list>

int main()
{
	StringList sl;
	sl.PushBack("Back element string");
	std::cout << sl.GetFrontElement() << std::endl;

	std::list<int> lt;
	lt.clear();
}