#pragma once
#include <sal.h>
#include <iostream>

#pragma region Raw
template <typename T>
class LinkedListRaw
{
private:

	struct Node
	{
		T data;
		Node * next = nullptr;

		Node(_In_opt_ const T & DATA = 0)
		{
			data = DATA;
			next = nullptr;
		}

	};


public:
	LinkedListRaw() = default;
	~LinkedListRaw() = default;

	Node * m_list = nullptr;
	
	void Insert(_In_opt_ const T & data = 0);
	const T & GetAt(_In_opt_ const unsigned int & index);
	   
	void PrintAllData();

};
template <typename T>
inline void LinkedListRaw<T>::Insert(_In_opt_ const T & data)
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
template <typename T>
inline void LinkedListRaw<T>::PrintAllData()
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
template <typename T>
inline const T& LinkedListRaw<T>::GetAt(const unsigned& index)
{
	unsigned int counter = 0;
	Node * node = m_list;
	while (node != nullptr && counter < index)
	{
		node = node->next;
		counter++;
	}
	return node->data;
}
#pragma endregion 

#pragma region Smart
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
	const int & GetAt(_In_opt_ const unsigned int & index);
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

const int& LinkedListSmart::GetAt(const unsigned& index)
{
	unsigned int counter = 0;
	Node * node = m_list.get();
	while (node != nullptr && counter < index)
	{
		node = node->next.get();
		counter++;
	}
	return node->data;
}
#pragma endregion 

class LinkedListOwnHeap
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

	MemoryStack m_meme;

public:
	LinkedListOwnHeap()
	{
		m_meme.Init();
	};
	~LinkedListOwnHeap() = default;

	Node * m_list = nullptr;

	void Insert(_In_opt_ const int & data = 0);
	void PrintAllData();
};

inline void LinkedListOwnHeap::Insert(const int& data)
{
	if (m_list == nullptr)
	{
		m_list = m_meme.AllocData<Node>();
		m_list->data = data;
		m_list->next = nullptr;
	}
	else
	{
		if (m_list->next == nullptr)
		{
			m_list->next = m_meme.AllocData<Node>();
			m_list->next->next = nullptr;
			m_list->next->data = data;
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
			node->next = m_meme.AllocData<Node>();
			node->next->next = nullptr;
			node->next->data = data;
		}
	}
}

inline void LinkedListOwnHeap::PrintAllData()
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
