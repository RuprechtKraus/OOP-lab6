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
}

void StringList::PushFront(const std::string& str)
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
}

void StringList::Clear() noexcept
{
	while (m_first)
	{
		m_first = std::move(m_first->m_next);
	}

	m_size = 0;
}

bool StringList::IsEmpty() const noexcept
{
	return !m_first.get();
}

std::string& StringList::GetBackElement() noexcept
{
	_STL_ASSERT(m_size != 0, "GetBackElement called on empty list");
	return m_last->m_data;
}

const std::string& StringList::GetBackElement() const noexcept
{
	_STL_ASSERT(m_size != 0, "GetBackElement called on empty list");
	return m_last->m_data;
}

std::string& StringList::GetFrontElement() noexcept
{
	_STL_ASSERT(m_size != 0, "GetFrontElement called on empty list");
	return m_first->m_data;
}

const std::string& StringList::GetFrontElement() const noexcept
{
	_STL_ASSERT(m_size != 0, "GetFrontElement called on empty list");
	return m_first->m_data;
}

size_t StringList::GetSize() const noexcept
{
	return m_size;
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
	throw std::logic_error("Method is not implemented");
}

StringListConstIterator::pointer StringListConstIterator::operator->() const noexcept
{
	throw std::logic_error("Method is not implemented");
}

StringListConstIterator& StringListConstIterator::operator++() noexcept
{
	throw std::logic_error("Method is not implemented");
}

StringListConstIterator StringListConstIterator::operator++(int) noexcept
{
	throw std::logic_error("Method is not implemented");
}

StringListConstIterator& StringListConstIterator::operator--() noexcept
{
	throw std::logic_error("Method is not implemented");
}

StringListConstIterator StringListConstIterator::operator--(int) noexcept
{
	throw std::logic_error("Method is not implemented");
}

bool operator==(const StringListConstIterator& left, const StringListConstIterator& right) noexcept
{
	throw std::logic_error("Method is not implemented");
}

bool operator!=(const StringListConstIterator& left, const StringListConstIterator& right) noexcept
{
	throw std::logic_error("Method is not implemented");
}

#pragma endregion StringListConstIterator