#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "PosApp.h"
#include "Perishable.h"
#include "NonPerishable.h"

using namespace std;

namespace superstore
{
	void PosApp::actionTitle(const char* title)
	{
		cout << ">>>> " << setw(72) << left << setfill('.') << title << endl;
	}
	void PosApp::menu()
	{
		bool exit = false;
		bool goodselect = false;
		int select;
		

		while (!exit)
		{
			cout << "The NoStore" << endl;
			cout << "1- List items" << endl;
			cout << "2- Add item" << endl;
			cout << "3- Remove item" << endl;
			cout << "4- Stock item" << endl;
			cout << "5- POS" << endl;
			cout << "0- exit program" << endl;
			cout << "> ";
			goodselect = false;

			while (!goodselect)
			{
				cin >> select;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Integer, try again: ";
				}
				else if (select == 1)
				{
					listItems();
					goodselect = true;
				}
				else if (select == 2)
				{
					addItem();
					goodselect = true;
				}
				else if (select == 3)
				{
					removeItem();
					goodselect = true;
				}
				else if (select == 4)
				{
					stockItem();
					goodselect = true;
				}
				else if (select == 5)
				{
					POS();
					goodselect = true;
				}
				else if (select < 0 || select > 5)
				{
					cout << "[0<=value<=5], retry: > ";
				}
				else if (select == 0)
				{
					saveRecs();
					goodselect = true;
					exit = true;
				}
			}
		}
	}
	void PosApp::addItem()
	{
		actionTitle("Adding Item to the store");
		if (m_nptr >= MAX_NO_ITEMS)
		{
			cout << "Inventory Full!" << endl;
		}
		else
		{
			Item* temp = nullptr;
			char type;
			bool done = 0;
			cout << "Is the Item perishable? (Y)es/(N)o: ";
			while (!done)
			{
				cin >> type;
				if (cin)
				{
					if (type == 'y' || type == 'Y')
					{
						temp = new Perishable();
						done = 1;
					}
					else if (type == 'N' || type == 'n')
					{
						temp = new NonPerishable();
						done = 1;
					}
				}
				else
				{
					cout << "Only 'y' and 'n' are acceptable: ";
				}
			}
			temp->read(cin);
			if (cin)
			{
				m_iptr[m_nptr] = temp;
				m_nptr++;
				actionTitle("DONE!");
			}
		}
	}
	void PosApp::removeItem()
	{
		actionTitle("Remove Item");
		int num = selectItem();
		cout << "Removing...." << endl;
		m_iptr[num - 1]->displayType(2);
		m_iptr[num - 1]->write(cout);
		actionTitle("DONE!");
		delete m_iptr[num - 1];
		for (int i = num; i < m_nptr; i++)
		{
			m_iptr[i - 1] = m_iptr[i];
		}
		m_iptr[m_nptr] = nullptr;
		m_nptr--;
	}
	void PosApp::stockItem()
	{
		actionTitle("Select an item to stock");
		sortItemsByName(m_iptr, m_nptr);
		int select = selectItem();
		cout << "Selected Item:" << endl;
		m_iptr[select - 1]->displayType(2);
		m_iptr[select - 1]->write(cout);
		bool pass = false;
		int num = 0;
		cout << "Enter quantity to add: ";
		cin >> num;
		while (!pass)
		{
			if (cin.fail())
			{
				cout << "Invalid Integer, try again: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> num;
			}
			else if (num > m_iptr[select-1]->quantity() || num < 1)
			{
				cout << "[1<=value<=" << 69 << "], retry: Enter quantity to add: ";
				cin >> num;
			}
			else
			{
				m_iptr[select - 1]->addQuantity(num);
				actionTitle("DONE!");
				pass = 1;
			}
		}
	}
	void PosApp::listItems()
	{
		actionTitle("Listing Items");
		sortItemsByName(m_iptr, m_nptr);
		double totalasset = 0.0;
		cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
		cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
		for (int i = 0; i < m_nptr; i++)
		{
			cout << setw(4) << setfill(' ') << right << i + 1 << " | ";
			cout.unsetf(ios::right);
			m_iptr[i]->displayType(1);
			m_iptr[i]->write(cout);
			cout << endl;
			totalasset += (m_iptr[i]->cost() * m_iptr[i]->quantity());
		}
		cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
		cout << "                               Total Asset: $  |" << setw(14) << setfill(' ') << right << totalasset << "|" << endl;
		cout << "-----------------------------------------------^--------------^" << endl << endl;
	}
	int PosApp::selectItem()
	{
		actionTitle("Item Selection by row number");
		cout << "Press <ENTER> to start....";
		cin.ignore(1000, '\n');
		cin.ignore(1000, '\n');
		actionTitle("Listing Items");
		sortItemsByName(m_iptr, m_nptr);
		cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
		cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
		for (int i = 0; i < m_nptr; i++)
		{
			cout << setw(4) << setfill(' ') << right << i + 1 << " | ";
			cout.unsetf(ios::right);
			m_iptr[i]->displayType(1);
			m_iptr[i]->write(cout);
			cout << endl;
		}
		cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
		int num = 0;
		cout << "Enter the row number: ";
		cin >> num;
		bool pass = 0;
		while (!pass)
		{
			if (cin.fail())
			{
				cout << "Invalid Integer, try again: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> num;
			}
			else if (num > m_nptr || num < 1)
			{
				cout << "[1<=value<=" << m_nptr << "], retry: Enter the row number: ";
				cin >> num;
			}
			else
			{
				pass = 1;
			}
		}
		return num;
	}
	void PosApp::POS()
	{
		cin.ignore(100, '\n');
		actionTitle("Starting Point of Sale");
		char sku[MAX_SKU_LEN + 1];
		bool billpass = 0;
		int pass = -1;
		while (!billpass)
		{
			cout << "Enter SKU or <ENTER> only to end sale..." << endl << "> ";
			char c;
			int i = -1;
			bool done = 1;
			while (done && i < MAX_SKU_LEN)
			{
				c = getchar();
				if (c == '\n')
				{
					done = 0;
				}
				i++;
				sku[i] = c;
			}
			if (i > 0)
			{
				sku[i] = '\0';
			}
			if (sku[0] == '\n')
			{
				m_bill.print(cout);
				billpass = 1;
			}
			else if (strlen(sku) > 0)
			{
				pass = -1;
				for (int i = 0; pass <= 0 && i < m_nptr; i++)
				{
					if (!strcmp(m_iptr[i]->sku(), sku))
					{
						pass = i;
					}
					else
					{
						pass = -1;
					}
				}
				if (pass != -1)
				{
					if (m_iptr[pass]->quantity() > 0)
					{
						m_iptr[pass]->addQuantity(-1);
						m_bill.add(m_iptr[pass]);
						m_iptr[pass]->displayType(2);
						m_iptr[pass]->write(cout);
						cout << endl << ">>>>> Added to bill" << endl << ">>>>> Total: " << setprecision(2) << fixed << m_bill.total() << endl;

					}
					else
					{
						cout << "Item out of stock" << endl;
					}
				}
				else if(pass == -1)
				{
					cout << "!!!!! Item Not Found !!!!!" << endl;
				}
			}
		}
	}
	void PosApp::saveRecs()
	{
		actionTitle("Saving Data");
		ofstream ofs(m_filename);
		for (int i = 0; i < m_nptr; i++) {
			m_iptr[i]->save(ofs);
			ofs << endl;
		}
		ofs.close();
	}
	void PosApp::loadRecs()
	{
		actionTitle("Loading Items");
		ifstream input(m_filename);
		if (!input.is_open())
		{
			ofstream create(m_filename);
			create.close();
			input.open(m_filename);
		}
		for (int i = 0; i < MAX_NO_ITEMS; i++) {
			if (m_iptr[i] != nullptr)
			{
				delete m_iptr[i];
				m_iptr[i] = nullptr;
			}
		}
		m_nptr = 0;
		
		for (int i = 0; input && i < MAX_NO_ITEMS; i++)
		{
			char type;

			input >> type;
			if (input)
			{
				if (type == 'P')
				{
					m_iptr[i] = new Perishable();
				}
				else if (type == 'N')
				{
					m_iptr[i] = new NonPerishable();
				}
				input.ignore();
				m_iptr[i]->load(input);
				m_nptr++;
			}
		}
		input.close();
	}
	void PosApp::sortItemsByName(Item* iptr[], int nptr)
	{
		bool pass = true;
		Item* temp;
		int x = 0;
		while (pass)
		{
			x++;
			pass = 0;
			for (int i = 0; i < nptr - x; i++)
			{
				if (strcmp(iptr[i]->name(), iptr[i + 1]->name()) > 0)
				{
					temp = iptr[i];
					iptr[i] = iptr[i + 1];
					iptr[i + 1] = temp;
					pass = true;
				}
			}
		}
		
	}
	PosApp::PosApp()
	{
		m_filename[0] = '\0';
		for (int i = 0; i < MAX_NO_ITEMS; i++)
		{
			m_iptr[i] = nullptr;
		}
		m_nptr = 0;
	}
	PosApp::PosApp(const char* filename)
	{
		strcpy(m_filename, filename);
		for (int i = 0; i < MAX_NO_ITEMS; i++)
		{
			m_iptr[i] = nullptr;
		}
		m_nptr = 0;
	}
	void PosApp::run()
	{
		if (m_filename[0] != '\0')
		{
			loadRecs();
			menu();
			cout << "Goodbye!" << endl;
		}
	}
	PosApp::~PosApp()
	{
		for (int i = 0; i < m_nptr; i++)
		{
			delete m_iptr[i];
		}
	}
}