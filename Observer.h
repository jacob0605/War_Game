#ifndef __OBSERVER__
#define __OBSERVER__

#include "LinkedList.h"
#include "Person.h"

class Observer : public Person {
public:
    Observer(const Observer&) = delete;
    Observer& operator=(const Observer&) = delete;

    Observer();
    explicit Observer(Game_World* w_ptr);
    Observer(Game_World* w_ptr, int id, double x, double y, const std::string& name);
    virtual ~Observer();

    virtual const char* get_type_name() const noexcept { return "Observer"; }
    virtual void update();
    virtual void display_status();
    virtual void move_command(Real_Pair new_destination);
    virtual void save(std::ofstream& outfile);
    virtual void restore(std::ifstream& infile);

private:
    void initialize();
    void start_next_destination();
    void report_visible_objects();

    Linked_List<Real_Pair> destinations;
};

#endif // __OBSERVER__
