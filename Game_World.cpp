#include <fstream>
#include <iostream>
#include <set>
#include <cstring>

#include "Game_World.h"

#include "Archer.h"
#include "BoardView.h"
#include "Peasant.h"
#include "Person.h"
#include "Soldier.h"

#define SAVE_FILE "objwar.svd"

using namespace std;

Game_World::Game_World() : num_objects(0), scan_active(false) {
    scan_iter.invalidate();
#ifdef _DEBUG
    cout << "Game_World constructor called" << endl;
#endif
}

Game_World::~Game_World() {
    clear();
#ifdef _DEBUG
    cout << "Game_World destructor called" << endl;
#endif
}

void Game_World::set_num_objects(int num) {
    num_objects = num;
}

void Game_World::insert_sorted(Person* ptr) {
    if (!ptr) {
        return;
    }

    if (objptr.get_list_length() == 0) {
        objptr.add_at_back(ptr);
        return;
    }

    Linked_List_Iterator<Person*> iter(objptr);
    while (!iter.at_end()) {
        Person* current = iter.access_at_iterator();
        if (!current) {
            iter.insert_before_iterator(ptr);
            return;
        }
        int cmp = std::strcmp(ptr->get_name(), current->get_name());
        if (cmp < 0 || (cmp == 0 && ptr->get_ID() < current->get_ID())) {
            iter.insert_before_iterator(ptr);
            return;
        }
        iter.advance();
    }
    objptr.add_at_back(ptr);
}

Person* Game_World::get_object_ptr(int id) {
    Linked_List_Iterator<Person*> iter(objptr);
    while (!iter.at_end()) {
        Person* person = iter.access_at_iterator();
        if (person && person->get_ID() == id) {
            return person;
        }
        iter.advance();
    }
#ifdef _DEBUG
    cout << "There is no Person that have such ID" << endl;
#endif
    return nullptr;
}

void Game_World::add_object(Person* ptr) {
    if (!ptr) {
        return;
    }

    insert_sorted(ptr);
    num_objects = objptr.get_list_length();
    scan_active = false;
    scan_iter.invalidate();
}

void Game_World::update_all_object() {
    Linked_List_Iterator<Person*> iter(objptr);
    while (!iter.at_end()) {
        Person* person = iter.access_at_iterator();
        if (!person) {
            iter.remove_at_iterator();
            continue;
        }
        person->update();
        if (!person->get_alive()) {
            delete person;
            iter.remove_at_iterator();
        } else {
            iter.advance();
        }
    }
    num_objects = objptr.get_list_length();
    scan_active = false;
    scan_iter.invalidate();
}

void Game_World::generate_display(BoardView& view) {
    Linked_List_Iterator<Person*> iter(objptr);
    while (!iter.at_end()) {
        Person* person = iter.access_at_iterator();
        if (person) {
            view.plot(person);
        }
        iter.advance();
    }
}

void Game_World::start_scan() {
    scan_iter.reset_from_list(objptr);
    scan_active = true;
}

Person* Game_World::get_next_scan_ptr() {
    if (!scan_active) {
        return nullptr;
    }
    if (scan_iter.at_end()) {
        scan_active = false;
        return nullptr;
    }
    Person* result = scan_iter.access_at_iterator();
    scan_iter.advance();
    if (scan_iter.at_end()) {
        scan_active = false;
    }
    return result;
}

int Game_World::get_new_ID() {
    std::set<int> used_ids;
    Linked_List_Iterator<Person*> iter(objptr);
    while (!iter.at_end()) {
        Person* person = iter.access_at_iterator();
        if (person) {
            used_ids.insert(person->get_ID());
        }
        iter.advance();
    }
    int candidate = 0;
    while (used_ids.count(candidate) != 0) {
        ++candidate;
    }
    return candidate;
}

void Game_World::save() {
    Linked_List<Person*> copy_list(objptr);
    objptr = copy_list;
    num_objects = objptr.get_list_length();
    scan_active = false;
    scan_iter.invalidate();

    ofstream saveFile(SAVE_FILE);
    if (!saveFile.is_open()) {
        cerr << "Error, Failed to open file " << SAVE_FILE << " at line " << __LINE__ << " in " << __FILE__ << "\n";
        return;
    }

    num_objects = objptr.get_list_length();
    saveFile << num_objects << endl;

    Linked_List_Iterator<Person*> iter(objptr);
    while (!iter.at_end()) {
        Person* person = iter.access_at_iterator();
        if (person) {
            person->save(saveFile);
        }
        iter.advance();
    }

    saveFile.close();
}

void Game_World::restore() {
    clear();

    ifstream saveFile(SAVE_FILE);
    if (!saveFile.is_open()) {
        cerr << "Error, Failed to open file " << SAVE_FILE << " at line " << __LINE__ << " in " << __FILE__ << "\n";
        return;
    }

    int expected_count = 0;
    saveFile >> expected_count;

    for (int i = 0; i < expected_count; ++i) {
        char type = '?';
        saveFile >> type;

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
            default:
                person = new Peasant(this);
                break;
        }

        if (!person) {
            continue;
        }

        person->restore(saveFile);
        add_object(person);
    }

    saveFile.close();
    num_objects = objptr.get_list_length();
    scan_active = false;
    scan_iter.invalidate();
}

void Game_World::clear() {
    Linked_List_Iterator<Person*> iter(objptr);
    while (!iter.at_end()) {
        Person* person = iter.access_at_iterator();
        delete person;
        iter.advance();
    }

    objptr.clear();
    num_objects = 0;
    scan_active = false;
    scan_iter.invalidate();
}
