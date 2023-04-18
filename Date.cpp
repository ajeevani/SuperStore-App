#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Date.h"
#include "Utils.h"
#include "POS.h"

using namespace std;

namespace superstore
{
	void Date::setEmpty()
	{
		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_hour = 0;
		m_min = 0;
		m_dateOnly = true;
	}
	bool Date::validate(int year, int mon, int day, int hour, int min)
	{
		bool pass = false;
		if (year >= MIN_YEAR && year <= MAX_YEAR)
		{
			if ((mon >= 1 && mon <= 12) || mon == -1)
			{
				if ((day >= 1 && day <= daysOfMonth(m_year, m_month)) || day == -1)
				{
					if (hour >= -1 && hour <= 23)
					{
						if (min >= -1 && min <= 59)
						{
							pass = true;
						}
						else
						{
							m_err = "Invalid Minute";
						}
					}
					else
					{
						m_err = "Invalid Hour";
					}
				}
				else
				{
					m_err = "Invalid Day";
				}
			}
			else
			{
				m_err = "Invalid Month";
			}
		}
		else
		{
			m_err = "Invalid Year";
		}

		return pass;
	}
	Date::Date()
	{
		setEmpty();
		getSystemDate(m_year, m_month, m_day, m_hour, m_min, m_dateOnly);
	}
	
	Date::Date(int year, int mon, int day, int hour, int min)
	{
		setEmpty();
		if (validate(year))
		{
			m_year = year;
			if (validate(year, mon))
			{
				m_month = mon;
				if (validate(year, mon, day))
				{
					m_day = day;
					if (validate(year, mon, day, hour))
					{
						m_dateOnly = 0;

						m_hour = hour;
						if (validate(year, mon, day, hour, min))
						{
							m_min = min;
							/*if ((m_hour == 0) && (m_min == 0))
							{
								m_dateOnly = 0;
							}
							else
							{
								m_dateOnly = 0;
							}*/
						}
						else
						{
							setEmpty();
						}
					}
					else
					{
						setEmpty();
					}
				}
				else
				{
					setEmpty();
				}
			}
			else
			{
				setEmpty();
			}
		}
	}
	bool Date::operator==(Date& date) const
	{
		if (m_dateOnly)
		{
			return ((m_year == date.m_year) && (m_month == date.m_month) && (m_day == date.m_day));
		}
		else
		{
			return ((m_year == date.m_year) && (m_month == date.m_month) && (m_day == date.m_day) && (m_hour == date.m_hour) && (m_min == date.m_min));
		}
	}
	bool Date::operator!=(Date& date) const
	{
		return !(*this == date);
	}
	bool Date::operator<(Date& date) const
	{ 
		bool pass = 0;
		if (m_year < date.m_year)
		{
			pass = 1;
		}
		else if (m_year == date.m_year)
		{
			if (m_month < date.m_month)
			{
				pass = 1;
			}
			else if (m_month == date.m_month)
			{
				if (m_day < date.m_day)
				{
					pass = 1;
				}
				else if(m_day == date.m_day)
				{
					if (m_hour < date.m_hour)
					{
						pass = 1;
					}
					else if (m_hour == date.m_hour)
					{
						if (m_min < date.m_min)
						{
							pass = 1;
						}
					}
				}
			}
		}
		return pass;
	}
	bool Date::operator>(Date& date) const
	{
		return !(*this < date && *this == date);
	}
	bool Date::operator<=(Date& date) const
	{
		return *this > date;
	}
	bool Date::operator>=(Date& date) const
	{
		return !(*this < date);
	}
	Date& Date::dateOnly(bool dateonly)
	{
		m_dateOnly = dateonly;
		if (m_dateOnly)
		{
			m_hour = 0;
			m_min = 0;
		}

		return *this;
	}
	Date::operator bool() const
	{
		return !m_err;
	}
	Error& Date::error() 
	{
		return m_err;
	}
	ostream& Date::operator<<(ostream& os)
	{
		if (*this)
		{
			if (m_year > 1999)
			{
				os << setw(4);
			}
			os << setfill('0') << m_year << "/" << setw(2) << m_month << "/" << setw(2) << m_day;
			if (!m_dateOnly)
			{
				os << ", " << setw(2) << m_hour << ":" << setw(2) << m_min;
			}
			
		}
		else
		{
			os << m_err << "(";
			if (m_year > 1999)
			{
				os << setw(4);
			}
			os << setfill('0') << m_year << "/" << setw(2) << m_month << "/" << setw(2) << m_day;
			if (!m_dateOnly)
			{
				os << ", " << setw(2) << m_hour << ":" << setw(2) << m_min;
			}
			os << ")";
		}

		return os;
	}
	istream& Date::operator>>(istream& is)
	{
		int year = 0;
		int mon = 0;
		int day = 0;
		int hour = 0;
		int min = 0;

		m_err.clear();
		setEmpty();
		dateOnly(false);
		is >> year;
		if (is)
		{
			m_year = year;
			is.ignore();
			is >> mon;
			if (is)
			{
				m_month = mon;
				is.ignore();
				is >> day;
				if (is)
				{
					m_day = day;
					//is.ignore();
					if (is.peek() != '\n')
					{
						is.ignore();
						is >> hour;
						if (is)
						{
							m_hour = hour;
							is.ignore();
							is >> min;
							if (!is)
							{
								m_err = "Cannot read minute entry";
							}
							else
							{
								m_min = min;
								m_dateOnly = 0;
								validate(m_year, m_month, m_day, m_hour, m_min);
							}
						}
						else
						{
							m_err = "Cannot read hour entry";
						}
					}
					else
					{
						m_dateOnly = 1;
						validate(m_year, m_month, m_day);
					}
				}
				else
				{
					m_err = "Cannot read day entry";
				}
			}
			else
			{
				m_err = "Cannot read month entry";
			}
		}
		else
		{
			m_err = "Cannot read year entry";
		}

		return is;
	}
	std::ostream& operator<<(std::ostream& os, Date& date)
	{
		return date.operator<<(os);
	}
	std::istream& operator>>(std::istream& is, Date& date)
	{
		return date.operator>>(is);
	}
}