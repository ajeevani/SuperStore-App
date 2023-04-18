#ifndef SDDS_ERROR_H_
#define SDDS_ERROR_H_
#include<iostream>

namespace superstore
{
	class Error
	{
		char* m_message;
	public:
		Error();
		Error(const char* mess);
		Error(Error& err);
		Error& operator=(Error& err);
		~Error();
		Error& operator=(const char* mess);
		operator bool() const;
		Error& clear();
		std::ostream& operator<<(std::ostream& os);
	};
	std::ostream& operator<<(std::ostream& os, Error& err);
}

#endif // !1
