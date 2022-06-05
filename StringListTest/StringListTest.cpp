#include "pch.h"
#include "CppUnitTest.h"
#include "StringList.h"
#include <optional>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

void VerifyStringList(const StringList& list, size_t expectedSize, bool expectedToBeEmpty, 
	const std::optional<std::string>& expectedFront, const std::optional<std::string>& expectedBack)
{
	Assert::AreEqual(expectedSize, list.GetSize(), L"Actual size doesn't match expected");
	Assert::AreEqual(expectedToBeEmpty, list.IsEmpty());

	if (expectedFront)
	{
		Assert::AreEqual(expectedFront.value(), list.GetFrontElement(), L"Actual front element doesn't match expected");
	}

	if (expectedBack)
	{
		Assert::AreEqual(expectedBack.value(), list.GetBackElement(), L"Actual back element doesn't match expected");
	}
}

namespace StringListTest
{
	TEST_CLASS(StringListTest)
	{
	public:
		
		TEST_METHOD(ConstructEmptyList)
		{
			StringList list;
			VerifyStringList(list, 0, true, std::nullopt, std::nullopt);
		}

		TEST_METHOD(GetBackElement)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);

			Assert::AreEqual(str1, list.GetFrontElement(), L"Actual front element doesn't match expected");
			Assert::AreEqual(str2, list.GetBackElement(), L"Actual back element doesn't match expected");
		}

		TEST_METHOD(PushBackOneElement)
		{
			StringList list;
			std::string str("New string");
			list.PushBack(str);
			VerifyStringList(list, 1, false, str, str);
		}

		TEST_METHOD(PushBackTwoElements)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");

			list.PushBack(str1);
			list.PushBack(str2);
			VerifyStringList(list, 2, false, str1, str2);
		}

		TEST_METHOD(PushFrontOneElement)
		{
			StringList list;
			std::string str("New string");
			list.PushFront(str);
			VerifyStringList(list, 1, false, str, str);
		}

		TEST_METHOD(PushFrontTwoElements)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");

			list.PushFront(str1);
			list.PushFront(str2);
			VerifyStringList(list, 2, false, str2, str1);
		}

		TEST_METHOD(ClearList)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");

			list.PushFront(str1);
			list.PushFront(str2);
			list.Clear();

			VerifyStringList(list, 0, true, std::nullopt, std::nullopt);
		}
	};

	TEST_CLASS(StringListConstIteratorTest)
	{
	public:

		TEST_METHOD(DereferenceIterator)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);

			Assert::AreEqual(str1, *list.cbegin(), L"Iterator points to wrong element");
		}

		TEST_METHOD(IterateThroughList)
		{
			StringList list;
			list.PushBack("1");
			list.PushBack("2");
			list.PushBack("3");

			std::ostringstream ss;
			for (const auto& str : list)
			{
				ss << str << " ";
			}

			Assert::AreEqual("1 2 3 "s, ss.str(), L"Iteration through list failed");
		}

		TEST_METHOD(DereferenceReverseIterator)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);

			Assert::AreEqual(str2, *list.crbegin(), L"Iterator points to wrong element");
		}

		TEST_METHOD(IterateThroughMyStringReversively)
		{
			StringList list;
			list.PushBack("1");
			list.PushBack("2");
			list.PushBack("3");

			std::ostringstream ss;
			for (StringList::ConstReverseIterator it = list.crbegin(); it != list.crend(); it++)
			{
				ss << *it << " ";
			}

			Assert::AreEqual("3 2 1 "s, ss.str(), L"Iteration through list failed");
		}
	};
}