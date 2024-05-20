

#ifndef __BOARD_VIEW__
#define __BOARD_VIEW__

// #include "Real_Pair.h"
#include "Peasant.h"
#include "Soldier.h"
#include "Archer.h"

#define maxsize 20

class BoardView {
private:
    int size; // 수직 방향과 수평 방향으로 각각 출력되는 화면상의 점들의 개수
        // 최대 크기는 전역 상수 maxsize의 이름으로 값 20으로 선언
        // size의 기본 초기값은 11
    double scale; // 각 점의 크기를 의미. scale이 5.0 이면, 첫번째 점은 (0,0)에서 (5,5) 까지의 영역을 표시
        // 기본 초기값은 2
    Real_Pair origin; // 화면에 출력되는 그림의 좌측 아래에 해당하는 원점의 좌표
    char display_array[maxsize][maxsize][2];
    void insert(char code, int id, Real_Pair coord); // Peasant와 Soldier 객체를 실제로 문자열 배열에 그려넣는 private 함수
//protected:
public:
    BoardView();
    void set_origin(double x, double y); // BoardView의 원점을 (x,y)로 설정함
    void set_scale (double s); // BoardView의 스케일을 s로 설정
    void set_size (int s); // 출력되는 화면의 크기를 s로 설정
    void clear();
    void plot(Peasant peasant_object); // 다형성 적용 전 구현 함수, 더 이상 안 씀
    void plot(Soldier soldier_object); // 다형성 적용 전 구현 함수, 더 이상 안 씀
    void plot(Person * object);
    void draw();
};

#endif // __BOARD_VIEW__