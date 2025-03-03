


#ifndef __PERSON__
#define __PERSON__

#include <fstream>
#include "Real_Pair.h"
// #include "Game_World.h"

class Game_World;
class Person {
private:
    Real_Pair delta; // 객체가 이동중에 있을 때, 그 객체의 매 시뮬레이션 시간별 x와 y 좌표 변화량
    std::string name;
protected:
    int id_num; // 객체를 유일하게 나타내는 식별자
    double speed; // 객체가 매 시각마다 이동하는 속도
    Real_Pair location; // 게임보드 이차원 평면상의 객체의 현재 위치
    Real_Pair destination; // 객체가 이동할 경우 최종 목적지의 위치 좌표
    int health; // 이 값이 0이 되면 그 객체는 "죽게 된다"
    bool is_moving; // 객체가 현재 이동중인지 정지 상태인지를 표시함. 이 값이 true 이면 이동중임
    void update_location(); // 객체의 위치를 재계산
    char code; // Person 객체의 타입을 표시해주는 한 문자 출력전용 목적, 기본 초기값은 '?'
    Game_World * world_ptr; // Game_World 클래스 객체를 가리키는 포인터이다. 기본값은 0이다.
public:
    Person(); // default constructor
    Person(Game_World * w_ptr); // 기본 생성자의 기능 + w_ptr 인자를 받아서 world_pointer 값 초기화 수행
    Person(Game_World * w_ptr, char c, int id, double in_x, double in_y, const std::string& _name); // 기본 생성자의 기능 + world_pointer 값 초기화 + Person 객체의 ID와 location 초기화 수행
    virtual ~Person() {}; // 정상적인 메모리 반납을 위해 베이스 클래스의 소멸자를 가상함수로 선언
    virtual void move_command(Real_Pair destination); // 객체를 주어진 좌표 destination으로 움직이도록 시동을 건다.  
    int get_ID() { return id_num; } // 객체의 ID 번호를 돌려준다.
    Real_Pair get_location() { return location; } // 객체의 현제 위치 좌표를  나타내는 Real-Pair 객체를 돌려준다.  
    bool get_alive() { return health>0; } // 객체가 살아있는지 (alive 상태인지) health 값을 기준으로 하여 돌려준다. (true 값을 return하면 alive 상태임을 뜻한다.)
    virtual void update() = 0;
    virtual void set_load(double in_load);
    virtual void display_status();
    virtual void save(std::ofstream & outfile);
    virtual void restore(std::ifstream & infile);
    char get_code() { return code; };
    virtual void attack_command(int target_id);
    virtual void receive_attack(int attacker_id, int attack_point);
    Real_Pair get_delta() { return delta; } // 임의로 추가한 함수, 이동중 공격 명령을 받아 멈춘 경우 공격을 멈추면 다시 이동하게 하기 위함.
    int get_health() { return health; }
    void set_health(int hp) { health = hp; }
    int get_speed() { return health; }
    void set_speed(int s) { speed = s; }
    std::string get_name() const { return name; }
    void set_name(std::string& _name);
};

#include "Game_World.h"

#endif // __PERSON__