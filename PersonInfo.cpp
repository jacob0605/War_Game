#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "PersonInfo.h"

using namespace std;

void PersonInfo::set_name(const char* src) {
    if (src == nullptr) {
        name[0] = 0;
        return;
    }
    std::strncpy(name, src, NAME_CAP);
    name[NAME_CAP] = 0;
}

void PersonInfo::save(ofstream& outfile) const {
    if (!outfile.is_open()) {
        cerr << "Error, Failed to open file for save data at line " << __LINE__ << " in " << __FILE__ << endl;
        return;
    }
    outfile << code << endl;
    outfile << id_num << endl;
    outfile << name << endl;
    outfile << health << endl;
    outfile << speed << endl;
    outfile << is_moving << endl;
    outfile << location << endl;
    outfile << destination << endl;
    outfile << delta << endl;
}

void PersonInfo::restore(std::ifstream& infile) {
    if (!infile.is_open()) {
        cerr << "Error, Failed to open file for save data at line " << __LINE__ << " in " << __FILE__ << endl;
        return;
    }

    string temp_name;

    infile >> code;
    infile >> id_num;
    infile >> temp_name;
    infile >> health;
    infile >> speed;
    infile >> is_moving;
    infile >> location;
    infile >> destination;
    infile >> delta;

    set_name(temp_name.c_str());
}
