#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "NonPerishable.h"

using namespace std;

namespace superstore
{
	char NonPerishable::itemType() const
	{
		return 'N';
	}
	ostream& NonPerishable::write(ostream& os)
	{
		Item::write(os);
		if (*this)
		{
			if (m_displayType == POS_LIST)
			{
				os << setw(13) << setfill(' ') << right << "N / A   " << "|";
				os.unsetf(ios::right);
			}
			else if (m_displayType == POS_FORM)
			{
				os << setw(14) << setfill('=') << "^" << endl;
			}
		}

		return os;
	}
}
