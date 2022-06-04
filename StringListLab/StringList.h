#pragma once
#include <memory>
#include <string>

class StringList
{
	class Node
	{
	public:
		Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next);
		~Node();

		std::string m_data;
		Node* m_prev;
		std::unique_ptr<Node> m_next;
	};

public:
	using Reference = std::string&;
	using ConstReference = const std::string&;

	void PushBack(const std::string& str);
	void PushFront(const std::string& str);
	void Clear();
	bool IsEmpty() const noexcept;
	Reference GetBackElement();
	ConstReference GetBackElement() const;
	Reference GetFrontElement();
	ConstReference GetFrontElement() const;
	size_t GetSize() const noexcept;

private:
	size_t m_size{};
	Node* m_last;
	std::unique_ptr<Node> m_first;
};