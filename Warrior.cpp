#include <iostream>
#include <fstream>
#include <cmath>
#include "Warrior.h"

using namespace std;

void Warrior::initialize(int _attack_point, double _range, bool is_attack, int _target) {
    this->attack_point = _attack_point; // 공격할 때 상대방에게 가하는 타격의 크기이다. 초기값은 3이다.
    this->range = _range; // 공격하는 사정거리이다. 이 값 이내에 상대가 위치하고 있어야 공격이 가능하다. 초기값은 3.0이다.
    this->is_attacking = is_attack; // 현재 이 객체가 공격중인 상태인지 나타낸다. 초기값은 false이다.
    this->target = _target; // 공격중인 경우에 공격 대상의 ID 값을 나타낸다. 초기값은 -1이다.
    // cout<<"Soldier initialize function called"<<endl; // 초기화 함수 호출 확인용
}

Warrior::Warrior(int id, double x, double y) {
    id_num = id;
    location.x = x;
    location.y = y;
    initialize();
    // cout<<"Soldier Default Constructor called"<<endl; // 생성자 작동 확인용 코드
}

Warrior::Warrior() : Person() {
    initialize();
    // cout<<"Soldier Default Constructor called"<<endl; // 생성자 작동 확인용 코드
}

Warrior::Warrior(Game_World * w_ptr) : Person(w_ptr) {
    // 기본 생성자의 기능 + w_ptr 인자를 받아서 world_pointer 값 초기화 수행
    // world_ptr = w_ptr;
    initialize();
    // cout<<"Soldier Second Constructor called"<<endl; // 생성자 작동 확인용 코드
}

// Person(Game_World * w_ptr, char c, int id, double in_x, double in_y);
Warrior::Warrior(Game_World * w_ptr, char c, int id, double x, double y) : Person(w_ptr, c, id, x, y) {
    // 기본 생성자의 기능 + world_pointer 값 초기화 + Person 객체의 ID와 location 초기화 수행
    // id_num = id;
    // location.x = x;
    // location.y = y;
    // world_ptr = w_ptr;
    initialize();
    // cout<<"Soldier Third Constructor called"<<endl; // 생성자 작동 확인용 코드
}

Warrior::~Warrior() {
    // cout<<"Soldier Default Constructor called"<<endl; // 생성자 작동 확인용 코드
}


void Warrior::save(ofstream & outfile) {
    Person::save(outfile);
    // 이 함수는 Soldier 객체에 새로 추가된 멤버 변수값들을 저장하기 위해서 수정되어야 한다.
    /*
    attack_point = 3; // 공격할 때 상대방에게 가하는 타격의 크기이다. 초기값은 3이다.
    range = 3.0; // 공격하는 사정거리이다. 이 값 이내에 상대가 위치하고 있어야 공격이 가능하다. 초기값은 3.0이다.
    is_attacking = false; // 현재 이 객체가 공격중인 상태인지 나타낸다. 초기값은 false이다.
    target = -1; // 공격중인 경우에 공격 대상의 ID 값을 나타낸다. 초기값은 -1이다.
    */
    outfile<< attack_point <<endl;
    outfile<< range <<endl;
    outfile<< is_attacking <<endl;
    outfile<< target <<endl;
}

void Warrior::restore(ifstream & infile) {
    Person::restore(infile);
    // code = 'S';
    // 이 함수도 Soldier 객체에 새로 추가된 멤버 변수들의 값을 복귀하기 위해서 수정되어야 한다.
    infile >> attack_point;
    infile >> range;
    infile >> is_attacking;
    infile >> target;
}

void Warrior::attack_command(int target_id) {
    /*
    Soldier 클래스의 이 함수는 만약에 이 객체(자신)와 목표물(target_id)이 모두 살아있고
    목표물이 사정거리 안에 있다면 목표물을 향해서 공격을 개시한다.
    공격이 시작되면 일단 is_attacking이란 멤버 변수(새로 선언되는 Soldier의 private 멤버)를 true로 바꾸고,
    목표물의 ID(target_id)를 target이란 멤버 변수에 저장한다.
    만약, 공격자 자신이 이동중이였다면 이동을 즉시 멈춘다.
    만약에 자신이나 목표물이 이미 죽은 상태라면 (health <= 0)이면,
    단지 공격할 수 없다는 메시지만을 화면에 출력시킨다.
    */

    cout<< "attack command is called" << endl;
    // double distance(Real_Pair r1, Real_Pair r2); // 두 점간의 Cartesian (ordinary) distance를 계산하여 반환
    if(this->get_alive() && world_ptr->get_object_ptr(target_id)->get_alive()) {
        if(distance(this->get_location(), world_ptr->get_object_ptr(target_id)->get_location()) <= range) {
            is_attacking = true;
            target = target_id;
            is_moving = false;
            // world_ptr->get_object_ptr(target)->receive_attack(this->get_ID(), this->attack_point);
        }
    } else {
        is_attacking = false;
        if(get_delta().x != 0 && get_delta().y !=0) {
            is_moving = true;
        }
        cout<< "Can't attack the target(id: " << target_id << ")" << endl;
    }
}
void Warrior::receive_attack(int attacker_id, int attack_point) {
    /*
    Soldier 클래스의 이 함수는 자신의 health 값에서 attack_point 만큼을 뺀다.
    그런데, 만약 이 객체가 공격중인 상태가 아직 아니라면 attack_command 함수를 호출해서 
    공격한 대상을 향해 반격을 개시한다.
    반격을 가할 때는 attacker_id를 함수 인자로 사용한다.
    */

    this->health -= attack_point;
    if(health < 0) {
        health = 0;
    }
    if(get_alive() && !is_attacking) { // 살아있으면서 공격중이 아님
        attack_command(attacker_id);
    }
}
