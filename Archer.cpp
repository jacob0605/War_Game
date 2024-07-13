#include <iostream>
#include <fstream>
#include <cmath>
#include "Archer.h"

using namespace std;

void Archer::initialize() {
    Warrior::initialize(2, 10);
    set_health(10);
    set_speed(7);
    // cout<<"Soldier initialize function called"<<endl; // 초기화 함수 호출 확인용
}

/*
- 초기화시 설정하는 값은 다음과 같이 변경된다.
    range = 10.0, attack_point = 2, health = 10, speed = 7
- 매 update시 마다, 공격중이 아닐 경우, 자동으로 공격 사정범위(range) 내의 가장 가까이 있는 객체를 검색하여 공격을 개시한다.
*/

Archer::Archer(int id, double x, double y) {
    id_num = id;
    location.x = x;
    location.y = y;
    // initialize();
    // cout<<"Soldier Default Constructor called"<<endl; // 생성자 작동 확인용 코드
}

Archer::Archer() : Warrior() {
    // initialize(int _attack_point = 3, double _range = (3.0), bool is_attack = false, int _target = -1);
    initialize();
    // cout<<"Soldier Default Constructor called"<<endl; // 생성자 작동 확인용 코드
}

Archer::Archer(Game_World * w_ptr) : Warrior(w_ptr) {
    // 기본 생성자의 기능 + w_ptr 인자를 받아서 world_pointer 값 초기화 수행
    // world_ptr = w_ptr;
    initialize();
    // cout<<"Soldier Second Constructor called"<<endl; // 생성자 작동 확인용 코드
}

// Person(Game_World * w_ptr, char c, int id, double in_x, double in_y);
Archer::Archer(Game_World * w_ptr, int id, double x, double y) : Warrior(w_ptr, 'A', id, x, y) {
    // 기본 생성자의 기능 + world_pointer 값 초기화 + Person 객체의 ID와 location 초기화 수행
    // id_num = id;
    // location.x = x;
    // location.y = y;
    // world_ptr = w_ptr;
    initialize();
    // cout<<"Soldier Third Constructor called"<<endl; // 생성자 작동 확인용 코드
}

void Archer::update() {
    /*
    Soldier 클래스의 이 함수는 이미 정의한 내용을 수정해야 한다.
    이 함수가 호출되면 가장 먼저 객체가 공격중인 상태인지 검사한다.
    만약 현재의 목표물이 죽었거나 사정거리를 벗어나서 공격할 수 없다면 공격을 멈추고 이를 설명하는 메시지를 출력한다.
    만약에 공격이 계속 진행된다면, 목표물의 receive_attack() 함수를 호출한다.
    receive_attack 함수를 호출할 때는 이 객체의 ID 번호와 attack_point를 인자로 넘겨주고,
    더불어서 공격중이라는 의미의 메시지를 화면에 출력한다.
    */
    /*
    Archer 클래스의 update 함수
    살아 있는 지 검사
        살아 있음
            공격 중인가
                공격 중
                공격 중이 아님
                    반복문 사용, 가장 가까운 객체 검색
                    대상과의 거리가 사정거리보다 작거나 같으면
                        공격
    */
    // if(health > 0 && is_moving==true) {

    #ifdef _DEBUG
        cout<< "Archer class update function called" << endl;
    #endif // _DEBUG
    

    if(get_alive()) {
        if(is_attacking) {
            // world_ptr->get_object_ptr(target)->receive_attack(this->get_ID(), this->attack_point);
            if(world_ptr->get_object_ptr(target)->get_alive()) {
                if(distance(this->get_location(), world_ptr->get_object_ptr(target)->get_location()) <= range) {
                    // is_attacking = true;
                    // target = target_id;
                    // is_moving = false;
                    world_ptr->get_object_ptr(target)->receive_attack(this->get_ID(), this->attack_point);
                    cout<< "attack the target(id: " << target << "), attack point is " << attack_point <<endl;
                } else {
                    is_attacking = false;
                    cout<< "target is out of range" <<endl;
                }
            } else {
                is_attacking = false;
                cout<< "the target is dead" << endl;
            }
        } else {
            cout<< "\tnow, not attacking" << endl;
            int total_num = world_ptr->get_num_objects();
            int d = 0;
            int min_d = range;
            int target_id = -1;
            int this_id = get_ID();
            for(int i=0; i<total_num; i++) {
                if(world_ptr->get_object_ptr(i)->get_alive()) {
                    if(i != this_id) {
                        d = distance(this->get_location(), world_ptr->get_object_ptr(i)->get_location());

                        // 디버그 모드 활성화 시 대상과의 거리 d 출력
                        #ifdef _DEBUG
                            cout<<"\t\t d: "<< d << endl;
                        #endif // _DEBUG
                        
                        if(d <= min_d) {
                            min_d = d;
                            target_id = i;
                        }
                    }
                }
            }
            // cout<<"\t\t distance is "<< min_d << endl;
            // cout<<"\t\t target id is "<< target_id << endl;
            if(target_id != -1) {
                cout<< "\tfind the target(id: " << target_id << "), start attack" << endl;
                // Warrior::attack_command(int target_id)
                attack_command(target_id);
                world_ptr->get_object_ptr(target)->receive_attack(this->get_ID(), this->attack_point);
            }
        }
        if(is_moving) {
            health--;
            if(health <= 0) {
                cout<< id_num << " dead"<<endl;
                is_moving = false;
            } else {
                update_location();
            }
        }
    }
}

