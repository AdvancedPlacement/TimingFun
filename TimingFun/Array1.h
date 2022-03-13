#ifndef ARRAY_H
#define ARRAY_H
#include "Exception.h"
//#include "Array.h"
template <typename T>
class Array
{
public:
	// Manager Functions
	Array(); // Default ctor
	Array(int length, int start_index = 0); // 1 or 2 argument ctor using
	//default argument
	Array(const Array<T>& copy); // Copy ctor
	Array(Array<T>&& copy); // Move ctor
	Array& operator = (const Array<T>& rhs);
	// Array(const Array<T>& copy);
	// Copy assignment operator
	Array& operator = (Array<T>&& rhs); // Move assignment operator
	~Array();
	T& operator[](int index);
	int getStartIndex() const;
	int getLength() const;
	void setStartIndex(int start_index);
	void setLength(int newLength);
private:
	int m_start_index;
	int m_length;
	T* m_data;
};
template <typename T>
Array<T>::Array() : m_data(nullptr), m_length(0), m_start_index(0)  // Always use base member initialization when you can
{ }
template <typename T>
Array<T>::Array(int length, int start_index) : m_data(nullptr), m_length(0), m_start_index(start_index)
{
	// Up to the producer to insure valid data
	if (length < 0)
	{
		//throw Exception("Cannot have a negative length");
		throw Exception();
	}

	//throw Exception("Cannot have a negative length");
	m_length = length; //is this supposed to set m_length to length if length < 0? Might be the error.
	m_data = new T[m_length];
}
template <typename T>
Array<T>::Array(const Array<T>& copy) : m_data(nullptr), m_start_index(copy.m_start_index), m_length(copy.m_length)
{
	if (copy.m_length >= 0) {
		m_data = new T[copy.m_length];
		if (copy.m_data != nullptr)
			for (int i = 0; i < m_length; ++i)
				m_data[i] = copy.m_data[i];
	}
	*this = copy; //let's see
}

template <typename T>
Array<T>::Array(Array<T>&& copy) : m_data(copy.m_data), m_length(copy.m_length), m_start_index(copy.m_start_index)
{
	// Move ctor: Steal the memory, sever the ties between the memory on the old 
	//object
	//Martha wanted me to comment this out, so I'm not sure if it's this.

	/*if (copy.m_length >= 0) {
		m_data = new T[copy.m_length];
		if (copy.m_data != nullptr)
			for (int i = 0; i < m_length; ++i)
				m_data[i] = copy.m_data[i];
	}*/
	copy.m_data = nullptr;
}
template <typename T>
Array<T>& Array<T>::operator = (const Array<T>& rhs)
{
	if (this != &rhs) // Check for self assignment
	{
		delete[] m_data;
		//	m_data = 
		T* new_data{ nullptr };
		//m_data = new_data; //mmmm
		m_data = new T[rhs.m_length];
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;

		for (int i = 0; i < m_length; ++i)
			m_data[i] = rhs.m_data[i];
		/*delete[] m_data;
		m_data = nullptr;
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;*/
		//if (rhs.m_data != nullptr)
		//{
		//	m_data = new T[rhs.m_length];
		//	// Using the newer new will throw an error if fails
		//	
		//}
	}
	return *this; // Needed for function chaining a = b = c
}
//template<typename T>
////inline Array<T>::operator Array& operator=(const Array<T>&& rhs)
////{
////}
template <typename T>
Array<T>& Array<T>::operator = (Array<T>&& rhs)
{
	if (this != &rhs) // Check for self assignment
	{
		delete[] m_data; // Purge the lhs
		m_data = rhs.m_data;
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;
		rhs.m_data = nullptr;
	}
	return *this; // Needed for function chaining a = b = c
}
template <typename T>
Array<T>::~Array()
{
	delete[] m_data;
	// Always return data members back to their default state
	m_data = nullptr;
	m_length = 0;
	m_start_index = 0;
}
template <typename T>
T& Array<T>::operator[](int index)
{
	if (index < m_start_index || index >= m_length)
		throw Exception();
	return m_data[index - m_start_index];
}
template <typename T>
int Array<T>::getStartIndex() const
{
	return m_start_index;
}
template <typename T>
int Array<T>::getLength() const
{
	return m_length;
}
template <typename T>
void Array<T>::setStartIndex(int start_index)
{
	m_start_index = start_index;
}
template <typename T>
void Array<T>::setLength(int newLength)
{
	if (newLength < 0) //try and catch instead of if?
		throw Exception();

	int shorter = (m_length < newLength ? m_length : newLength);


	T* newData = new T[newLength];
	for (int i = 0; i < shorter; ++i)
	{
		newData[i] = m_data[i];
	}
	delete[] m_data;
	m_data = newData;
	m_length = newLength;
}
#endif
