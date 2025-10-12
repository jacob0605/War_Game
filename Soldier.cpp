#include <iostream>
#include <fstream>
#include <cmath>

#include "Soldier.h"

using namespace std;

Soldier::Soldier() : Warrior() { baseData.code = 'S'; }

Soldier::Soldier(int id, double x, double y) : Warrior() {
    baseData.code = 'S';
    baseData.id_num = id;
    baseData.location = Real_Pair(x, y);
}

Soldier::Soldier(Game_World* w_ptr) : Warrior(w_ptr) { baseData.code = 'S'; }

Soldier::Soldier(Game_World* w_ptr, int id, double x, double y, const char* name_value)
    : Warrior(w_ptr, 'S', id, x, y, name_value) { baseData.code = 'S'; }

void Soldier::update() {
    if (!get_alive()) {
        return;
    }

    Game_World* world = baseData.world_ptr;
    if (is_attacking && world != nullptr) {
        Person* target_ptr = world->get_object_ptr(target);
        if (target_ptr != nullptr && target_ptr->get_alive()) {
            if (distance(get_location(), target_ptr->get_location()) <= range) {
                target_ptr->receive_attack(get_ID(), attack_point);
                cout << "attack the target(id: " << target << "), attack point is " << attack_point << endl;
            } else {
                is_attacking = false;
                cout << "target is out of range" << endl;
            }
        } else {
            is_attacking = false;
            cout << "the target is dead" << endl;
        }
    }

    if (baseData.is_moving) {
        baseData.health--;
        if (baseData.health <= 0) {
            cout << baseData.id_num << " dead" << endl;
            baseData.is_moving = false;
        } else {
            update_location();
        }
    }
}

void Soldier::display_status() {
    const Real_Pair location = get_location();
    Person::display_status();

    if (baseData.health > 0) {
        cout << "Soldier ID: " << baseData.id_num << " at (" << location.x << ", " << location.y << ") is alive" << endl;
        cout << "Health is " << baseData.health << ", speed is " << baseData.speed << endl;
        cout << (baseData.is_moving ? "Moving" : "Not moving") << endl;
        cout << "Attack point is " << attack_point << endl;
        cout << "Range is " << range << endl;
        if (is_attacking) {
            cout << "Attacking, target id is " << target << endl;
        } else {
            cout << "Not attacking" << endl;
        }
    } else {
        cout << "Soldier ID: " << baseData.id_num << " at (" << location.x << ", " << location.y << ") is dead" << endl;
    }
}

void Soldier::save(ofstream& outfile) {
    Warrior::save(outfile);
}

void Soldier::restore(ifstream& infile) {
    Warrior::restore(infile);
    baseData.code = 'S';
}
