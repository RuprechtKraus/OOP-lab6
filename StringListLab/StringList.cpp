#include "StringList.h"
#include <iostream>

#pragma region StringList

StringList::Node::Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next)
	: m_data(data)
	, m_prev(prev)
	, m_next(std::move(next))
{
	std::cout << "Node with value \"" << m_data << "\" has been created" << std::endl;
}

StringList::Node::~Node() noexcept
{
	std::cout << "Node with value \"" << m_data << "\" has been destroyed" << std::endl;
}

StringList::~StringList() noexcept
{
	Clear();
}

void StringList::PushBack(const std::string& str)
{
	EmplaceBack(str);
}

void StringList::PushFront(const std::string& str)
{
	EmplaceFront(str);
}

StringList::NodePtr StringList::EmplaceBack(const std::string& str)
{
	auto node{ std::make_unique<Node>(str, m_last, nullptr) };
	Node* newLast{ node.get() };

	if (m_last)
	{
		m_last->m_next = std::move(node);
	}
	else
	{
		m_first = std::move(node);
	}
	m_last = newLast;

	m_size++;
	return m_last;
}

StringList::NodePtr StringList::EmplaceFront(const std::string& str)
{
	auto node{ std::make_unique<Node>(str, nullptr, std::move(m_first)) };
	Node* newFirst{ node.get() };

	m_first = std::move(node);
	if (m_last)
	{
		m_first->m_next->m_prev = newFirst;
	}
	else
	{
		m_last = newFirst;
	}

	m_size++;
	return m_first.get();
}

StringList::NodePtr StringList::Emplace(const std::string& str, NodePtr position)
{
	auto node{ std::make_unique<Node>(str, position->m_prev, std::move(position->m_prev->m_next)) };
	Node* newNode{ node.get() };

	newNode->m_prev->m_next = std::move(node);
	newNode->m_next->m_prev = newNode;
	m_size++;

	return newNode;
}

void StringList::Clear() noexcept
{
	while (m_first)
	{
		m_first = std::move(m_first->m_next);
	}

	m_size = 0;
}

void StringList::PopBack() noexcept
{
	_STL_ASSERT(m_size != 0, "PopBack called on empty list");
	EraseBack();
}

void StringList::PopFront() noexcept
{
	_STL_ASSERT(m_size != 0, "PopFront called on empty list");
	EraseFront();
}

StringList::NodePtr StringList::EraseBack() noexcept
{
	m_last = m_last->m_prev;
	m_last->m_next = nullptr;
	m_size--;
	return nullptr;
}

StringList::NodePtr StringList::EraseFront() noexcept
{
	m_first = std::move(m_first->m_next);
	m_first->m_prev = nullptr;
	m_size--;
	return m_first.get();
}

StringList::NodePtr StringList::Erase(NodePtr position) noexcept
{
	Node* node{ position->m_next.get() };
	position->m_next->m_prev = position->m_prev;
	position->m_prev->m_next = std::move(position->m_next);
	m_size--;
	return node;
}

bool StringList::IsEmpty() const noexcept
{
	return !m_first.get();
}

StringList::Iterator StringList::Insert(ConstIterator position, const std::string& str)
{
	_STL_VERIFY(position.m_container == this, "List insert iterator outside range");
	if (position.m_ptr == m_first.get())
	{
		return MakeIterator(EmplaceFront(str));
	}
	else if (position.m_ptr == nullptr)
	{
		return MakeIterator(EmplaceBack(str));
	}
	else
	{
		return MakeIterator(Emplace(str, position.m_ptr));
	}
}

StringList::Iterator StringList::MakeIterator(NodePtr ptr) const noexcept
{
	return Iterator(ptr, this);
}

StringList::ConstIterator StringList::MakeConstIterator(NodePtr ptr) const noexcept
{
	return ConstIterator(ptr, this);
}

StringList::Iterator StringList::Erase(ConstIterator position)
{
	_STL_VERIFY(position.m_container == this, "List erase iterator outside range");
	if (position.m_ptr == m_first.get())
	{
		return MakeIterator(EraseFront());
	}
	else if (position.m_ptr == m_last)
	{
		return MakeIterator(EraseBack());
	}
	else
	{
		return MakeIterator(Erase(position.m_ptr));
	}
}

std::string& StringList::GetBack() noexcept
{
	_STL_ASSERT(m_size != 0, "GetBackElement called on empty list");
	return m_last->m_data;
}

const std::string& StringList::GetBack() const noexcept
{
	_STL_ASSERT(m_size != 0, "GetBackElement called on empty list");
	return m_last->m_data;
}

std::string& StringList::GetFront() noexcept
{
	_STL_ASSERT(m_size != 0, "GetFrontElement called on empty list");
	return m_first->m_data;
}

