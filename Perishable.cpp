#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Perishable.h"

using namespace std;

namespace superstore
{
	Perishable::Perishable() : Item()
	{
		
	}
	char Perishable::itemType() const
	{
		return 'P';
	}
	ostream& Perishable::write(ostream& os)
	{
		Item::write(os);
		if (*this)
		{
			if (m_displayType == POS_LIST)
			{
				os << "  " << date << " " << "|";
			}
			else if (m_displayType == POS_FORM)
			{
				os << "Expiry date: " << date << endl << "=============^" << endl;
			}
		}

		return os;
	}
	std::ofstream& Perishable::save(std::ofstream& ofs)
	{
		Item::save(ofs);
		if (*this)
		{
			ofs << "," << date;
		}

		return ofs;
	}
	istream& Perishable::read(istream& is)
	{
		Item::read(is);
		if (*this && is)
		{
			Date d;
			d.dateOnly(1);
			cout << "Expiry date (YYYY/MM/DD)" << endl;
			cout << "> ";
			is >> d;
			if (d)
			{
				date = d;
			}
			else
			{
				date.error() = Item::m_err;
			}
		}

		return is;
	}
	ifstream& Perishable::load(ifstream& ifs)
	{
		Item::load(ifs);
		if (*this && ifs)
		{
			Date d;
			d.dateOnly(1);
			ifs.ignore(1 , ',');
			ifs >> d;
			if (d)
			{
				date = d;
			}
			else
			{
				date.error() = Item::m_err;
			}
		}

		return ifs;
	}
}