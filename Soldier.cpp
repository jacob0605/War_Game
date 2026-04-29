#include <iostream>

#include "Soldier.h"
#include "Game_World.h"

using namespace std;

Soldier::Soldier() : Warrior(nullptr, 'S', 0, 0, 0, "Soldier") {}

Soldier::Soldier(int id, double x, double y) : Warrior(nullptr, 'S', id, x, y, "Soldier") {}

Soldier::Soldier(Game_World* w_ptr) : Warrior(w_ptr, 'S', 0, 0, 0, "Soldier") {}

Soldier::Soldier(Game_World* w_ptr, int id, double x, double y, const string& in_name)
    : Warrior(w_ptr, 'S', id, x, y, in_name) {}

Soldier::~Soldier() {
    cout << "Soldier " << get_name() << " is deallocated" << endl;
}

void Soldier::update() {
    if (!get_alive()) {
        return;
    }

    if (is_attacking) {
        Person* target_ptr = world_ptr != nullptr ? world_ptr->get_object_ptr(target) : nullptr;

        if (target_ptr == nullptr || !target_ptr->get_alive()) {
            is_attacking = false;
            cout << "The target is dead" << endl;
        } else if (distance(location, target_ptr->get_location()) > range) {
            is_attacking = false;
            cout << "Target is out of range" << endl;
        } else {
            target_ptr->receive_attack(id_num, attack_point);
            cout << "Soldier " << code << id_num << "(\"" << get_name() << "\") attacks target "
                 << target << endl;
        }
    }

    if (moving) {
        --health;
        if (health <= 0) {
            health = 0;
            moving = false;
            cout << "Soldier " << code << id_num << "(\"" << get_name() << "\") died while moving" << endl;
        } else {
            update_location();
        }
    }
}

void Soldier::display_status() {
    cout << "Soldier " << code << id_num << "(\"" << get_name() << "\") at " << location
         << " is " << (get_alive() ? "alive" : "dead") << endl;

    if (!get_alive()) {
        return;
    }

    cout << "Health is " << health << ", speed is " << speed << endl;
    cout << (moving ? "Moving" : "Not moving") << endl;
    cout << "Attack point is " << attack_point << ", range is " << range << endl;
    cout << (is_attacking ? "Attacking" : "Not attacking");
    if (is_attacking) {
        cout << ", target id is " << target;
    }
    cout << endl;
}

void Soldier::save(ofstream& outfile) {
    Warrior::save(outfile);
}

void Soldier::restore(ifstream& infile) {
    code = 'S';
    Warrior::restore(infile);
}
