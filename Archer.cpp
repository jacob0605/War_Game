#include <iostream>

#include "Archer.h"
#include "Game_World.h"

using namespace std;

void Archer::initialize() {
    Warrior::initialize(2, 10.0, false, -1);
    health = 10;
    speed = 7.0;
}

Archer::Archer() : Warrior(nullptr, 'A', 0, 0, 0, "Archer") {
    initialize();
}

Archer::Archer(int id, double x, double y) : Warrior(nullptr, 'A', id, x, y, "Archer") {
    initialize();
}

Archer::Archer(Game_World* w_ptr) : Warrior(w_ptr, 'A', 0, 0, 0, "Archer") {
    initialize();
}

Archer::Archer(Game_World* w_ptr, int id, double x, double y, const string& in_name)
    : Warrior(w_ptr, 'A', id, x, y, in_name) {
    initialize();
}

Archer::~Archer() {
    cout << "Archer " << get_name() << " is deallocated" << endl;
}

void Archer::update() {
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
            cout << "Archer " << code << id_num << "(\"" << get_name() << "\") attacks target "
                 << target << endl;
        }
    } else if (world_ptr != nullptr) {
        Person* closest_target = nullptr;
        double best_distance = range + 1.0;

        world_ptr->start_scan();
        while (Person* scanned = world_ptr->get_next_scan_ptr()) {
            if (scanned == this || !scanned->get_alive()) {
                continue;
            }

            const double current_distance = distance(location, scanned->get_location());
            if (current_distance <= range && current_distance < best_distance) {
                best_distance = current_distance;
                closest_target = scanned;
            }
        }

        if (closest_target != nullptr) {
            attack_command(closest_target->get_ID());
            if (is_attacking) {
                closest_target->receive_attack(id_num, attack_point);
                cout << "Archer " << code << id_num << "(\"" << get_name() << "\") starts attacking "
                     << target << endl;
            }
        }
    }

    if (moving) {
        --health;
        if (health <= 0) {
            health = 0;
            moving = false;
            cout << "Archer " << code << id_num << "(\"" << get_name() << "\") died while moving" << endl;
        } else {
            update_location();
        }
    }
}

void Archer::display_status() {
    cout << "Archer " << code << id_num << "(\"" << get_name() << "\") at " << location
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

void Archer::save(ofstream& outfile) {
    Warrior::save(outfile);
}

void Archer::restore(ifstream& infile) {
    code = 'A';
    Warrior::restore(infile);
}
