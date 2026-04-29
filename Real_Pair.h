#ifndef __REAL_PAIR__
#define __REAL_PAIR__

#include <iosfwd>

class Real_Pair {
public:
    double x;
    double y;

    Real_Pair(double in_x = 0, double in_y = 0);
    Real_Pair(const Real_Pair& other);
    ~Real_Pair();
};

Real_Pair operator+(const Real_Pair& lhs, const Real_Pair& rhs);
Real_Pair operator-(const Real_Pair& lhs, const Real_Pair& rhs);
Real_Pair operator/(const Real_Pair& lhs, double d);
Real_Pair operator*(double d, const Real_Pair& rhs);
Real_Pair operator*(const Real_Pair& lhs, double d);
std::ostream& operator<<(std::ostream& os, const Real_Pair& rhs);
std::istream& operator>>(std::istream& is, Real_Pair& rhs);
double distance(Real_Pair r1, Real_Pair r2);

#endif // __REAL_PAIR__
