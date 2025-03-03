

#ifndef __ARCHER__
#define __ARCHER__

#include "Warrior.h"

class Archer : public Warrior {
// private:
//     int attack_point; // 공격할 때 상대방에게 가하는 타격의 크기이다. 초기값은 3이다.
//     double range; // 공격하는 사정거리이다. 이 값 이내에 상대가 위치하고 있어야 공격이 가능하다. 초기값은 3.0이다.
//     bool is_attacking; // 현재 이 객체가 공격중인 상태인지 나타낸다. 초기값은 false이다.
//     int target; // 공격중인 경우에 공격 대상의 ID 값을 나타낸다. 초기값은 -1이다.
//     void initialize(); 
private:
    void virtual initialize(); 
// protected:
public:
    Archer();
    Archer(int id, double x, double y);
    Archer(Game_World * w_ptr); // 기본 생성자의 기능 + w_ptr 인자를 받아서 world_pointer 값 초기화 수행
    Archer(Game_World * w_ptr, int id, double x, double y, const std::string& _name); // 기본 생성자의 기능 + world_pointer 값 초기화 + Person 객체의 ID와 location 초기화 수행
    virtual void update(); // 객체의 상태를 갱신한다. 자세한 내용은 다음의 [객체 이동 방법]에서 설명한다.  
    virtual void display_status();
    virtual void save(std::ofstream & outfile); 
    virtual void restore(std::ifstream & infile);
};

#endif // __ARCHER__