#define _CRT_SECURE_NO_WARNINGS
#include "PosIO.h"

using namespace std;

namespace superstore
{
    ostream& operator<<(ostream& os, PosIO& posio)
    {
        posio.write(os);
        return os;
    }
    ofstream& operator<<(ofstream& ofs, PosIO& posio)
    {
        posio.save(ofs);
        return ofs;
    }
    istream& operator>>(istream& is, PosIO& posio)
    {
        posio.read(is);
        return is;
    }
    ifstream& operator>>(ifstream& ifs, PosIO& posio)
    {
        posio.load(ifs);
        return ifs;
    }
}