const std::string& StringList::GetFront() const noexcept
{
	_STL_ASSERT(m_size != 0, "GetFrontElement called on empty list");
	return m_first->m_data;
}

size_t StringList::GetSize() const noexcept
{
	return m_size;
}

StringList::Iterator StringList::begin() noexcept
{
	return Iterator(m_first.get(), this);
}

StringList::Iterator StringList::end() noexcept
{
	return Iterator(nullptr, this);
}

StringList::ConstIterator StringList::begin() const noexcept
{
	return ConstIterator(m_first.get(), this);
}

StringList::ConstIterator StringList::end() const noexcept
{
	return ConstIterator(nullptr, this);
}

StringList::ConstIterator StringList::cbegin() const noexcept
{
	return begin();
}

StringList::ConstIterator StringList::cend() const noexcept
{
	return end();
}

StringList::ReverseIterator StringList::rbegin() noexcept
{
	return ReverseIterator(end());
}

StringList::ReverseIterator StringList::rend() noexcept
{
	return ReverseIterator(begin());
}

StringList::ConstReverseIterator StringList::rbegin() const noexcept
{
	return ConstReverseIterator(end());
}

StringList::ConstReverseIterator StringList::rend() const noexcept
{
	return ConstReverseIterator(begin());
}

StringList::ConstReverseIterator StringList::crbegin() const noexcept
{
	return rbegin();
}

StringList::ConstReverseIterator StringList::crend() const noexcept
{
	return rend();
}

#pragma endregion StringList

#pragma region StringListConstIterator

StringListConstIterator::StringListConstIterator() noexcept
	: m_ptr(nullptr)
	, m_container(nullptr)
{
}

StringListConstIterator::StringListConstIterator(NodePtr ptr, const Container* container) noexcept
	: m_ptr(ptr)
	, m_container(container)
{
}

StringListConstIterator::reference StringListConstIterator::operator*() const noexcept
{
	_STL_ASSERT(m_container, "Cannot dereference value-initialized list iterator");
	_STL_ASSERT(m_ptr != nullptr, "Cannot dereference end list iterator");
	return m_ptr->m_data;
}

StringListConstIterator::pointer StringListConstIterator::operator->() const noexcept
{
	return &(**this);
}

StringListConstIterator& StringListConstIterator::operator++() noexcept
{
	_STL_ASSERT(m_container, "Cannot increment value-initialized list iterator");
	_STL_ASSERT(m_ptr != nullptr, "Cannot increment end list iterator");
	this->m_ptr = this->m_ptr->m_next.get();
	return *this;
}

StringListConstIterator StringListConstIterator::operator++(int) noexcept
{
	StringListConstIterator tmp{ *this };
	++*this;
	return tmp;
}

StringListConstIterator& StringListConstIterator::operator--() noexcept
{
	_STL_ASSERT(m_container, "Cannot decrement value-initialized list iterator");
	_STL_ASSERT(m_ptr != m_container->m_first.get(), "Cannot decrement begin list iterator");
	if (m_ptr == nullptr)
	{
		this->m_ptr = m_container->m_last;
	}
	else
	{
		this->m_ptr = this->m_ptr->m_prev;
	}
	return *this;
}

StringListConstIterator StringListConstIterator::operator--(int) noexcept
{
	StringListConstIterator tmp{ *this };
	--*this;
	return tmp;
}

bool operator==(const StringListConstIterator& left, const StringListConstIterator& right) noexcept
{
	_STL_ASSERT(left.m_container == right.m_container, "List iterators incompatible");
	return left.m_ptr == right.m_ptr;
}

bool operator!=(const StringListConstIterator& left, const StringListConstIterator& right) noexcept
{
	return !(left == right);
}

#pragma endregion StringListConstIterator

#pragma region StringListIterator

StringListIterator::StringListIterator() noexcept
	: StringListConstIterator(nullptr, nullptr)
{
}

StringListIterator::StringListIterator(NodePtr ptr, const Container* container) noexcept
	: StringListConstIterator(ptr, container)
{
}

StringListIterator::reference StringListIterator::operator*() const noexcept
{
	return const_cast<reference>(MyBase::operator*());
}

StringListIterator::pointer StringListIterator::operator->() const noexcept
{
	return &(**this);
}

StringListIterator& StringListIterator::operator++() noexcept
{
	MyBase::operator++();
	return *this;
}

StringListIterator StringListIterator::operator++(int) noexcept
{
	StringListIterator tmp{ *this };
	MyBase::operator++();
	return tmp;
}

StringListIterator& StringListIterator::operator--() noexcept
{
	MyBase::operator--();
	return *this;
}

StringListIterator StringListIterator::operator--(int) noexcept
{
	StringListIterator tmp{ *this };
	MyBase::operator--();
	return tmp;
}

#pragma endregion StringListIterator