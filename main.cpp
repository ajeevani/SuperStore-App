#include <fstream>
#include <iostream>
#include "PosApp.h"
void resetDataFile();
void displayfileContent();
int main() {
    resetDataFile();
    superstore::PosApp pos("data.csv");
    pos.run();
    displayfileContent();
    return 0;
}
void resetDataFile() {
    char ch{};
    std::ofstream outfile("data.csv");
    std::ifstream infile("dataTest.csv");
    while (infile.get(ch)) {
        outfile.put(ch);
    }
}
void displayfileContent() {
    std::cout << "Data file:\n------------------\n";
    char ch{};
    std::ifstream infile("data.csv");
    while (infile.get(ch)) {
        std::cout.put(ch);
    }
    std::cout << "------------------\n";
}