#include <iostream>
#include <list>
#include "StringList.h"

int main()
{
	StringList sl1;
	StringList sl2;

	sl1.PushBack("First");
	sl1.PushBack("Second");
	sl1.PushBack("Third");

	sl2.PushBack("1");
	sl2.PushBack("2");

	sl1 = sl2;
}