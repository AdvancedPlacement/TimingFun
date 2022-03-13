#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <list>
#include <cstring>
#include "ListNode.h"
using namespace std;






namespace data_structures
{
	//template <class K, V> for the k and V, how do I add this like T for template <class T>

	class HashTable {
	private:
		static const int HashGroups = 10;
		list<pair<int, string>> table[HashGroups]; // list 1 = index 0, list 2 index 1, etc

	public:
		bool isEmpty() const;
		int hashFunction(int key);
		//void I(int K key, V value);
		string searchTable(int key); //K key?
		void printTable();
		void Insert(int key, string value);
		void removeItem(int key);

		//void Insert(K key, V value);
		//void setHash(K key); // Extra credit if you do with a function pointer for this
		//V operator [] (K key);
		//void Delete(K key);
		//void Traverse(V value); // traverse all values from the given value
	};

	bool HashTable::isEmpty() const {
		int sum{};
		for (int i{}; i < HashGroups; i++) {
			sum += table[i].size();

		}
		if (!sum) {
			return true;
		}
		//https://www.youtube.com/watch?v=2_3fR-k-LzI
		return false;
	}

	int HashTable::hashFunction(int key) {
		return key % HashGroups; //key is 905, in return this function will spit out 5
	}
	void HashTable::Insert(int key, string value)
	{
		int HashValue = hashFunction(key);
		auto& cell = table[HashValue];
		auto bItr = begin(cell);
		bool keyExists = false;
		for (; bItr != end(cell); bItr++) {
			if (bItr->first == key) {
				keyExists = true;
				bItr->second = value;
				cout << "warning: key exists value replaced." << endl;
				break;
			}
		}
		if (!keyExists) {
			cell.emplace_back(key, value);
		}
		return;
	}

	void HashTable::removeItem(int key) {
		{
			int HashValue = hashFunction(key);
			auto& cell = table[HashValue];
			auto bItr = begin(cell);
			bool keyExists = false;
			for (; bItr != end(cell); bItr++) {
				if (bItr->first == key) {
					keyExists = true;
					bItr = cell.erase(bItr); //ERASE, returns iterator to next iterator of bItr. Ie  2->3
					cout << "info: item removed." << endl;
					break;
				}
			}
			if (!keyExists) {
				cout << "WARNING: item not found." << endl;
			}
			return;
		}
	}
	void HashTable::printTable() {
		for (int i{}; i < HashGroups; i++) {
			if (table[i].size() == 0) continue;

			auto bItr = table[i].begin();
			for (; bItr != table[i].end(); bItr++) {
				cout << "info: key: " << bItr->first << " Value: " << bItr->second << endl;
			}
			return;
		}

	}



	template <class T>
	class LinkedList final
	{
	public:
		LinkedList() = default;
		LinkedList(const LinkedList& copy);
		LinkedList(LinkedList&& copy) noexcept;
		~LinkedList();

		LinkedList& operator=(const LinkedList& rhs);
		LinkedList& operator=(LinkedList&& rhs) noexcept;

		explicit operator bool() const;

		void Append(const T& data);
		void Prepend(const T& data);
		void RemoveLast();
		void RemoveFirst();
		void Extract(const T& data);
		void InsertAfter(const T& data, const T& after);
		void InsertBefore(const T& data, const T& before);
		void Clear() noexcept;
		T& Last();
		T Last() const;
		T& First();
		T First() const;
		ListNode<T>* Head() const noexcept;
		ListNode<T>* Tail() const noexcept;
		bool Empty() const noexcept;
		size_t Size() const noexcept;

		T ListElement(int index);

		bool operator==(const LinkedList<T>& rhs) const noexcept;


	private:
		ListNode<T>* m_head = nullptr;
		ListNode<T>* m_tail = nullptr;
		size_t m_count = 0;
	};


	template <class T>
	LinkedList<T>::~LinkedList()
	{
		auto traverse = m_head;

		while (traverse != nullptr)
		{
			auto temp = traverse->Next();
			delete traverse;
			traverse = temp;
		}
		m_head = nullptr;
		m_tail = nullptr;
	}

	template <class T>
	LinkedList<T>::LinkedList(const LinkedList& copy)
	{
		*this = copy;
	}

	template <class T>
	LinkedList<T>& LinkedList<T>::operator=(const LinkedList& rhs)
	{
		if (this != &rhs)
		{

			Clear();
			auto traverse = rhs.Head();
			for (traverse; traverse != nullptr; traverse = traverse->Next())
			{
				Append(traverse->Value());
			}

		}
		return *this;
	}

	template <class T>
	LinkedList<T>::LinkedList(LinkedList&& copy) noexcept
	{
		*this = std::move(copy);
	}

