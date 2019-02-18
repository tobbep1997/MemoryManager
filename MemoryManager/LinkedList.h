#pragma once
#include <sal.h>
#include <iostream>

class LinkedListRaw
{
private:

	struct Node
	{
		int data;
		Node * next = nullptr;

		Node(_In_opt_ const int & DATA = 0)
		{
			data = DATA;
			next = nullptr;
		}

	};


public:
	LinkedListRaw() = default;
	~LinkedListRaw() = default;

	Node * m_list = nullptr;
	
	void Insert(_In_opt_ const int & data = 0);
	void PrintAllData();

};
inline void LinkedListRaw::Insert(_In_opt_ const int & data)
{
	if (m_list == nullptr)
	{
		m_list = new Node(data);
	}
	else
	{
		if (m_list->next == nullptr)
		{
			m_list->next = new Node(data);
		}
		else
		{
			Node * node = nullptr;
			Node * nextNode = m_list->next;
			while (nextNode != nullptr)
			{
				node = nextNode;
				nextNode = nextNode->next;
				
			}
			node->next = new Node(data);
		}
	}
}
inline void LinkedListRaw::PrintAllData()
{
	int counter = 0;
	Node * node = m_list;
	while (node != nullptr)
	{
		std::cout << counter << ": data" << node->data << std::endl;
		node = node->next;
		counter++;
	}
}

class LinkedListSmart
{
private:

	struct Node
	{
		int data;
		std::shared_ptr<Node> next = nullptr;

		Node(_In_opt_ const int & DATA = 0)
		{
			data = DATA;
			next = nullptr;
		}

	};


public:
	LinkedListSmart() = default;
	~LinkedListSmart() = default;

	std::shared_ptr<Node> m_list = nullptr;

	void Insert(_In_opt_ const int & data = 0);
	void PrintAllData();

};

inline void LinkedListSmart::Insert(_In_opt_ const int& data)
{
	if (m_list == nullptr)
	{
		m_list = std::make_shared<Node>(data);
	}
	else
	{
		if (m_list->next == nullptr)
		{
			m_list->next = std::make_shared<Node>(data);
		}
		else
		{
			std::shared_ptr<Node> node = nullptr;
			std::shared_ptr<Node> nextNode = m_list.get()->next;
			while (nextNode != nullptr)
			{
				node = nextNode;
				nextNode = nextNode->next;

			}
			node->next = std::make_shared<Node>(data);
		}
	}
}

inline void LinkedListSmart::PrintAllData()
{
	int counter = 0;
	std::shared_ptr<Node> node = m_list;
	while (node != nullptr)
	{
		std::cout << counter << ": data" << node->data << std::endl;
		node = node->next;
		counter++;
	}
}
