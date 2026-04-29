#ifndef __SOLDIER__
#define __SOLDIER__

#include "Warrior.h"

class Soldier : public Warrior {
public:
    Soldier();
    Soldier(int id, double x, double y);
    explicit Soldier(Game_World* w_ptr);
    Soldier(Game_World* w_ptr, int id, double x, double y, const std::string& name);
    virtual ~Soldier();

    virtual const char* get_type_name() const noexcept { return "Soldier"; }
    virtual void update();
    virtual void display_status();
    virtual void save(std::ofstream& outfile);
    virtual void restore(std::ifstream& infile);
};

#endif // __SOLDIER__
