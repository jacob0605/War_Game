
#include <iostream>
#include <cmath>
#include "Real_Pair.h"

using namespace std;

// Real_Pair::Real_Pair(double in_x, double in_y) { // 생성자
//     this->x = in_x;
//     this->y = in_y;
//     // cout<<"Real_Pair Constructor called"<<endl; // 생성자 호출 확인용
// }

Real_Pair::Real_Pair(double in_x, double in_y) : x(in_x), y(in_y) { // 생성자
    // this->x = in_x;
    // this->y = in_y;
    // cout<<"Real_Pair Constructor called"<<endl; // 생성자 호출 확인용
}

Real_Pair::Real_Pair(const Real_Pair & other) { // 복사 생성자
    if(this != &other) {
        this->x = other.x;
        this->y = other.y;
        // cout<<"Real_Pair Copy Constructor called"<<endl; // 복사 생성자 호출 확인용
    }
}

Real_Pair::~Real_Pair() { // 소멸자
    // cout<<"Real_Pair Destructor called"<<endl; // 소멸자 호출 확인용
}

Real_Pair operator+(const Real_Pair& lhs, const Real_Pair& rhs) {
    Real_Pair temp;
    temp.x = lhs.x + rhs.x;
    temp.y = lhs.y + rhs.y;
    return temp;
}

Real_Pair operator-(const Real_Pair& lhs, const Real_Pair& rhs) {
    Real_Pair temp;
    temp.x = lhs.x - rhs.x;
    temp.y = lhs.y - rhs.y;
    return temp;
}

Real_Pair operator/(const Real_Pair& lhs, double d) {
    Real_Pair temp;
    temp.x = lhs.x / d;
    temp.y = lhs.y / d;
    return temp;
}

Real_Pair operator*(double d, const Real_Pair& rhs) {
    Real_Pair temp;
    temp.x = d * rhs.x;
    temp.y = d * rhs.y;
    return temp;
}

Real_Pair operator*(const Real_Pair& lhs, double d) {
    Real_Pair temp;
    temp.x = lhs.x * d;
    temp.y = lhs.y * d;
    return temp;
}

ostream& operator<<(ostream& os, const Real_Pair & rhs) {
    return os << "(" << rhs.x << ", " << rhs.y << ")";
}

istream& operator>>(istream& is, Real_Pair & rhs) { // 임의로 추가한 함수. 연산자 오버로딩으로 파일에 적은걸 역으로 읽어서 저장함
    /*
    연산자 오버로딩으로 Real_Pair 객체의 값을 편하게 출력할 수 있다.
    그리고 이는 파일에 입력할때도 동일하게 작동함을 확인했다.
    그렇다면 이렇게 파일에 입력한 것을 역으로 읽어서 객체에 저장할 수도 있지 않을까?
    코드는 챗gpt로 생성했다.
    */
    char left_paren, comma, right_paren;
    double x_val, y_val;
    if (is >> left_paren >> x_val >> comma >> y_val >> right_paren && left_paren == '(' && comma == ',' && right_paren == ')') {
        rhs.x = x_val;
        rhs.y = y_val;
    } 
    // else {
    //     // 입력이 잘못된 경우 에러 처리
    //     is.setstate(ios_base::failbit);
    // }

    return is;
}

double distance(Real_Pair r1, Real_Pair r2) {
    return sqrt(pow((r1.x - r2.x), 2) + pow((r1.y - r2.y), 2));
}