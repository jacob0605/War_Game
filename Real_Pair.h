


#ifndef __REAL_PAIR__
#define __REAL_PAIR__

// #include <iostream>
// #include <cmath>


class Real_Pair { // 게임 보드를 나타내는 이차원 평면 상에서의 좌표
public:
    double x; // x 좌표의 x 축 값
    double y; // y 좌표의 y 축 값
    // 기본 생성자 (default constructor)는 x와 y를 (0,0)으로 초기화한다.
    Real_Pair(double in_x = 0, double in_y = 0); // x와 y의 초기값을 in_x와 in_y로 설정하는 생성자
    Real_Pair(const Real_Pair & other); // copy constructor
    ~Real_Pair(); // destructor
};

// 연산자 오버로딩 : 일반 함수로 정의
Real_Pair operator+(const Real_Pair& lhs, const Real_Pair& rhs);
Real_Pair operator-(const Real_Pair& lhs, const Real_Pair& rhs);
Real_Pair operator/(const Real_Pair& lhs, double d);
Real_Pair operator*(double d, const Real_Pair& rhs);
Real_Pair operator*(const Real_Pair& lhs, double d);
std::ostream& operator<<(std::ostream& os, const Real_Pair & rhs);
std::istream& operator>>(std::istream& is, Real_Pair & rhs);
double distance(Real_Pair r1, Real_Pair r2); // 두 점간의 Cartesian (ordinary) distance를 계산하여 반환

#endif // __REAL_PAIR__
