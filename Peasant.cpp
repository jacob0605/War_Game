#include <iostream>

#include "Peasant.h"

using namespace std;

void Peasant::initialize() {
    health = 10;
    max_speed = 5.0;
    load = 0.0;
    capacity = 50.0;
    speed = max_speed;
}

Peasant::Peasant() : Person(nullptr, 'P', 0, 0, 0, "Peasant") {
    initialize();
}

Peasant::Peasant(int id, double x, double y) : Person(nullptr, 'P', id, x, y, "Peasant") {
    initialize();
}

Peasant::Peasant(Game_World* w_ptr) : Person(w_ptr, 'P', 0, 0, 0, "Peasant") {
    initialize();
}

Peasant::Peasant(Game_World* w_ptr, int id, double x, double y, const string& in_name)
    : Person(w_ptr, 'P', id, x, y, in_name) {
    initialize();
}

Peasant::~Peasant() {
    cout << "Peasant " << get_name() << " is deallocated" << endl;
}

void Peasant::update() {
    if (get_alive()) {
        update_location();
    }
}

void Peasant::set_load(double in_load) {
    if (in_load > capacity) {
        cout << "Specified load is greater than carrying capacity" << endl;
        return;
    }

    load = in_load;
    speed = max_speed - (load / capacity) * max_speed;
    if (speed < 0.5) {
        speed = 0.5;
    }

    if (moving) {
        move_command(destination);
    }

    cout << "With load of " << load << " can move at speed " << speed << endl;
}

void Peasant::display_status() {
    cout << "Peasant " << code << id_num << "(\"" << get_name() << "\") at " << location
         << " is " << (get_alive() ? "alive" : "dead") << endl;

    if (!get_alive()) {
        return;
    }

    cout << "Load is " << load << ", health is " << health << endl;
    if (moving) {
        cout << "Moving at speed " << speed << " to " << destination << endl;
    } else {
        cout << "Not moving" << endl;
    }
}

void Peasant::save(ofstream& outfile) {
    Person::save(outfile);
    outfile << capacity << endl;
    outfile << load << endl;
    outfile << max_speed << endl;
}

void Peasant::restore(ifstream& infile) {
    code = 'P';
    Person::restore(infile);
    infile >> capacity;
    infile >> load;
    infile >> max_speed;
}
