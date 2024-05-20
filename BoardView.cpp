


#include <iostream>
#include <iomanip>
#include "BoardView.h"

using namespace std;

BoardView::BoardView() {
    size = 11;
    scale = 2;
    // cout<<"BoardView Constructor called"<<endl;
}

void BoardView::insert(char code, int id, Real_Pair coord) {
    /*
    Peasant와 Soldier 객체를 실제로 문자열 배열에 그려넣는 private 함수
    이 함수는 현재의 scale과 origin 값을 이용하여
    이차원 배열 display_array[][]상의 어느 위치에 주어진 객체의 위치 coord를 나타내야 할지를
    display_array의 인덱스 (i,j)를 계산한다.
    display_array[i][j][0]에는 code를 대입하고,
    display_array[i][j][1]에는 정수형 ID를 문자로 변환하여 대입한다.
    객체의 좌표 Coord가 (x,y) 의 실수값 좌표로 주어지므로
    이를 배열상의 원소의 위치를 나타내는 정수값으로 변환하기 위해서는 다음 식을 사용한다. 
        (coord - origin) / scale;
    만약에 계산 결과의 (i,j)가 범위를 벗어나면 문자를 배열에 저장하지 않고
    다음과 같은 식의 메시지를 출력한다.
        "Object S3 is outside the display"
    만약에 같은 자리에 두개 이상의 객체가 겹쳐서 그려진다면 '*'와 ' '로 표시한다.
    */
    // display_array[i][j][0] = code;
    // display_array[i][j][1] = (char)id;
    /*
    Y축
        일반항 = temp[1] - i * scale
        범위 : i = [0,size-1]
    X축
        temp[0] + i * scale
        i = [0,size-1]
    */
    Real_Pair temp;
    temp = (coord - origin) / scale; // 
    int x_location = (int) temp.x;
    int y_location = (int) temp.y;
    // [origin.x, origin.x + (size-1) * scale]
    // [origin.y, origin.y + (size-1) * scale]

    if(x_location > maxsize || y_location > maxsize || x_location < 0 || y_location < 0) {
        cout<<"Object "<<code<<id<<" is outside the display"<<endl;
    } else {
        if(display_array[x_location][y_location][0]=='.') { // 현 좌표에 아무것도 없음
            display_array[x_location][y_location][0] = code;
            // display_array[x_location][y_location][1] = (char)id;
            display_array[x_location][y_location][1] = id + '0';
        } else { // 현 좌표에 어느 객체가 위치함 == 두개 이상의 객체가 겹침
            display_array[x_location][y_location][0] = '*'; 
            display_array[x_location][y_location][1] = ' ';
        }
    }
}

void BoardView::set_origin(double x, double y) {
    // BoardView의 원점을 (x,y)로 설정함
    origin.x = x;
    origin.y = y;
    cout<<"set board origin to ("<< x <<", "<< y <<")"<<endl;
}

void BoardView::set_scale (double s) {
    // BoardView의 스케일을 s로 설정
    scale = s;
    cout<<"set board scale to "<< scale <<endl;
}

void BoardView::set_size (int s) {
    if(s > 20 || s < 3) {
        cout<<"board size should in [3, 20]" << endl;
    } else {
        size = s;
        cout<<"set board size to "<< size <<endl;
    }
    
}

void BoardView::clear() {
    /*
    이 함수는 display_array 상의 모든 객체들을 지워서 빈 보드판을 만든다.
    즉, 모든 좌표의 출력을 ‘.’ (마침표)문자와 ‘  ’(공백)문자로 대체한다. 
    */
    for(int i = 0; i<maxsize; i++) {
        for(int j=0; j<maxsize; j++) {
            display_array[i][j][0] = '.';
            display_array[i][j][1] = ' ';
        }
    }
}

// void BoardView::plot(Peasant peasant_object) {
//     // 이 함수는 다른 private insert 함수를 사용하여 Peasant 객체 peasant_object 를 보드 상에 삽입하여 그려 넣는다.
//     // void BoardView::insert(char code, int id, Real_Pair coord);
//     int id = peasant_object.get_ID();
//     Real_Pair coord;
//     coord = peasant_object.get_location();
//     insert('P', id, coord);
// }

// void BoardView::plot(Soldier soldier_object) {
//     /*
//     이 함수는 다른 private insert 함수를 사용하여 Peasant 객체
//     peasant_object 를 보드 상에 삽입하여 그려 넣는다.
//     이 함수는 Peasant 를 위한 plot 함수와 아울러서 함수의 중첩 
//     (overloading) 함수가 된다. 그러나, 이번 과제에서는
//     함수의 다형성(polymorphism) 구현을 목적으로 하지 않기 때문에
//     단지 별개의 함수로 구현만 해 둔다. 
//     */
//     int id = soldier_object.get_ID();
//     Real_Pair coord;
//     coord = soldier_object.get_location();
//     insert('S', id, coord);
// }

void BoardView::plot(Person * object) {
    // 이 함수는 다른 private insert 함수를 사용하여 Person 객체 object 를 보드 상에 삽입하여 그려 넣는다.
    // void BoardView::insert(char code, int id, Real_Pair coord);
    int id = object->get_ID();
    Real_Pair coord;
    coord = object->get_location();
    char code = object->get_code();
    insert(code, id, coord);
}

void BoardView::draw() { // 기본 출력: 좌표 및 객체(예, S3) 출력만 구현해둠, 추후 수정할것.
    double temp[2] = { origin.x, origin.y + scale * (size-1) };
    cout<<"Display size: "<< size <<", scale:  "<< scale <<", origin: "<< origin <<endl;
    for(int j=size-1; j>=0; j--) { 
        if(j%2==0) {
            cout<<setw(2)<<temp[1]<<" "; // Y축 좌표 출력 (너비 2칸, 우측 정렬)

        } else {
            cout<<"   "; // 숫자들과의 정렬을 맞추기 위한 여백
        }
        for(int i=0; i<size; i++) { // size 변수의 크기만큼 반복 == 게임 보드의 크기에 맞게 출력
            cout<<display_array[i][j][0]<<display_array[i][j][1]; // ". " 혹은 "P1" 같은 게임보드 내용 출력
        }
        cout<<endl;
        if(j!=0) { temp[1] -= scale; } // Y축 좌표 값 변경
    }
    cout<<"   ";
    for(int i=0; i<size; i++) {
        if(i%2==0) {
            cout<<setw(2)<<temp[0]; // X축 좌표 출력
        } else {
            cout<<"  ";
        }
        temp[0] += scale; // X축 좌표 값 변경
    }
}