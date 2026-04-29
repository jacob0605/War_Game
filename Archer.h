#ifndef __ARCHER__
#define __ARCHER__

#include "Warrior.h"

class Archer : public Warrior {
public:
    Archer();
    Archer(int id, double x, double y);
    explicit Archer(Game_World* w_ptr);
    Archer(Game_World* w_ptr, int id, double x, double y, const std::string& name);
    virtual ~Archer();

    virtual const char* get_type_name() const noexcept { return "Archer"; }
    virtual void update();
    virtual void display_status();
    virtual void save(std::ofstream& outfile);
    virtual void restore(std::ifstream& infile);

private:
    void initialize();
};

#endif // __ARCHER__
