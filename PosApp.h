#ifndef SDDS_POSAPP_H_
#define SDDS_POSAPP_H_
#include <iostream>
#include "Item.h"
#include "Bill.h"

namespace superstore
{
	class PosApp
	{
		char m_filename[128 + 1];
		Item* m_iptr[MAX_NO_ITEMS + 1];
		int m_nptr;
		Bill m_bill;

		void actionTitle(const char* title);
		void menu();
		void addItem();
		void removeItem();
		void stockItem();
		void listItems();
		int selectItem();
		void POS();
		void saveRecs();
		void loadRecs();
		void sortItemsByName(Item* iptr[], int nptr);
	public:
		PosApp();
		PosApp(const char* filename);
		PosApp(PosApp& pos) = delete;
		PosApp& operator=(PosApp& pos) = delete;
		~PosApp();
		void run();
	};
}

#endif