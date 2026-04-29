#ifndef __WARRIOR__
#define __WARRIOR__

#include "Person.h"

class Warrior : public Person {
public:
    Warrior();
    Warrior(int id, double x, double y);
    explicit Warrior(Game_World* w_ptr);
    Warrior(Game_World* w_ptr, char c, int id, double x, double y, const std::string& name);
    virtual ~Warrior();

    virtual void save(std::ofstream& outfile);
    virtual void restore(std::ifstream& infile);
    virtual void attack_command(int target_id);
    virtual void receive_attack(int attacker_id, int attack_point);

protected:
    void initialize(int in_attack_point = 3, double in_range = 3.0, bool in_attacking = false, int in_target = -1);

    int attack_point;
    double range;
    bool is_attacking;
    int target;
};

#endif // __WARRIOR__
