#ifndef __PERSON_INFO__
#define __PERSON_INFO__

#include <iostream>
#include "Real_Pair.h"

#define DEFAULT_ID 0
#define DEFAULT_HP 5
#define DEFAULT_SPEED 5

class Game_World; // Forward Declarations

struct PersonInfo {
    char code = '?';
    std::string name = "defaultName";
    int id_num = DEFAULT_ID;
    int health = DEFAULT_HP;
    double speed = DEFAULT_SPEED;
    Real_Pair delta;
    Real_Pair location;
    Real_Pair destination;
    bool is_moving = false;
    Game_World* world_ptr = nullptr;
};

#endif // __PERSON_INFO__
