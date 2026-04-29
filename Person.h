#ifndef __PERSON__
#define __PERSON__

#include <fstream>
#include <string>

#include "Real_Pair.h"

class Game_World;

class Person {
public:
    Person(const Person&) = delete;
    Person& operator=(const Person&) = delete;
    virtual ~Person();

    char get_code() const noexcept { return code; }
    int get_ID() const noexcept { return id_num; }
    const char* get_name() const noexcept { return name != nullptr ? name : ""; }
    int get_health() const noexcept { return health; }
    double get_speed() const noexcept { return speed; }
    bool get_alive() const noexcept { return health > 0; }
    bool is_moving() const noexcept { return moving; }
    Real_Pair get_location() const noexcept { return location; }
    Real_Pair get_destination() const noexcept { return destination; }
    Real_Pair get_delta() const noexcept { return delta; }

    void set_health(int hp) { health = hp; }
    void set_speed(double new_speed) { speed = new_speed; }

    virtual const char* get_type_name() const noexcept = 0;
    virtual void update() = 0;
    virtual void display_status();
    virtual void move_command(Real_Pair new_destination);
    virtual void set_load(double in_load);
    virtual void attack_command(int target_id);
    virtual void receive_attack(int attacker_id, int attack_point);
    virtual void save(std::ofstream& outfile);
    virtual void restore(std::ifstream& infile);

protected:
    explicit Person(Game_World* w_ptr = nullptr);
    Person(Game_World* w_ptr, char c, int id, double in_x, double in_y, const std::string& in_name);

    void set_name(const std::string& in_name);
    void update_location();

    Game_World* world_ptr;
    char code;
    int id_num;
    char* name;
    int health;
    double speed;
    bool moving;
    Real_Pair location;
    Real_Pair destination;
    Real_Pair delta;
};

#endif // __PERSON__
