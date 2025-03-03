

#ifndef __PEASANT__
#define __PEASANT__

#include "Person.h"

class Peasant : public Person {
private:
    double capacity; // 최대 적재가능 부하 용량치   
    double load; // 현재 객체에 가해진 부하량(짐의 무게) 
    double max_speed; // 이동 가능 속도의 최대 한계치 
    void initialize(); 
// protected:

public:
    Peasant();
    Peasant(int id, double x, double y); // 객체의 ID를 id로 설정, 초기위치를 (x,y)로 설정. 나머지 정보는 private 초기화 함수를 이용 
    Peasant(Game_World * w_ptr);
    Peasant(Game_World * w_ptr, int id, double x, double y, const std::string& _name);
    virtual void update(); // 객체의 상태를 매 time step 마다 갱신
    virtual void set_load(double in_load);
    virtual void display_status();
    virtual void save(std::ofstream & outfile);
        // 이 함수는 먼저 Person::save(outfile)을 호출해서 Person 클래스에 공통적으로 속하는 정보를 파일에 저장
        // 이 클래스에 고유한 멤버 변수들의 정보를 주어진 파일에 저장한다.
    virtual void restore(std::ifstream & infile);
};

#endif // __PEASANT__