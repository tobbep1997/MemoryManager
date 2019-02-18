#pragma once
#include <sal.h>
#include <iostream>

class LinkedList
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
	LinkedList() = default;
	~LinkedList() = default;

	Node * m_list = nullptr;
	
	void Insert(_In_opt_ const int & data = 0);
	void PrintAllData();

};

inline void LinkedList::Insert(const int & data)
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

inline void LinkedList::PrintAllData()
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

