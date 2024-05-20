

#ifndef __GAME_WORLD__
#define __GAME_WORLD__

// #include "Person.h"
// #include "Peasant.h"
// #include "Soldier.h"

class Game_World {
private:
    Person * objptr[10];
    int max_num_objects; // 생성할 수 있는 객체의 총 개수, 기본값 10
    int num_objects; // 현재 존재하는 객체의 수, 기본값 0
// protected
public:
    Game_World(); // 기본 생성자, 멤버 변수들 초기화
    ~Game_World();
    int get_num_objects() { return num_objects; } // 포인터 배열이 현재 가리키는 객체의 개수를 반환한다.
    void set_num_objects(int num);
    bool has_space(); // 추가의 객체를 위한 포인터를 저장할 장소가 배열에 남아 있는지 점검하여 true/false를 반환한다.
    Person * get_object_ptr(int i) { return objptr[i]; }// ID가 i인 객체의 포인터를 반환한다.
    void add_object(Person *ptr); // 원래는 bool 타입이였음, 임의로 void로 타입 변경함.
    void save();
    void restore(); // 원래 bool 타입이였는데 void로 바꿈
    void clear();
};

#endif // __GAME_WORLD__