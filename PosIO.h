#ifndef SDDS_POSIO_H_
#define SDDS_POSIO_H_
#include <iostream>
#include <fstream>

namespace superstore
{
	class PosIO
	{
	public:
		virtual std::ostream& write(std::ostream& os) = 0;
		virtual std::istream& read(std::istream& is) = 0;
		virtual std::ofstream& save(std::ofstream& ofs) = 0;
		virtual std::ifstream& load(std::ifstream& ifs) = 0;
		virtual ~PosIO() {};
	};
	std::ostream& operator<<(std::ostream& os, PosIO& posio);
	std::ofstream& operator<<(std::ofstream& ofs, PosIO& posio);
	std::istream& operator>>(std::istream& is, PosIO& posio);
	std::ifstream& operator>>(std::ifstream& ifs, PosIO& posio);
}
#endif