#ifndef __GAME_WORLD__
#define __GAME_WORLD__

#include "LinkedList.h"

class Person;

class Game_World {
private:
    Linked_List<Person*> objptr;
    int num_objects;

public:
    Game_World();
    ~Game_World();

    int get_num_objects() const { return num_objects; }
    void set_num_objects(int num);

    Person* get_object_ptr(int id);
    void add_object(Person* ptr);
    void save();
    void restore();
    void clear();
};

#endif // __GAME_WORLD__
