#ifndef __GAME_WORLD__
#define __GAME_WORLD__

#include "LinkedList.h"

class Person;
class BoardView;

class Game_World {
private:
    Linked_List<Person*> objptr;
    int num_objects;
    Linked_List_Iterator<Person*> scan_iter;
    bool scan_active;

    void insert_sorted(Person* ptr);

public:
    Game_World();
    ~Game_World();

    int get_num_objects() const { return num_objects; }
    void set_num_objects(int num);

    Person* get_object_ptr(int id);
    void add_object(Person* ptr);
    void update_all_object();
    void generate_display(BoardView& view);
    void start_scan();
    Person* get_next_scan_ptr();
    int get_new_ID();
    void save();
    void restore();
    void clear();
};

#endif // __GAME_WORLD__
