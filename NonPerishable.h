#ifndef SDDS_NONPERISHABLE_H_
#define SDDS_NONPERISHABLE_H_
#include "Item.h"

namespace superstore
{
	class NonPerishable : public Item
	{
	public:
		char itemType()const;
		std::ostream& write(std::ostream& os);
	};
}

#endif