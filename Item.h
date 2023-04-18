#ifndef SDDS_ITEM_H_
#define SDDS_ITEM_H_
#include "POS.h"
#include "PosIO.h"
#include "Error.h"

namespace superstore
{
	class Item : public PosIO
	{
		char m_sku[MAX_SKU_LEN + 1];
		char m_item[MAX_NAME_LEN + 1]; //MAX_NAME_LEN
		double m_price;
		bool m_taxed;
		int m_quantity;
	protected:
		int m_displayType; //POS_LIST or POS_FORM
		Error m_err;
	public:
		Item();
		Item(Item& item);
		Item& operator=(const Item& item);
		bool operator==(const char* sku);
		bool operator>(Item& item);
		int operator+=(int quantity);
		int operator-=(int quantity);
		operator bool();
		Item& displayType(int pos);
		double cost() const;
		int quantity();
		Item& clear();
		std::ostream& write(std::ostream& os);
		std::ofstream& save(std::ofstream& ofs);
		virtual char itemType()const = 0; 
		std::istream& read(std::istream& is);
		std::ifstream& load(std::ifstream& ifs);
		std::ostream& bprint(std::ostream& os) const;
		const char* name();
		void printDataFile();
		void addQuantity(int quan);
		const char* sku();
	};
	double operator+=(double& val, Item& item);
}
#endif