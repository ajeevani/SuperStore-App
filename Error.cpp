#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Error.h"

using namespace std;

namespace superstore
{
	Error::Error()
	{
		m_message = nullptr;
	}
	Error::Error(const char* mess)
	{
		m_message = nullptr;
		*this = mess;
	}
	Error::Error(Error& err)
	{
		m_message = nullptr;
		*this = err;
	}
	Error& Error::operator=(Error& err)
	{
		if (err.m_message != nullptr)
		{
			delete[] m_message;
			m_message = new char[strlen(err.m_message) + 1];
			strcpy(m_message, err.m_message);
		}

		return *this;
	}
	Error::~Error()
	{
		delete[] m_message;
	}
	Error& Error::operator=(const char* mess)
	{
		if (mess != nullptr && mess[0] != '\0')
		{
			m_message = new char[strlen(mess) + 1];
			strcpy(m_message, mess);
		}
		return *this;
	}
	Error::operator bool() const
	{
		return m_message != nullptr;
	}
	Error& Error::clear()
	{
		delete[] m_message;
		m_message = nullptr;

		return *this;
	}
	std::ostream& Error::operator<<(std::ostream& os)
	{
		if(*this)
		{
			os << m_message;
		}

		return os;
	}
	std::ostream& operator<<(std::ostream& os, Error& err)
	{
		return err.operator<<(os);
	}
}