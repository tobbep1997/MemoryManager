#pragma once
#include <sal.h>
#include <iostream>

void PrintProgress(int i, int max)
{
	if ((i + 1) % 1000 == 0)
		std::cout << "\r" << (static_cast<float>(i + 1) / static_cast<float>(max)) * 100.0f << "%";
}

#pragma region Raw
template <typename T>
class LinkedListRaw
{
private:

	struct Node
	{
		T data;
		Node * next = nullptr;

		Node(_In_opt_ const T & DATA = 0, _In_ Node * NEXT = nullptr)
		{
			data = DATA;
			next = NEXT;
		}

	};


public:
	LinkedListRaw() = default;
	~LinkedListRaw() = default;

	Node * m_list = nullptr;
	
	void Insert(_In_opt_ const T & data = 0);
	const T & GetAt(_In_opt_ const unsigned int & index);
	void Test(_In_opt_ std::vector<double> * readTime, const unsigned int & testSize);
	   
	void PrintAllData();

};
template <typename T>
inline void LinkedListRaw<T>::Insert(_In_opt_ const T & data)
{
	m_list = new Node(data, m_list);	
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

template <typename T>
void LinkedListRaw<T>::Test(std::vector<double>* readTime, const unsigned& testSize)
{
	DeltaTimer timer;
	   
	unsigned int counter = 0;
	Node * node = m_list;
	while (node != nullptr && counter < testSize)
	{
		PrintProgress(counter, testSize);

		timer.Init();

		node = node->next;
		counter++;

		const double t = timer.GetDeltaTimeInSeconds();
		readTime->push_back(t);
	}

	
}
#pragma endregion 

#pragma region Smart
template <typename T>
class LinkedListSmart
{
private:

	struct Node
	{
		T data;
		std::shared_ptr<Node> next = nullptr;

		Node(_In_opt_ const T & DATA = 0, _In_opt_ std::shared_ptr<Node> NEXT = nullptr)
		{
			data = DATA;
			next = NEXT;
		}

	};


public:
	LinkedListSmart() = default;
	~LinkedListSmart() = default;

	std::shared_ptr<Node> m_list = nullptr;

	void Insert(_In_opt_ const T & data = 0);
	const T & GetAt(_In_opt_ const unsigned int & index);
	void Test(_In_opt_ std::vector<double> * readTime, const unsigned int & testSize);


	void PrintAllData();

};

template <typename T>
inline void LinkedListSmart<T>::Insert(_In_opt_ const T& data)
{
	m_list = std::make_shared<Node>(data, m_list);
	return;
	if (m_list == nullptr)
	{

		
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

template <typename T>
inline void LinkedListSmart<T>::PrintAllData()
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

template <typename T>
const T& LinkedListSmart<T>::GetAt(const unsigned& index)
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

template <typename T>
void LinkedListSmart<T>::Test(std::vector<double>* readTime, const unsigned& testSize)
{
	DeltaTimer timer;

	unsigned int counter = 0;
	Node * node = m_list.get();
	while (node != nullptr && counter < testSize)
	{
		PrintProgress(counter, testSize);

		timer.Init();

		node = node->next.get();
		counter++;

		const double t = timer.GetDeltaTimeInSeconds();
		readTime->push_back(t);
	}
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
