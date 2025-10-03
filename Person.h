#ifndef __PERSON__
#define __PERSON__

#include <fstream>
#include "Real_Pair.h"
#include "PersonInfo.h"
// #include "Game_World.h"

class Game_World;
class Person {
protected:
    PersonInfo baseData;
    void update_location();

public:
    Person() {};
    Person(Game_World* w_ptr);
    Person(Game_World* w_ptr, char c, int id, double in_x, double in_y, const std::string& _name);
    virtual ~Person() {};

    // 기본 정보
    char get_code() const noexcept { return baseData.code; }
    int get_ID() { return baseData.id_num; }
    std::string get_name() const noexcept { return baseData.name; }
    void set_name(const std::string& _name) { baseData.name = _name; }
    int get_health() const noexcept { return baseData.health; }
    void set_health(int hp) { baseData.health = hp; }
    bool get_alive() { return baseData.health > 0; }
    double get_speed() const noexcept { return baseData.speed; }
    void set_speed(double s) { baseData.speed = s; }
    bool is_moving() const noexcept { return baseData.is_moving; }
    Real_Pair get_location() const noexcept { return baseData.location; }
    Real_Pair get_destination() const noexcept { return baseData.destination; }
    Real_Pair get_delta() const noexcept { return baseData.delta; }

    // 동작 관련 (순수 가상 또는 virtual)
    virtual void update() = 0;
    virtual void display_status();
    virtual void move_command(Real_Pair destination);
    virtual void set_load(double in_load);
    virtual void attack_command(int target_id);
    virtual void receive_attack(int attacker_id, int attack_point);

    // 저장/복원
    virtual void save(std::ofstream& outfile);
    virtual void restore(std::ifstream& infile);
};

#include "Game_World.h"

#endif // __PERSON__
