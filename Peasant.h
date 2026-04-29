#ifndef __PEASANT__
#define __PEASANT__

#include "Person.h"

class Peasant : public Person {
public:
    Peasant();
    Peasant(int id, double x, double y);
    explicit Peasant(Game_World* w_ptr);
    Peasant(Game_World* w_ptr, int id, double x, double y, const std::string& name);
    virtual ~Peasant();

    virtual const char* get_type_name() const noexcept { return "Peasant"; }
    virtual void update();
    virtual void set_load(double in_load);
    virtual void display_status();
    virtual void save(std::ofstream& outfile);
    virtual void restore(std::ifstream& infile);

private:
    void initialize();

    double capacity;
    double load;
    double max_speed;
};

#endif // __PEASANT__
