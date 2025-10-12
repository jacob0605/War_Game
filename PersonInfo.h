#ifndef __PERSON_INFO__
#define __PERSON_INFO__

#include <cstddef>
#include <iostream>
#include "Real_Pair.h"

#define DEFAULT_ID 0
#define DEFAULT_HP 5
#define DEFAULT_SPEED 5
#define DEFAULT_MOVING_STATE false

class Game_World; // Forward Declarations

struct PersonInfo {
    static constexpr std::size_t NAME_CAP = 128;

    // 분류 코드 (사람 종류 구분/표시용)
    char code = '?';

    // 기본 정보
    int id_num = DEFAULT_ID;
    char name[NAME_CAP + 1] = {0};

    // 상태 정보
    int health = DEFAULT_HP;
    double speed = DEFAULT_SPEED;
    bool is_moving = DEFAULT_MOVING_STATE;

    // 위치 정보
    Real_Pair location;
    Real_Pair destination;
    Real_Pair delta;

    // 외부 참조
    Game_World* world_ptr = nullptr;

    void set_name(const char* src);
    const char* get_name() const noexcept { return name; }

    void save(std::ofstream& outfile) const;
    void restore(std::ifstream& infile);
};

#endif // __PERSON_INFO__
