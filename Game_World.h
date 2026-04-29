#ifndef __GAME_WORLD__
#define __GAME_WORLD__

#include "LinkedList.h"

class BoardView;
class Person;

class Game_World {
public:
    Game_World();
    ~Game_World();

    int get_num_objects() const { return obj_list.get_list_length(); }
    int get_time() const { return current_time; }
    int get_new_ID() const;

    Person* get_object_ptr(int id) const;
    void add_object(Person* ptr);
    void display_all_objects();
    void update_all_objects();
    void generate_display(BoardView& board) const;
    void start_scan();
    Person* get_next_scan_ptr();
    void advance_time() { ++current_time; }
    void save();
    void restore();
    void clear();

private:
    Linked_List<Person*> obj_list;
    mutable Linked_List_Iterator<Person*> scan_iter;
    int current_time;
};

#endif // __GAME_WORLD__
