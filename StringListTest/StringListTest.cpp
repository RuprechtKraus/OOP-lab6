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
		Assert::AreEqual(expectedFront.value(), list.GetFront(), L"Actual front element doesn't match expected");
	}

	if (expectedBack)
	{
		Assert::AreEqual(expectedBack.value(), list.GetBack(), L"Actual back element doesn't match expected");
	}
}

bool AreListsEqual(const StringList& left, const StringList& right)
{
	return std::equal(left.cbegin(), left.cend(), right.cbegin(), right.cend());
}

namespace StringListTest
{
	#pragma warning(push)
	#pragma warning(disable: 26800)

	TEST_CLASS(StringListTest)
	{
	public:
		
		TEST_METHOD(ConstructEmptyList)
		{
			StringList list;
			VerifyStringList(list, 0, true, std::nullopt, std::nullopt);
		}

		TEST_METHOD(CopyConstruct)
		{
			StringList l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");

			StringList l2(l1);
			VerifyStringList(l2, 3, false, "1", "3");
			Assert::IsTrue(AreListsEqual(l1, l2), L"Lists aren't equal");
		}

		TEST_METHOD(MoveConstruct)
		{
			StringList l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");

			StringList l2(std::move(l1));
			VerifyStringList(l1, 0, true, std::nullopt, std::nullopt);
			VerifyStringList(l2, 3, false, "1", "3");
		}

		TEST_METHOD(CopyAssign)
		{
			StringList l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");

			StringList l2 = l1;
			VerifyStringList(l2, 3, false, "1", "3");
			Assert::IsTrue(AreListsEqual(l1, l2), L"Lists aren't equal");
		}

		TEST_METHOD(MoveAssign)
		{
			StringList l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");

			StringList l2 = std::move(l1);
			VerifyStringList(l1, 0, true, std::nullopt, std::nullopt);
			VerifyStringList(l2, 3, false, "1", "3");
		}
		
		TEST_METHOD(RangeConstruct)
		{
			StringList l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");
			l1.PushBack("4");
			l1.PushBack("5");

			StringList l2(++l1.begin(), --l1.end());
			VerifyStringList(l2, 3, false, "2", "4");
		}

		TEST_METHOD(AssignMethod)
		{
			StringList l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");

			StringList l2;
			l2.Assign(l1.cbegin(), l1.cend());
			VerifyStringList(l2, 3, false, "1", "3");
			Assert::IsTrue(AreListsEqual(l1, l2), L"Lists aren't equal");
		}

		TEST_METHOD(SwapMethod)
		{
			StringList l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");

			StringList l2;
			l2.PushBack("4");
			l2.PushBack("5");

			l1.Swap(l2);
			VerifyStringList(l1, 2, false, "4", "5");
			VerifyStringList(l2, 3, false, "1", "3");
		}

		TEST_METHOD(GetBackAndFrontElements)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);

			Assert::AreEqual(str1, list.GetFront(), L"Actual front element doesn't match expected");
			Assert::AreEqual(str2, list.GetBack(), L"Actual back element doesn't match expected");
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

		TEST_METHOD(PopBack)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");

			list.PushBack(str1);
			list.PushBack(str2);
			list.PopBack();
			VerifyStringList(list, 1, false, str1, str1);
		}

		TEST_METHOD(PopFront)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");

			list.PushBack(str1);
			list.PushBack(str2);
			list.PopFront();
			VerifyStringList(list, 1, false, str2, str2);
		}

		TEST_METHOD(InsertElementInTheBeginning)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			auto it{ list.Insert(list.begin(), str2) };
			
			VerifyStringList(list, 2, false, str2, str1);
			Assert::AreEqual(str2, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(InsertElementInTheEnd)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			auto it{ list.Insert(list.end(), str2) };

			VerifyStringList(list, 2, false, str1, str2);
			Assert::AreEqual(str2, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(InsertElementInTheMiddle)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			std::string str3("Third string");
			list.PushBack(str1);
			list.PushBack(str2);
			auto it{ list.Insert(++list.begin(), str3) };

			VerifyStringList(list, 3, false, str1, str2);
			Assert::AreEqual(*(++list.begin()), str3, L"Actual second element doesn't match expected");
			Assert::AreEqual(str3, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(InsertElementInTheBeginningOfEmptyList)
		{
			StringList list;
			std::string str1("First string");
			auto it{ list.Insert(list.begin(), str1) };

			VerifyStringList(list, 1, false, str1, str1);
			Assert::AreEqual(str1, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(InsertElementInTheEndOfEmptyList)
		{
			StringList list;
			std::string str1("First string");
			auto it{ list.Insert(list.end(), str1) };

			VerifyStringList(list, 1, false, str1, str1);
			Assert::AreEqual(str1, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(IncrementReturnedIteratorAfterInsertingElementInTheMiddle)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			std::string str3("Third string");
			list.PushBack(str1);
			list.PushBack(str2);
			auto it{ list.Insert(++list.begin(), str3) };

			Assert::AreEqual(str2, *(++it), L"Incremented returned iterator points to wrong element");
		}

		TEST_METHOD(DecrementReturnedIteratorAfterInsertingElementInTheMiddle)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			std::string str3("Third string");
			list.PushBack(str1);
			list.PushBack(str2);
			auto it{ list.Insert(++list.begin(), str3) };

			Assert::AreEqual(str1, *(--it), L"Incremented returned iterator points to wrong element");
		}

		TEST_METHOD(EraseInTheBeginning)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);
			auto it{ list.Erase(list.begin()) };

			VerifyStringList(list, 1, false, str2, str2);
			Assert::AreEqual(str2, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(EraseInTheEnd)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);
			auto it{ list.Erase(--list.end()) };

			VerifyStringList(list, 1, false, str1, str1);
			Assert::IsTrue(list.end() == it, L"Returned iterator doesn't point to end");
		}

		TEST_METHOD(EraseInTheMiddle)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			std::string str3("Third string");
			list.PushBack(str1);
			list.PushBack(str2);
			list.PushBack(str3);
			auto it{ list.Erase(++list.begin()) };

			VerifyStringList(list, 2, false, str1, str3);
			Assert::AreEqual(str3, *it, L"Returned iterator points to wrong element");
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

	TEST_CLASS(StringListIteratorTest)
	{
		TEST_METHOD(DereferenceIterator)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);

			Assert::AreEqual(str1, *list.begin(), L"Iterator points to wrong element");
		}

		TEST_METHOD(ChangeElementValueThroughIterator)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);
			*list.begin() = "Third string";

			Assert::AreEqual("Third string"s, *list.begin(), L"Iterator points to wrong element");
		}

		TEST_METHOD(DereferenceReverseIterator)
		{
			StringList list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);

			Assert::AreEqual(str2, *list.rbegin(), L"Iterator points to wrong element");
		}

		TEST_METHOD(IterateThroughMyStringReversively)
		{
			StringList list;
			list.PushBack("1");
			list.PushBack("2");
			list.PushBack("3");

			std::ostringstream ss;
			for (StringList::ConstReverseIterator it = list.rbegin(); it != list.rend(); it++)
			{
				ss << *it << " ";
			}

			Assert::AreEqual("3 2 1 "s, ss.str(), L"Iteration through list failed");
		}
	};

	#pragma warning(pop)
}