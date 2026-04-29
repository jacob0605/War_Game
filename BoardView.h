#ifndef __BOARD_VIEW__
#define __BOARD_VIEW__

#include "Real_Pair.h"

#define maxsize 20

class Person;

class BoardView {
public:
    BoardView();

    void set_origin(double x, double y);
    void set_scale(double s);
    void set_size(int s);
    void clear();
    void plot(const Person* object);
    void draw();

private:
    void insert(char code, int id, Real_Pair coord);

    int size;
    double scale;
    Real_Pair origin;
    char display_array[maxsize][maxsize][2];
};

#endif // __BOARD_VIEW__