void Archer::display_status() {
/*
Soldier 객체의 현재 상태에 대한 정보를 출력한다. 예컨대 아래와 같다. 
    Soldier ID: 4 at (20, 10) is alive  
    Health is 2  
    Not moving. 

    int attack_point; // 공격할 때 상대방에게 가하는 타격의 크기이다. 초기값은 3이다.
    double range; // 공격하는 사정거리이다. 이 값 이내에 상대가 위치하고 있어야 공격이 가능하다. 초기값은 3.0이다.
    bool is_attacking; // 현재 이 객체가 공격중인 상태인지 나타낸다. 초기값은 false이다.
    int target; // 공격중인 경우에 공격 대상의 ID 값을 나타낸다. 초기값은 -1이다.
*/
    if(health > 0) {
        cout<<"Archer ID: "<< id_num <<" at ("<< location.x <<", "<< location.y << ") is alive"<<endl;
        cout<<"Health is "<< health << ", speed is " << speed << endl;
        if(is_moving) {
            cout<< "Moving" << endl;
        } else {
            cout<< "Not moving" << endl;
        }
        cout<<"Attack point is "<< attack_point <<endl;
        cout<<"Range is "<< range <<endl;
        if(is_attacking) {
            cout<< "Attacking, target id is " << target << endl;
        } else {
            cout<< "Not attacking" << endl;
        }
    } else {
        cout<<"Archer ID: "<< id_num <<" at ("<< location.x <<", "<< location.y << ") is dead"<<endl;
    }

    // 이 함수는 공격과 관련되어 Soldier 객체에 추가된 여러 멤버 변수들을 추가로 출력하기 위해서 수정되어야 한다.

}

void Archer::save(ofstream & outfile) {
    Warrior::save(outfile);
    // 이 함수는 Soldier 객체에 새로 추가된 멤버 변수값들을 저장하기 위해서 수정되어야 한다.
    /*
    attack_point = 3; // 공격할 때 상대방에게 가하는 타격의 크기이다. 초기값은 3이다.
    range = 3.0; // 공격하는 사정거리이다. 이 값 이내에 상대가 위치하고 있어야 공격이 가능하다. 초기값은 3.0이다.
    is_attacking = false; // 현재 이 객체가 공격중인 상태인지 나타낸다. 초기값은 false이다.
    target = -1; // 공격중인 경우에 공격 대상의 ID 값을 나타낸다. 초기값은 -1이다.
    */
    // outfile<< attack_point <<endl;
    // outfile<< range <<endl;
    // outfile<< is_attacking <<endl;
    // outfile<< target <<endl;
}

void Archer::restore(ifstream & infile) {
    Warrior::restore(infile);
    code = 'A';
    // 이 함수도 Soldier 객체에 새로 추가된 멤버 변수들의 값을 복귀하기 위해서 수정되어야 한다.
    // infile >> attack_point;
    // infile >> range;
    // infile >> is_attacking;
    // infile >> target;
}
