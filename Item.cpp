#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "Item.h"

using namespace std;

namespace superstore
{
	Item::Item()
	{
		m_sku[0] = '\0';
		m_item[0] = '\0';
		m_price = 0.0;
		m_taxed = false;
		m_quantity = 0;
		m_displayType = 0;
	}
	Item::Item(Item& item)
	{
		m_sku[0] = '\0';
		m_item[0] = '\0';
		m_price = 0.0;
		m_taxed = false;
		m_quantity = 0;
		m_displayType = 0;

		*this = item;
	}
	Item& Item::operator=(const Item& item)
	{
		if (strlen(item.m_sku) <= MAX_SKU_LEN && strlen(item.m_item) <= MAX_NAME_LEN)
		{
			strncpy(m_sku, item.m_sku, MAX_SKU_LEN);
			//m_item = new char[strlen(item.m_item) + 1];
			strcpy(m_item, item.m_item);
			m_price = item.m_price;
			m_taxed = item.m_taxed;
			m_quantity = item.m_quantity;
			m_displayType = item.m_displayType;
		}

		return *this;
	}
	bool Item::operator==(const char* sku)
	{
		return !strcmp(sku, m_sku);
	}
	bool Item::operator>(Item& item)
	{
		return strcmp(m_item, item.m_item);
	}
	int Item::operator+=(int quantity)
	{
		m_quantity += quantity;
		if (m_quantity > MAX_STOCK_NUMBER)
		{
			m_quantity = MAX_STOCK_NUMBER;
			m_err = ERROR_POS_QTY;
		}

		return m_quantity;
	}
	int Item::operator-=(int quantity)
	{
		m_quantity -= quantity;
		if (m_quantity < 0)
		{
			m_quantity = 0;
			m_err = ERROR_POS_STOCK;
		}
		return m_quantity;
	}
	Item::operator bool()
	{
		return !m_err;
	}
	Item& Item::displayType(int pos)
	{
		m_displayType = pos;
		return *this;
	}
	double Item::cost() const
	{
		double price = 0;
		if (m_taxed)
		{
			price = m_price + (m_price * TAX);
		}
		else
		{
			price = m_price;
		}
		return price;
	}
	int Item::quantity()
	{
		return m_quantity;
	}
	Item& Item::clear()
	{
		m_err.clear();

		return *this;
	}
	ostream& Item::write(ostream& os)
	{
		if (m_err)
		{
			os << m_err;
		}
		else if (m_displayType == POS_LIST)
		{
			char name[MAX_NAME_LEN + 1];
			strcpy(name, m_item);
			name[20] = '\0';

			os << setw(7) << setfill(' ') << left << m_sku << "|" << left << setw(20) << name << "|" << setw(7) << right << m_price << "| ";
			if (m_taxed)
			{
				os << internal << "X";
			}
			else
			{
				os << " ";
			}
			os << " |" << setw(4) << right << m_quantity << "|" << setw(9) << right << setprecision(2) << fixed << cost()*m_quantity << "|";
			os.unsetf(ios::right);
		}
		else if (m_displayType == POS_FORM)
		{
			os << setw(14) << left << setfill('=') << right << "v" << endl << setw(13) << setfill(' ')  << left << "Name:" << right << m_item << endl << setw(13) << left << "Sku:" << right << m_sku << endl << setw(13) << left << "Price:" << right << m_price << endl << setw(13) << left << "Price + tax:" << right << setprecision(2) << fixed;
			if (m_taxed)
			{
				os << cost() << endl;
			}
			else
			{
				os << "N/A" << endl;
			}
			os << setw(13) << left << "Stock Qty:" << right << m_quantity << endl;
			os.unsetf(ios::right);
		}


		return os;
	}
	ofstream& Item::save(ofstream& ofs)
	{
		if (m_err)
		{
			cerr << m_err << endl;
		}
		else
		{
			ofs << itemType() << "," << m_sku << "," << m_item << "," << setprecision(2) << fixed << m_price << ",";
			if (m_taxed)
			{
				ofs << 1;
			}
			else
			{
				ofs << 0;
			}
			ofs << "," << m_quantity;
		}

		return ofs;
	}
	std::istream& Item::read(std::istream& is)
	{
		bool sku = 0;
		is.clear();
		cout << "Sku" << endl << "> ";
		while (!sku)
		{
			is >> m_sku;
			if (strlen(m_sku) > MAX_SKU_LEN)
			{
				cout << ERROR_POS_SKU << endl << "> ";
			}
			else
			{
				sku = 1;
			}
		}
		bool itemname = 0;
		char name[100];
		is.ignore();
		cout << "Name" << endl << "> ";
		while (!itemname)
		{
			is.getline(name, 99);
			if ((strlen(name)) >= MAX_NAME_LEN)
			{
				cout << ERROR_POS_NAME << endl << "> ";
			}
			else
			{
				//m_item = new char[strlen(name) + 1];
				strcpy(m_item, name);
				itemname = 1;
			}
		}
		bool price = 0;
		//is.ignore();
		cout << "Price" << endl << "> ";
		while (!price)
		{
			is >> m_price;
			if ((m_price < 0.0) || is.fail())
			{
				is.clear(); // clear error flag
				is.ignore(1000, '\n');
				cout << ERROR_POS_PRICE << endl << "> ";
				//is.ignore();
			}
			else
			{
				price = 1;
			}
		}
		bool taxed = 0;
		char tax;
		//is.ignore();
		cout << "Taxed?" << endl << "(Y)es/(N)o: ";
		while (!taxed)
		{
			is >> tax;
			if ((tax != 'y' && tax != 'Y' && tax != 'n' && tax != 'N') || is.fail())
			{
				is.clear(); // clear error flag
				is.ignore(1000, '\n');
				cout << "Only 'y' and 'n' are acceptable: ";
			}
			else
			{
				if (tax == 'y' || tax == 'Y')
				{
					m_taxed = 1;
				}
				else
				{
					m_taxed = 0;
				}
				taxed = 1;
			}
		}
		bool quant = 0;
		cout << "Quantity" << endl << "> ";
		while (!quant)
		{
			is >> m_quantity;
			if (m_quantity <= 0 || (m_quantity > MAX_STOCK_NUMBER) || is.fail())
			{
				is.clear(); // clear error flag
				is.ignore(1000,'\n');
				cout << ERROR_POS_QTY << endl << "> ";
			}
			else
			{
				quant = 1;
			}
		}

		return is;
	}
	ifstream& Item::load(ifstream& ifs)
	{
		char sku[100 + 1];
		char item[100 + 1];
		double price;
		int taxed;
		int quantity;
		m_err.clear();
		ifs.getline(sku, 100, ',');
		ifs.getline(item, 100, ',');
		
		//ifs.ignore(',');
		ifs >> price;
		ifs.ignore();
		ifs >> taxed;
		ifs.ignore();
		ifs >> quantity;

		if (!ifs.fail())
		{
			if (strlen(sku) > 0 && strlen(sku) <= MAX_SKU_LEN)
			{
				strcpy(m_sku, sku);
				if (strlen(item) <= MAX_NAME_LEN)
				{
					//m_item = new char[strlen(item) + 1];
					strncpy(m_item, item, MAX_NAME_LEN);
					if (price > 0.0)
					{
						m_price = price;
						if (taxed == 0 || taxed == 1)
						{
							m_taxed = taxed;
							if (quantity <= MAX_STOCK_NUMBER)
							{
								m_quantity = quantity;
							}
							else
							{
								m_err = ERROR_POS_QTY;
							}
						}
						else
						{
							m_err = ERROR_POS_TAX;
						}
					}
					else
					{
						m_err = ERROR_POS_PRICE;
					}
				}
				else
				{
					m_err = ERROR_POS_NAME;
				}
			}
			else
			{
				m_err = ERROR_POS_SKU;
			}
		}

		return ifs;
	}
	ostream& Item::bprint(ostream& os) const
	{
		char name[MAX_NAME_LEN + 1];
		strcpy(name, m_item);
		name[20] = '\0';

		os << "| " << setw(20) << setfill(' ') << left << name << right << "| " << setw(9) << cost() << " |  " << internal;
		(m_taxed) ? os << "T" : os << " ";
		os << "  |" << endl;
		os.unsetf(ios::internal);

		return os;
	}
	const char* Item::name()
	{
		return m_item;
	}
	void Item::printDataFile()
	{
		cout << itemType() << "," << m_sku << "," << m_item << "," << setprecision(2) << fixed << m_price << ",";
		if (m_taxed)
		{
			cout << 1;
		}
		else
		{
			cout << 0;
		}
		cout << "," << m_quantity << endl;
	}
	void Item::addQuantity(int quan)
	{
		m_quantity += quan;
	}
	const char* Item::sku()
	{
		return m_sku;
	}
	double operator+=(double& val, Item& item)
	{
		val += (item.cost() * item.quantity());
		return val;
	}
}