#include <cmath>
#include <iostream>

#include "Person.h"

using namespace std;

namespace {
const char* resolve_label(char code) {
    switch (code) {
        case 'P': return "Peasant";
        case 'S': return "Soldier";
        case 'A': return "Archer";
        default: return "Person";
    }
}
}

Person::Person() {
    baseData.set_name("defaultName");
}

Person::Person(Game_World* w_ptr) {
    baseData.set_name("defaultName");
    baseData.world_ptr = w_ptr;
}

Person::Person(Game_World* w_ptr, char c, int id, double in_x, double in_y, const char* name_value) {
    baseData.code = c;
    baseData.id_num = id;
    baseData.location = Real_Pair(in_x, in_y);
    baseData.world_ptr = w_ptr;
    baseData.set_name(name_value);
}

Person::~Person() {
    cout << resolve_label(baseData.code) << " " << get_name() << " is deallocated" << endl;
}

void Person::update_location() {
    if (baseData.is_moving == true) {
        if ((abs(baseData.destination.x - baseData.location.x) <= abs(baseData.delta.x)) &&
            (abs(baseData.destination.y - baseData.location.y) <= abs(baseData.delta.y))) {
            baseData.location = baseData.destination;
            cout << "ID: " << baseData.id_num << ", arrived" << endl;
            baseData.delta.x = 0;
            baseData.delta.y = 0;
            baseData.is_moving = false;
        } else {
            baseData.location = baseData.location + baseData.delta;
            cout << "ID: " << baseData.id_num << ", moving" << endl;
        }
    }
}

void Person::move_command(Real_Pair destination) {
    if (baseData.health <= 0) {
        cout << "I'm dead - can't move (id: " << baseData.id_num << ")" << endl;
    } else {
        baseData.destination = destination;
        baseData.is_moving = true;
        baseData.delta = (baseData.destination - baseData.location) *
                         (baseData.speed / distance(baseData.destination, baseData.location));
    }
}

void Person::set_load(double) {
    cout << "I can't carry a load" << endl;
}

void Person::display_status() {
    cout << "Name : " << get_name() << endl;
}

void Person::save(ofstream& outfile) {
    if (!outfile.is_open()) {
        cerr << "Error, Failed to open file for save data at line " << __LINE__ << " in " << __FILE__ << endl;
        return;
    }

    baseData.save(outfile);
}

void Person::restore(ifstream& infile) {
    if (!infile.is_open()) {
        cerr << "Error, Failed to open file for save data at line " << __LINE__ << " in " << __FILE__ << endl;
        return;
    }
    baseData.restore(infile);
}

void Person::attack_command(int) {
    cout << "I can't attack the enemy" << endl;
}

void Person::receive_attack(int, int attack_point) {
    if (baseData.health > attack_point) {
        cout << "Outch!" << endl;
        baseData.health -= attack_point;
    } else {
        baseData.health = 0;
    }
}
