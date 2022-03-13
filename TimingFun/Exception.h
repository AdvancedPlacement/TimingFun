#pragma once
#pragma warning(disable : 4996)


#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <ostream>
#include <cstring> 
#include <exception>

using std::ostream;

class Exception : public std::exception {
private:
	char* m_msg;
public:
	Exception() : m_msg(nullptr) {};
	~Exception();
	Exception(const char* msg);
	Exception(Exception& copy);
	Exception(Exception&& copy) noexcept;
	Exception& operator =(const Exception& rhs);
	Exception& operator =(Exception&& rhs) noexcept;
	const char* getMessage();
	void setMessage(const char* msg);
	friend ostream& operator <<(ostream& stream, const Exception& except);

	//	//defs are new

	//
		//void setMessage(const char* msg) { //BOTH OF THESE ALREADY DEFINED??
	//		delete[] m_msg;
	//		m_msg = new char[strlen(msg) + 1];
	//		strcpy_s(m_msg, strlen(msg) + 1, msg);
	//	}
	//};

};

Exception::~Exception() {
	if (m_msg != nullptr)
		delete[] m_msg;
}

Exception::Exception(const char* msg) {
	//m_msg = new char[strlen(msg) + 1]();
	//m_msg = msg;
}

Exception::Exception(Exception& copy) :Exception(copy.m_msg) {
}

Exception::Exception(Exception&& copy) noexcept {
	m_msg = copy.m_msg;
	copy.m_msg = nullptr;
}

Exception& Exception::operator=(const Exception& rhs) {
	m_msg = new char[strlen(rhs.m_msg) + 1]();
	strcpy(m_msg, rhs.m_msg);
	return *this;
}

Exception& Exception::operator= (Exception&& rhs) noexcept {
	m_msg = rhs.m_msg;
	rhs.m_msg = nullptr;
	return *this;
}

const char* Exception::getMessage() {
	return m_msg;
};  // useless semicolon but we'll leave it here anyway

void Exception::setMessage(const char* msg) {
	/*m_msg = new char[strlen(msg) + 1]();
	strcpy(m_msg, msg);*/
}

ostream& operator<<(ostream& stream, const Exception& except) {
	stream << except.m_msg;
	return stream;
}

#endif
