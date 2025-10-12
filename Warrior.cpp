#include <iostream>
#include <fstream>
#include <cmath>

#include "Warrior.h"

using namespace std;

void Warrior::initialize(int _attack_point, double _range, bool is_attack, int _target) {
    attack_point = _attack_point;
    range = _range;
    is_attacking = is_attack;
    target = _target;
}

Warrior::Warrior() : Person() {
    initialize();
}

Warrior::Warrior(int id, double x, double y) : Person() {
    baseData.id_num = id;
    baseData.location = Real_Pair(x, y);
    initialize();
}

Warrior::Warrior(Game_World* w_ptr) : Person(w_ptr) {
    initialize();
}

Warrior::Warrior(Game_World* w_ptr, char c, int id, double x, double y, const char* name_value)
    : Person(w_ptr, c, id, x, y, name_value) {
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
#ifdef _DEBUG
    cout << "attack command is called" << endl;
#endif // _DEBUG

    Game_World* world = baseData.world_ptr;
    Person* target_ptr = (world != nullptr) ? world->get_object_ptr(target_id) : nullptr;

    if (get_alive() && target_ptr != nullptr && target_ptr->get_alive()) {
        if (distance(get_location(), target_ptr->get_location()) <= range) {
            is_attacking = true;
            target = target_id;
            baseData.is_moving = false;
        }
    } else {
        is_attacking = false;
        if (get_delta().x != 0 || get_delta().y != 0) {
            baseData.is_moving = true;
        }
        cout << "Can't attack the target(id: " << target_id << ")" << endl;
    }
}

void Warrior::receive_attack(int attacker_id, int attack_point_value) {
    baseData.health -= attack_point_value;
    if (baseData.health < 0) {
        baseData.health = 0;
    }
    if (get_alive() && !is_attacking) {
        attack_command(attacker_id);
    }
}
