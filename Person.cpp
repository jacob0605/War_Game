#include <cmath>
#include <cstring>
#include <iostream>

#include "Person.h"

using namespace std;

Person::Person(Game_World* w_ptr)
    : world_ptr(w_ptr),
      code('?'),
      id_num(0),
      name(nullptr),
      health(5),
      speed(5.0),
      moving(false),
      location(0, 0),
      destination(0, 0),
      delta(0, 0) {
    set_name("defaultName");
}

Person::Person(Game_World* w_ptr, char c, int id, double in_x, double in_y, const string& in_name)
    : world_ptr(w_ptr),
      code(c),
      id_num(id),
      name(nullptr),
      health(5),
      speed(5.0),
      moving(false),
      location(in_x, in_y),
      destination(in_x, in_y),
      delta(0, 0) {
    set_name(in_name);
}

Person::~Person() {
    delete[] name;
    name = nullptr;
}

void Person::set_name(const string& in_name) {
    delete[] name;
    name = new char[in_name.size() + 1];
    std::strcpy(name, in_name.c_str());
}

void Person::update_location() {
    if (!moving) {
        return;
    }

    const bool will_arrive =
        (std::abs(destination.x - location.x) <= std::abs(delta.x)) &&
        (std::abs(destination.y - location.y) <= std::abs(delta.y));

    if (will_arrive) {
        location = destination;
        delta = Real_Pair(0, 0);
        moving = false;
        cout << get_type_name() << " " << code << id_num << "(\"" << get_name() << "\") arrived" << endl;
        return;
    }

    location = location + delta;
    cout << get_type_name() << " " << code << id_num << "(\"" << get_name() << "\") moving" << endl;
}

void Person::display_status() {
    cout << get_type_name() << ' ' << code << id_num << "(\"" << get_name() << "\") at "
         << location << " is " << (get_alive() ? "alive" : "dead") << endl;
}

void Person::move_command(Real_Pair new_destination) {
    if (!get_alive()) {
        cout << "I'm dead - can't move " << code << id_num << "(\"" << get_name() << "\")" << endl;
        return;
    }

    destination = new_destination;
    const double total_distance = distance(destination, location);

    if (total_distance == 0.0) {
        delta = Real_Pair(0, 0);
        moving = false;
        return;
    }

    delta = (destination - location) * (speed / total_distance);
    moving = true;
}

void Person::set_load(double) {
    cout << "I can't carry a load" << endl;
}

void Person::attack_command(int) {
    cout << "I can't attack the enemy" << endl;
}

void Person::receive_attack(int, int attack_point) {
    if (!get_alive()) {
        return;
    }

    health -= attack_point;
    if (health < 0) {
        health = 0;
    }
}

void Person::save(ofstream& outfile) {
    outfile << code << endl;
    outfile << id_num << endl;
    outfile << get_name() << endl;
    outfile << health << endl;
    outfile << speed << endl;
    outfile << moving << endl;
    outfile << location << endl;
    outfile << destination << endl;
    outfile << delta << endl;
}

void Person::restore(ifstream& infile) {
    string restored_name;

    infile >> id_num;
    infile >> restored_name;
    set_name(restored_name);
    infile >> health;
    infile >> speed;
    infile >> moving;
    infile >> location;
    infile >> destination;
    infile >> delta;
}
