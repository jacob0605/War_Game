#include <iostream>

#include "Observer.h"
#include "Game_World.h"

using namespace std;

void Observer::initialize() {
    code = 'O';
    health = 5;
    speed = 5.0;
}

Observer::Observer() : Person(nullptr, 'O', 0, 0, 0, "Observer") {
    initialize();
}

Observer::Observer(Game_World* w_ptr) : Person(w_ptr, 'O', 0, 0, 0, "Observer") {
    initialize();
}

Observer::Observer(Game_World* w_ptr, int id, double x, double y, const string& in_name)
    : Person(w_ptr, 'O', id, x, y, in_name) {
    initialize();
}

Observer::~Observer() {
    cout << "Observer " << get_name() << " is deallocated" << endl;
}

void Observer::start_next_destination() {
    Linked_List_Iterator<Real_Pair> iter(destinations);
    if (iter.at_end()) {
        moving = false;
        delta = Real_Pair(0, 0);
        return;
    }

    Person::move_command(iter.access_at_iterator());
}

void Observer::report_visible_objects() {
    if (world_ptr == nullptr) {
        return;
    }

    if (!moving && destinations.get_list_length() == 0) {
        return;
    }

    world_ptr->start_scan();
    while (Person* seen = world_ptr->get_next_scan_ptr()) {
        if (seen == this) {
            continue;
        }

        if (distance(location, seen->get_location()) <= 10.0) {
            cout << "I see " << seen->get_code() << seen->get_ID() << "(\"" << seen->get_name()
                 << "\") at location " << seen->get_location() << endl;
        }
    }
}

void Observer::update() {
    if (!get_alive()) {
        return;
    }

    if (moving) {
        update_location();
        if (!moving) {
            Linked_List_Iterator<Real_Pair> iter(destinations);
            if (!iter.at_end()) {
                iter.remove_at_iterator();
            }

            if (destinations.get_list_length() > 0) {
                start_next_destination();
            }
        }
    } else if (destinations.get_list_length() > 0) {
        start_next_destination();
    }

    report_visible_objects();
}

void Observer::display_status() {
    cout << "Observer " << code << id_num << "(\"" << get_name() << "\") at " << location
         << " is " << (get_alive() ? "alive" : "dead") << endl;

    if (!get_alive()) {
        return;
    }

    cout << (moving ? "Moving" : "Waiting") << ", pending destinations: "
         << destinations.get_list_length() << endl;
}

void Observer::move_command(Real_Pair new_destination) {
    if (!get_alive()) {
        cout << "I'm dead - can't move " << code << id_num << "(\"" << get_name() << "\")" << endl;
        return;
    }

    destinations.add_at_back(new_destination);
    if (!moving && destinations.get_list_length() == 1) {
        start_next_destination();
    }
}

void Observer::save(ofstream& outfile) {
    Person::save(outfile);
    outfile << destinations.get_list_length() << endl;

    Linked_List_Iterator<Real_Pair> iter(destinations);
    while (!iter.at_end()) {
        outfile << iter.access_at_iterator() << endl;
        iter.advance();
    }
}

void Observer::restore(ifstream& infile) {
    code = 'O';
    destinations.clear();
    Person::restore(infile);

    int count = 0;
    infile >> count;
    for (int i = 0; i < count; ++i) {
        Real_Pair point;
        infile >> point;
        destinations.add_at_back(point);
    }
}