	template <class T>
	LinkedList<T>& LinkedList<T>::operator=(LinkedList&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			m_count = rhs.m_count;
			m_head = rhs.m_head;
			m_tail = rhs.m_tail;

			rhs.m_head = nullptr;
			rhs.m_tail = nullptr;
		}
		return *this;
	}

	template <class T>
	LinkedList<T>::operator bool() const
	{
		return !Empty();
	}

	template <class T>
	void LinkedList<T>::Append(const T& data)
	{
		auto new_node = new ListNode<T>(data, nullptr, m_tail);
		if (m_head == nullptr)
		{
			m_head = new_node;
		}
		else
		{
			m_tail->Next(new_node);
		}
		m_tail = new_node;
		m_count++;
	}

	template <class T>
	void LinkedList<T>::Prepend(const T& data)
	{
		auto new_node = new ListNode<T>(data, m_head, nullptr);
		if (m_head == nullptr)
		{
			m_tail = new_node;
		}
		else
		{
			m_head->Previous(new_node);
		}
		m_head = new_node;
		m_count++;
	}

	template <class T>
	void LinkedList<T>::RemoveLast()
	{
		auto temp = m_tail;
		m_tail = m_tail->Previous();
		delete temp;
		m_tail->Next(nullptr);
		m_count--;
	}

	template <class T>
	void LinkedList<T>::RemoveFirst()
	{
		auto temp = m_head;
		m_head = m_head->Next();
		delete temp;
		m_count--;
	}

	template <class T>
	void LinkedList<T>::Extract(const T& data) //test
	{
		for (auto travel = m_head; travel != nullptr; travel = travel->Next()) {
			if (travel->Value() == data)
			{
				if (travel == m_head)
				{
					auto temp = m_head->Next();
					delete m_head;
					m_head = temp;
					m_count--;
					return;
				}
				if (travel == m_tail)
				{
					auto temp = m_tail->Previous();
					delete m_tail;
					m_tail = temp;
					m_count--;
					return;
				}
				auto temp = travel->Previous();
				temp->Next(travel->Next());
				delete travel;
				m_count--;
				return;
			}
		}
	}

	template <class T>
	void LinkedList<T>::InsertAfter(const T& data, const T& after)
	{
		auto current = m_head;
		while (current != nullptr) {
			if (current->Value() == after)
			{
				auto new_node = new ListNode<T>(data, current->Next(), current);
				current->Next(new_node);
				current->Next()->Previous(new_node);
				m_count++;
				break;
			}
			current = current->Next();
		}
	}

	template <class T>
	void LinkedList<T>::InsertBefore(const T& data, const T& before)
	{
		auto current = m_head;


		while (current != nullptr) {
			if (current->Value() == before)
			{
				auto new_node = new ListNode<T>(data, current, current->Previous());
				current->Previous()->Next(new_node);
				current->Previous(new_node);
				m_count++;
				break;
			}
			current = current->Next();
		}
	}

	template <class T>
	void LinkedList<T>::Clear() noexcept
	{
		while (m_head != nullptr)
		{
			auto temp = m_head;
			m_head = m_head->Next();
			delete temp;
		}
		m_count = 0;
	}

	template <class T>
	T& LinkedList<T>::Last()
	{
		return m_tail->Value();
	}

	template <class T>
	T LinkedList<T>::Last() const
	{
		return m_tail->Value();
	}

	template <class T>
	T& LinkedList<T>::First()
	{
		return m_head->Value();
	}

	template <class T>
	T LinkedList<T>::First() const
	{
		return m_head->Value();
	}

	template <class T>
	ListNode<T>* LinkedList<T>::Head() const noexcept
	{
		return m_head;
	}

	template <class T>
	ListNode<T>* LinkedList<T>::Tail() const noexcept
	{
		return m_tail;
	}

	template <class T>
	bool LinkedList<T>::Empty() const noexcept
	{
		return m_count == 0;
	}

	template <class T>
	size_t LinkedList<T>::Size() const noexcept
	{
		return m_count;
	}

	template <class T>
	bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const noexcept
	{
		auto travel = m_head;
		auto rhs_travel = rhs.m_head;
		if (m_count != rhs.m_count)
		{
			return false;
		}
		while (travel != nullptr || rhs_travel != nullptr)
		{
			if (travel->Value() != rhs_travel->Value() || m_count != rhs.m_count)
			{
				return false;
			}
			travel = travel->Next();
			rhs_travel = rhs_travel->Next();
		}
		return true;
	}

	template <class T>
	T LinkedList<T>::ListElement(int index)
	{
		auto current = m_head;
		int count = 0;

		while (current != nullptr) {
			if (count == index)
				return current->Value();
			count++;
			current = current->Next();
		}
		return 0;
	}
}
#endif