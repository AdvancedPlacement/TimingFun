#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

#include "Node.h"

namespace data_structures
{
	template <class T>
	class ListNode : public Node<T>
	{
	public:


		ListNode<T>* Next() noexcept;
		ListNode<T>* Next() const noexcept;
		ListNode<T>* Previous() noexcept;
		ListNode<T>* Previous() const noexcept;

		ListNode() = delete;
		explicit ListNode(const T& data, ListNode<T>* next = nullptr, ListNode<T>* previous = nullptr);
		ListNode(const ListNode<T>& copy);
		ListNode<T>& operator=(const ListNode<T>& rhs);

		ListNode(ListNode<T>&& copy) noexcept;
		ListNode<T>& operator=(ListNode<T>&& rhs) noexcept;

		void Next(ListNode<T>* const next) noexcept;
		void Previous(ListNode<T>* const previous) noexcept;

		~ListNode() = default;
	private:
		ListNode<T>* m_next = nullptr;
		ListNode<T>* m_previous = nullptr;
	};

	template <class T>
	ListNode<T>::ListNode(const T& data, ListNode<T>* next, ListNode<T>* previous)
		:Node<T>(data), m_next(next), m_previous(previous)
	{

	}

	template <class T>
	ListNode<T>::ListNode(const ListNode<T>& copy)
	{
		*this = copy;
	}

	template <class T>
	ListNode<T>& ListNode<T>::operator=(const ListNode<T>& rhs)
	{
		if (this != &rhs)
		{
			m_next = rhs.m_next;
			m_previous = rhs.m_previous;
		}
	}

	template <class T>
	ListNode<T>::ListNode(ListNode<T>&& copy) noexcept
	{
		*this = std::move(copy);
	}

	template <class T>
	ListNode<T>& ListNode<T>::operator=(ListNode<T>&& rhs) noexcept
	{
		if (this != &rhs)
		{
			delete m_next;
			delete m_previous;

			m_next = rhs.m_next;
			m_previous = rhs.m_previous;
		}
	}

	template <class T>
	ListNode<T>* ListNode<T>::Next() noexcept
	{
		return m_next;
	}

	template <class T>
	ListNode<T>* ListNode<T>::Next() const noexcept
	{
		return m_next;
	}

	template <class T>
	ListNode<T>* ListNode<T>::Previous() noexcept
	{
		return m_previous;
	}

	template <class T>
	ListNode<T>* ListNode<T>::Previous() const noexcept
	{
		return m_previous;
	}

	template <class T>
	void ListNode<T>::Next(ListNode<T>* const next) noexcept
	{
		m_next = next;
	}

	template <class T>
	void ListNode<T>::Previous(ListNode<T>* const previous) noexcept
	{
		m_previous = previous;
	}
}
#endif