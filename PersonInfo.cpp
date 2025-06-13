#include <iostream>
#include <fstream>
#include "PersonInfo.h"

using namespace std;

void PersonInfo::save(ofstream& outfile) {
    if (!outfile.is_open()) {
        cerr << "Error, Failed to open file for save data at line " << __LINE__ << " in " << __FILE__ << "\n";
        return;
    }
    outfile << code << endl;
    git
            outfile
        << id_num << endl;
    outfile << name << endl;
    outfile << health << endl;
    outfile << speed << endl;
    outfile << is_moving << endl;
    outfile << location << endl;
    outfile << destination << endl;
    outfile << delta << endl;
}

void PersonInfo::restore(std::ifstream& infile) {
}
