#include "StringList.h"
#include <iostream>

StringList::Node::Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next)
	: m_data(data)
	, m_prev(prev)
	, m_next(std::move(next))
{
	std::cout << "Node with value \"" << m_data << "\" has been created" << std::endl;
}

StringList::Node::~Node()
{
	std::cout << "Node with value \"" << m_data << "\" has been destroyed" << std::endl;
}

void StringList::PushBack(const std::string& str)
{
	auto node{ std::make_unique<Node>(str, m_last, nullptr) };
	Node* newLast{ node.get() };

	if (m_first)
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
	/*auto node{ std::make_unique<Node>(str, nullptr, m_first) };
	m_first = std::move(node);

	if (m_last)
	{

	}*/
}

void StringList::Clear()
{
	throw std::logic_error("Method is not implemented");
}

bool StringList::IsEmpty() const noexcept
{
	return !m_first.get();
}

std::string& StringList::GetBackElement()
{
	_STL_ASSERT(m_size != 0, "GetBackElement called on empty list");
	return m_last->m_data;
}

const std::string& StringList::GetBackElement() const
{
	_STL_ASSERT(m_size != 0, "GetBackElement called on empty list");
	return m_last->m_data;
}

std::string& StringList::GetFrontElement()
{
	_STL_ASSERT(m_size != 0, "GetFrontElement called on empty list");
	return m_first->m_data;
}

const std::string& StringList::GetFrontElement() const
{
	_STL_ASSERT(m_size != 0, "GetFrontElement called on empty list");
	return m_first->m_data;
}

size_t StringList::GetSize() const noexcept
{
	return m_size;
}