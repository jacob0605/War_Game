#ifndef __PERSON_INFO__
#define __PERSON_INFO__

#include <iostream>
#include "Real_Pair.h"

#define DEFAULT_ID 0
#define DEFAULT_HP 5
#define DEFAULT_SPEED 5
#define DEFAULT_MOVING_STATE false

class Game_World; // Forward Declarations

struct PersonInfo {
    // 구분 코드 (가장 먼저 저장/복원됨)
    char code = '?';

    // 기본 정보
    int id_num = DEFAULT_ID;
    std::string name = "defaultName";

    // 상태 관련
    int health = DEFAULT_HP;
    double speed = DEFAULT_SPEED;
    bool is_moving = DEFAULT_MOVING_STATE;

    // 위치 관련
    Real_Pair location;
    Real_Pair destination;
    Real_Pair delta;

    // 외부 연결
    Game_World* world_ptr = nullptr;

    void save(std::ofstream& outfile);
    void restore(std::ifstream& infile);
};

#endif // __PERSON_INFO__
