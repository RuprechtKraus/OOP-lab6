#pragma once
#include <memory>
#include <string>

class StringList
{
	friend class StringListIterator;
	friend class StringListConstIterator;

	class Node
	{
	public:
		Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next);
		~Node() noexcept;

		std::string m_data;
		Node* m_prev{};
		std::unique_ptr<Node> m_next;
	};

public:
	using Iterator = StringListIterator;
	using ConstIterator = StringListConstIterator;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
	using ValueType = std::string;
	using Reference = ValueType&;
	using ConstReference = const ValueType&;

	~StringList() noexcept;

	void PushBack(const std::string& str);
	void PushFront(const std::string& str);
	void Clear() noexcept;
	bool IsEmpty() const noexcept;
	Reference GetBackElement() noexcept;
	ConstReference GetBackElement() const noexcept;
	Reference GetFrontElement() noexcept;
	ConstReference GetFrontElement() const noexcept;
	size_t GetSize() const noexcept;

	Iterator begin() noexcept;
	Iterator end() noexcept;
	ConstIterator begin() const noexcept;
	ConstIterator end() const noexcept;
	ConstIterator cbegin() const noexcept;
	ConstIterator cend() const noexcept;
	ReverseIterator rbegin() noexcept;
	ReverseIterator rend() noexcept;
	ConstReverseIterator rbegin() const noexcept;
	ConstReverseIterator rend() const noexcept;
	ConstReverseIterator crbegin() const noexcept;
	ConstReverseIterator crend() const noexcept;

private:
	size_t m_size{};
	Node* m_last{};
	std::unique_ptr<Node> m_first;
};

class StringListConstIterator
{
	friend class StringList;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = std::string;
	using pointer = const value_type*;
	using reference = const value_type&;
	using Container = StringList;
	using NodePtr = Container::Node*;
	
	StringListConstIterator() noexcept;

	reference operator*() const noexcept;
	pointer operator->() const noexcept;

	StringListConstIterator& operator++() noexcept;
	StringListConstIterator operator++(int) noexcept;
	StringListConstIterator& operator--() noexcept;
	StringListConstIterator operator--(int) noexcept;

	friend bool operator==(const StringListConstIterator& left, const StringListConstIterator& right) noexcept;
	friend bool operator!=(const StringListConstIterator& left, const StringListConstIterator& right) noexcept;

protected:
	StringListConstIterator(NodePtr ptr, const Container* container) noexcept;

	NodePtr m_ptr;
	const Container* m_container;
};

class StringListIterator : public StringListConstIterator
{
	friend class StringList;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = std::string;
	using pointer = value_type*;
	using reference = value_type&;
	using Container = StringList;
	using MyBase = StringListConstIterator;

	StringListIterator() noexcept;

	reference operator*() const noexcept;
	pointer operator->() const noexcept;

	StringListIterator& operator++() noexcept;
	StringListIterator operator++(int) noexcept;
	StringListIterator& operator--() noexcept;
	StringListIterator operator--(int) noexcept;

private:
	StringListIterator(NodePtr ptr, const Container* container) noexcept;
};