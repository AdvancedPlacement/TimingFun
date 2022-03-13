#ifndef NODE_HPP
#define NODE_HPP

#include <algorithm>

namespace data_structures
{
	template <class T>
	class Node
	{
	public:
		explicit Node() = delete;
		Node(const Node& copy);
		explicit Node(const T& data);

		Node<T>& operator=(const Node& copy);

		Node(Node&& copy) noexcept;
		Node<T>& operator=(Node&& copy) noexcept;

		virtual ~Node() = default;

		T& Value() noexcept;
		T Value() const noexcept;
		void Value(const T& data);
	private:
		T value_{};
	};


	template <class T>
	Node<T>::Node(const Node& copy)
	{
		*this = copy;
	}

	template <class T>
	Node<T>::Node(const T& data)
		:value_(data)
	{}

	template <class T>
	Node<T>& Node<T>::operator=(const Node& copy)
	{
		if (this != &copy)
		{
			value_ = copy.value_;
		}
		return *this;
	}

	template <class T>
	Node<T>::Node(Node&& copy) noexcept
	{
		*this = std::move(copy);
	}

	template <class T>
	Node<T>& Node<T>::operator=(Node&& copy) noexcept
	{
		if (this != &copy)
		{
			value_ = copy.value_;
		}
		return *this;
	}

	template <class T>
	T& Node<T>::Value() noexcept
	{
		return value_;
	}

	template <class T>
	T Node<T>::Value() const noexcept
	{
		return value_;
	}

	template <class T>
	void Node<T>::Value(const T& data)
	{
		value_ = data;
	}
}
#endif