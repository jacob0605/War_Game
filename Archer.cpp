#include <iostream>
#include <fstream>
#include <cmath>

#include "Archer.h"

using namespace std;

void Archer::initialize() {
    Warrior::initialize(2, 10);
    set_health(10);
    set_speed(7);
}

Archer::Archer() : Warrior() {
    initialize();
}

Archer::Archer(int id, double x, double y) : Warrior(id, x, y) {
    initialize();
}

Archer::Archer(Game_World* w_ptr) : Warrior(w_ptr) {
    initialize();
}

Archer::Archer(Game_World* w_ptr, int id, double x, double y, const string& _name)
    : Warrior(w_ptr, 'A', id, x, y, _name) {
    initialize();
}

void Archer::update() {
#ifdef _DEBUG
    cout << "Archer class update function called" << endl;
#endif // _DEBUG

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
    } else if (world != nullptr) {
        cout << "	now, not attacking" << endl;
        int total_num = world->get_num_objects();
        double min_d = range;
        int target_id = -1;
        int this_id = get_ID();
        for (int i = 0; i < total_num; ++i) {
            Person* candidate = world->get_object_ptr(i);
            if (candidate == nullptr || !candidate->get_alive()) {
                continue;
            }
            if (candidate->get_ID() == this_id) {
                continue;
            }
            double d = distance(get_location(), candidate->get_location());
#ifdef _DEBUG
            cout << "		 d: " << d << endl;
#endif // _DEBUG
            if (d <= min_d) {
                min_d = d;
                target_id = candidate->get_ID();
            }
        }
        if (target_id != -1) {
            cout << "	find the target(id: " << target_id << "), start attack" << endl;
            attack_command(target_id);
            if (is_attacking) {
                Person* target_ptr = world->get_object_ptr(target);
                if (target_ptr != nullptr) {
                    target_ptr->receive_attack(get_ID(), attack_point);
                }
            }
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

void Archer::display_status() {
    const Real_Pair location = get_location();

    if (baseData.health > 0) {
        cout << "Archer ID: " << baseData.id_num << " at (" << location.x << ", " << location.y << ") is alive" << endl;
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
        cout << "Archer ID: " << baseData.id_num << " at (" << location.x << ", " << location.y << ") is dead" << endl;
    }
}

void Archer::save(ofstream& outfile) {
    Warrior::save(outfile);
}

void Archer::restore(ifstream& infile) {
    Warrior::restore(infile);
    baseData.code = 'A';
}
