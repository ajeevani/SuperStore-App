#ifndef  SDDS_PERISHABLE_H_
#define  SDDS_PERISHABLE_H_
#include "Item.h"
#include "Date.h"

namespace superstore
{
	class Perishable : public Item
	{
		Date date;
	public:
		Perishable();
		char itemType()const;
		std::ostream& write(std::ostream& os);
		std::ofstream& save(std::ofstream& ofs);
		std::istream& read(std::istream& is);
		std::ifstream& load(std::ifstream& ifs);
	};
}

#endif // ! SDDS_PERISHABLE_H_
