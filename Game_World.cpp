#include <fstream>
#include <iostream>

#include "Game_World.h"

#include "Archer.h"
#include "Peasant.h"
#include "Person.h"
#include "Soldier.h"

#define SAVE_FILE "objwar.svd"

using namespace std;

Game_World::Game_World() : num_objects(0) {
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

    objptr.add_at_back(ptr);
    num_objects = objptr.get_list_length();
}

void Game_World::save() {
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
}
