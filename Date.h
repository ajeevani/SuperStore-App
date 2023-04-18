#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include "Error.h"

namespace superstore
{
	class Date
	{
		int m_year;
		int m_month;
		int m_day;
		int m_hour;
		int m_min;
		bool m_dateOnly;
		Error m_err;

		void setEmpty();
		bool validate(int year, int mon = -1, int day = -1, int hour = -1, int min = -1);
	public:
		Date();
		//Date(int year, int mon, int day);
		Date(int year, int mon, int day, int hour = 0, int min = 0);
		bool operator==(Date& date) const;
		bool operator!=(Date& date) const;
		bool operator<(Date& date) const;
		bool operator>(Date& date) const;
		bool operator<=(Date& date) const;
		bool operator>=(Date& date) const;
		Date& dateOnly(bool dateonly);
		operator bool() const;
		Error& error();
		std::ostream& operator<<(std::ostream& os);
		std::istream& operator>>(std::istream& is);
	};
	std::ostream& operator<<(std::ostream& os, Date& date);
	std::istream& operator>>(std::istream& is, Date& date);
}

#endif
