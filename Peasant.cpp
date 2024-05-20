
#include <iostream>
#include <fstream>
#include <cmath>
#include "Peasant.h"

using namespace std;

void Peasant::initialize() {
/*
Peasant 객체의 초기화를 도와주는 private 함수이다.
이함수는 기본 생성자와 3개의 인자를 가진 생성자가 공통으로 호출한다.
이 함수가 하는 일은 구체적으로 다음과 같다.
    health = 10 : Person 클래스에서 정한 default 값을 덮어쓴다 (override) 
    max_speed = 5  
    load = 0 
    capacity = 50 
*/
    health = 10;
    max_speed = 5;
    load = 0;
    capacity = 50;
    // cout<<"initialize function called"<<endl; // 초기화 함수 호출 확인용
    // cout<<"health = "<<health<<", max_speed = "<<max_speed<<", load = "<<load<<", capacity = "<<capacity<<endl;
}

Peasant::Peasant(int id, double x, double y) {
/*
이 생성자는 ID를 id로 설정하고 객체의 초기위치를 (x,y)로 설정한다.
나머지 정보는 private 초기화 함수를 이용해서 초기화한다.
*/
    id_num = id;
    location.x = x;
    location.y = y;
    // cout<< "Peasant Default Constructor called" << endl;
    // cout<< "ID = "<< id <<", x = "<< x <<", y = "<< y <<endl;
    initialize();
}

Peasant::Peasant() : Person() {
/*
나머지 정보는 private 초기화 함수를 이용해서 초기화한다.
*/
    // cout<< "Peasant Default Constructor called" << endl;
    // cout<< "ID = "<< id <<", x = "<< x <<", y = "<< y <<endl;
    initialize();
}

Peasant::Peasant(Game_World * w_ptr) : Person(w_ptr) {
    // world_ptr = w_ptr;
    // cout<< "Peasant Second Constructor called" << endl;
    // cout<< "ID = "<< id <<", x = "<< x <<", y = "<< y <<endl;
    initialize();
}

Peasant::Peasant(Game_World * w_ptr, int id, double x, double y) : Person(w_ptr, 'P', id, x, y) {
    // id_num = id;
    // location.x = x;
    // location.y = y;
    // world_ptr = w_ptr;
    // cout<< "Peasant Third Constructor called" << endl;
    // cout<< "ID = "<< id <<", x = "<< x <<", y = "<< y <<endl;
    initialize();
}

void Peasant::update() {
// Peasant 객체의 update 함수는 Person 클래스로부터 상속받은 update_location 함수를 호출하는 일만 함.
    update_location();
}

void Peasant::set_load(double in_load) {
    /*
    이 함수는 객체의 주어진 짐(load)의 크기와 최대 적재가능부하 용량의 비율에 따라 최대 이동 한계 속도로부터 비례해서 속도를 줄인다.
    그러나, 이동 속도의 최소 한계치는 존재한다.
    구체적으로는 다음 방식으로 속도가 정해진다.
    만약 in_load가 최대 적재가능 부하 용량을 초과하면 
        “Specified load is greater than carrying capacity” 메시지를 출력하고 객체에 아무런 변화를 주지 않는다.
    그렇지 않다면,
        객체의 속도를 다음 식에 의해 계산하다. 
            max_speed - (load/capacity) * max_speed 
        객체의 속도를 위 식으로 계산하되, 최소치는 0.5 미만이 되지 않도록 한다.
        그리고, “With load of 25 can move at speed 2.5” 식의 메시지를 화면에 출력한다. 
    */
    if(in_load > capacity) {
        cout<< "Specified load is greater than carrying capacity" <<endl;
    } else {
        this->load = in_load;
        // cout<<"in_load = "<<in_load<<", load = "<<load<<endl;
        speed = max_speed - (load/capacity) * max_speed;
        if(speed < 0.5) {
            speed = 0.5;
        }
        cout<< "With load of "<< load <<" can move at speed "<< speed << endl;
    }
}

void Peasant::display_status() {
    /*
    이 함수는 객체의 현재 상태, Peasant 객체 고유의 정보들을 출력한다. 예를 들면 다음과 같은 
    메시지를 출력한다. 
    Peasant ID: 1 at (5.16025, 3.77350) is alive  
    Load is 30, health is 10  
    Moving at speed 2 to (10, 7)
    */
    // char alive_dead[2][6] = { "alive", "dead" };
    // int is_alive = 0;
    if(health > 0) { // get_alive() == true
        // is_alive = 0;
        cout<<"Peasant ID: "<< id_num <<" at ("<< location.x << ", " << location.y <<  ") is alive"<<endl;
        cout<<"Load is "<< load <<", health is "<< health << endl;
        cout<<"Moving at speed "<< speed <<" to ("<<destination.x<<", "<<destination.y<<")"<<endl;
    } else {
        // is_alive = 1;
        cout<<"Peasant ID: "<< id_num <<" at ("<< location.x << ", " << location.y <<  ") is dead"<<endl;
    }
    // cout<<"Peasant ID: "<< id_num <<" at ("<< location.x << ", " << location.y <<  ") is "<<alive_dead[is_alive]<<endl;
    // cout<<"Load is "<< load <<", health is "<< health << endl;
    // cout<<"Moving at speed "<< max_speed <<" to ("<<destination.x<<", "<<destination.y<<")";
}

void Peasant::save(ofstream & outfile) {
// 이 함수는 먼저 Person::save(outfile)을 호출해서 Person 클래스에 공통적으로 속하는 정보를 파일에 저장
// 이 클래스에 고유한 멤버 변수들의 정보를 주어진 파일에 저장한다.
    Person::save(outfile); // Person 클래스에 속한 정보들 저장

    // Peasant 클래스의 고유한 정보들 저장
    /*
    private:
    double capacity; // 최대 적재가능 부하 용량치   
    double load; // 현재 객체에 가해진 부하량(짐의 무게) 
    double max_speed; // 이동 가능 속도의 최대 한계치 
    */
    outfile<< capacity <<endl;
    outfile<< load << endl;
    outfile<< max_speed << endl;
}
        
void Peasant::restore(ifstream & infile) {
    Person::restore(infile);
    code = 'P';
    infile >> capacity;
    infile >> load;
    infile >> max_speed;
}