#include <iostream>

#include "Warrior.h"
#include "Game_World.h"

using namespace std;

void Warrior::initialize(int in_attack_point, double in_range, bool in_attacking, int in_target) {
    attack_point = in_attack_point;
    range = in_range;
    is_attacking = in_attacking;
    target = in_target;
}

Warrior::Warrior() : Person(nullptr, 'W', 0, 0, 0, "Warrior") {
    initialize();
}

Warrior::Warrior(int id, double x, double y) : Person(nullptr, 'W', id, x, y, "Warrior") {
    initialize();
}

Warrior::Warrior(Game_World* w_ptr) : Person(w_ptr, 'W', 0, 0, 0, "Warrior") {
    initialize();
}

Warrior::Warrior(Game_World* w_ptr, char c, int id, double x, double y, const string& in_name)
    : Person(w_ptr, c, id, x, y, in_name) {
    initialize();
}

Warrior::~Warrior() = default;

void Warrior::save(ofstream& outfile) {
    Person::save(outfile);
    outfile << attack_point << endl;
    outfile << range << endl;
    outfile << is_attacking << endl;
    outfile << target << endl;
}

void Warrior::restore(ifstream& infile) {
    Person::restore(infile);
    infile >> attack_point;
    infile >> range;
    infile >> is_attacking;
    infile >> target;
}

void Warrior::attack_command(int target_id) {
    if (!get_alive()) {
        cout << "Can't attack because I am dead" << endl;
        return;
    }

    if (world_ptr == nullptr) {
        cout << "No world to attack in" << endl;
        return;
    }

    Person* target_ptr = world_ptr->get_object_ptr(target_id);
    if (target_ptr == nullptr || !target_ptr->get_alive()) {
        is_attacking = false;
        cout << "Can't attack the target(id: " << target_id << ")" << endl;
        return;
    }

    if (distance(location, target_ptr->get_location()) > range) {
        is_attacking = false;
        cout << "Target is out of range" << endl;
        return;
    }

    is_attacking = true;
    target = target_id;
    moving = false;
}

void Warrior::receive_attack(int attacker_id, int in_attack_point) {
    if (!get_alive()) {
        return;
    }

    health -= in_attack_point;
    if (health < 0) {
        health = 0;
    }

    if (get_alive() && !is_attacking) {
        attack_command(attacker_id);
    }
}
