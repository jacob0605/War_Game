#include <cstring>
#include <fstream>
#include <iostream>

#include "Archer.h"
#include "BoardView.h"
#include "Game_World.h"
#include "Observer.h"
#include "Peasant.h"
#include "Soldier.h"

#define SAVE_FILE "objwar.svd"

using namespace std;

Game_World::Game_World() : scan_iter(), current_time(1) {
    scan_iter.reset_from_list(obj_list);
}

Game_World::~Game_World() {
    clear();
}

int Game_World::get_new_ID() const {
    int candidate = 0;

    while (true) {
        bool used = false;
        Linked_List_Iterator<Person*> iter(const_cast<Linked_List<Person*>&>(obj_list));
        while (!iter.at_end()) {
            Person* person = iter.access_at_iterator();
            if (person != nullptr && person->get_ID() == candidate) {
                used = true;
                break;
            }
            iter.advance();
        }

        if (!used) {
            return candidate;
        }
        ++candidate;
    }
}

Person* Game_World::get_object_ptr(int id) const {
    Linked_List_Iterator<Person*> iter(const_cast<Linked_List<Person*>&>(obj_list));
    while (!iter.at_end()) {
        Person* person = iter.access_at_iterator();
        if (person != nullptr && person->get_ID() == id) {
            return person;
        }
        iter.advance();
    }
    return nullptr;
}

void Game_World::add_object(Person* ptr) {
    if (ptr == nullptr) {
        return;
    }

    Linked_List_Iterator<Person*> iter(obj_list);
    while (!iter.at_end()) {
        Person* current = iter.access_at_iterator();
        if (current != nullptr && std::strcmp(ptr->get_name(), current->get_name()) < 0) {
            iter.insert_before_iterator(ptr);
            return;
        }
        iter.advance();
    }

    obj_list.add_at_back(ptr);
}

void Game_World::display_all_objects() {
    Linked_List_Iterator<Person*> iter(obj_list);
    while (!iter.at_end()) {
        Person* person = iter.access_at_iterator();
        if (person != nullptr) {
            person->display_status();
        }
        iter.advance();
    }
}

void Game_World::update_all_objects() {
    Linked_List_Iterator<Person*> iter(obj_list);
    while (!iter.at_end()) {
        Person* person = iter.access_at_iterator();
        if (person != nullptr) {
            person->update();
        }
        iter.advance();
    }

    iter.reset_from_list(obj_list);
    while (!iter.at_end()) {
        Person* person = iter.access_at_iterator();
        if (person != nullptr && !person->get_alive()) {
            delete person;
            iter.remove_at_iterator();
        } else {
            iter.advance();
        }
    }

    scan_iter.reset_from_list(obj_list);
}

void Game_World::generate_display(BoardView& board) const {
    Linked_List_Iterator<Person*> iter(const_cast<Linked_List<Person*>&>(obj_list));
    while (!iter.at_end()) {
        board.plot(iter.access_at_iterator());
        iter.advance();
    }
}

void Game_World::start_scan() {
    scan_iter.reset_from_list(obj_list);
}

Person* Game_World::get_next_scan_ptr() {
    if (scan_iter.at_end()) {
        return nullptr;
    }

    Person* current = scan_iter.access_at_iterator();
    scan_iter.advance();
    return current;
}

void Game_World::save() {
    ofstream save_file(SAVE_FILE);
    if (!save_file.is_open()) {
        cerr << "Error, Failed to open file " << SAVE_FILE << endl;
        return;
    }

    Linked_List<Person*> copy_list(obj_list);
    obj_list = copy_list;
    scan_iter.reset_from_list(obj_list);

    save_file << current_time << endl;
    save_file << get_num_objects() << endl;

    Linked_List_Iterator<Person*> iter(obj_list);
    while (!iter.at_end()) {
        Person* person = iter.access_at_iterator();
        if (person != nullptr) {
            person->save(save_file);
        }
        iter.advance();
    }
}

void Game_World::restore() {
    ifstream save_file(SAVE_FILE);
    if (!save_file.is_open()) {
        cerr << "Error, Failed to open file " << SAVE_FILE << endl;
        return;
    }

    clear();

    int object_count = 0;
    save_file >> current_time;
    save_file >> object_count;

    for (int i = 0; i < object_count; ++i) {
        char type = '?';
        save_file >> type;

        Person* person = nullptr;
        switch (type) {
            case 'P':
                person = new Peasant(this);
                break;
            case 'S':
                person = new Soldier(this);
                break;
            case 'A':
                person = new Archer(this);
                break;
            case 'O':
                person = new Observer(this);
                break;
            default:
                cerr << "Unknown object code in save file: " << type << endl;
                return;
        }

        person->restore(save_file);
        add_object(person);
    }

    scan_iter.reset_from_list(obj_list);
}

void Game_World::clear() {
    Linked_List_Iterator<Person*> iter(obj_list);
    while (!iter.at_end()) {
        Person* person = iter.access_at_iterator();
        delete person;
        iter.remove_at_iterator();
    }
    scan_iter.reset_from_list(obj_list);
}
