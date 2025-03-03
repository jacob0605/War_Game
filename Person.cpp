#include <iostream>
#include <fstream>
#include <cmath>
#include "Person.h"

using namespace std;

Person::Person() : world_ptr(nullptr), code('?'), id_num(0), speed(5), health(5), is_moving(false) {
    // // 기본 생성자
    // id_num = 0; // ID = 0
    // speed = 5; // speed = 5 units/tick
    // // location, destination, delta; // location, destination, delta 멤버들은 모두 Real_Pair 객체임
    //     // Real_Pair 디폴트 생성자에 의해 (0,0)으로 자동으로 초기화
    // health = 5; // health = 5
    // is_moving = false; // not moving 현재 상태, 정지중임
    // code = '?';
    // world_ptr = nullptr;
    // cout<<"Person Default Constructor called"<<endl;
    name = "defaultName";
}

/**
 * Person class constructor
 * @param w_ptr world pointer
 */
Person::Person(Game_World * w_ptr) : 
                world_ptr(w_ptr), 
                // name(_name),
                code('?'), 
                id_num(0), 
                speed(5), 
                health(5), 
                is_moving(false) { // not moving 현재 상태, 정지중임
    // // 기본 생성자의 기능 + w_ptr 인자를 받아서 world_pointer 값 초기화 수행
    // id_num = 0; // ID = 0
    // speed = 5; // speed = 5 units/tick
    // // location, destination, delta; // location, destination, delta 멤버들은 모두 Real_Pair 객체임
    //     // Real_Pair 디폴트 생성자에 의해 (0,0)으로 자동으로 초기화
    // health = 5; // health = 5
    // is_moving = false; 
    // code = '?';
    // world_ptr = w_ptr;
    // cout<<"Person Second Constructor called"<<endl;
}

Person::Person(Game_World * w_ptr, char c, int id, double in_x, double in_y, const string& _name) : world_ptr(w_ptr), name(_name), code(c), id_num(id), location(in_x, in_y), speed(5), health(5), is_moving(false) {
    // // 기본 생성자의 기능 + world_pointer 값 초기화 + Person 객체의 ID와 location 초기화 수행
    // id_num = id; // ID = 0
    // speed = 5; // speed = 5 units/tick
    // // location, destination, delta; // location, destination, delta 멤버들은 모두 Real_Pair 객체임
    //     // Real_Pair 디폴트 생성자에 의해 (0,0)으로 자동으로 초기화
    // health = 5; // health = 5
    // is_moving = false; // not moving 현재 상태, 정지중임
    // code = c;
    // world_ptr = w_ptr;
    // location.x = in_x; 
    // location.y = in_y;
    // cout<<"Person Third Constructor called"<<endl;
}

void Person::update_location() {
    if(is_moving == true) { // 객체가 이동중이라면 == is_moving의 값이 true임
        if(( abs(destination.x - location.x) <= abs(delta.x)) && ( abs(destination.y - location.y) <= abs(delta.y))) { // 곧 도착
            location = destination;
            cout<< "ID: " << id_num <<", arrived" << endl;
            /*
            공격할 수 있는 객체가 이동 중 적을 공격하고
            목표가 죽은 경우 다시 원래의 목적지로 이동하게 만들 예정이다.
            이를 위해 해당 객체에서는 delta 값이 (0,0)인지를 검사하고
            delta가 (0,0)이 아닌 경우, is_moving 값을 true로 바꾼다.
            이를 위해 목적지에 도착한 경우 delta 값을 (0,0)으로 설정하였다.
            그러나, delta의 값에 무관하게 아래의 조건으로 인해
                if(( abs(destination.x - location.x) <= abs(delta.x)) && ( abs(destination.y - location.y) <= abs(delta.y)))
            delta 값이 (0,0)이 아니더라도 is_moving의 값은 다시 false로 변할 것이고
            cout<< "ID: " << id_num <<", arrived" << endl;
            이 코드에 의해 도착했음을 알릴 것이다.
            하지만, 이미 도착해 있는 상태에서 다시 도착 메시지를 출력하지 않게 하기 위해
            delta의 값을 (0,0)으로 변경한다.
            */
            delta.x = 0;
            delta.y = 0;
            is_moving = false;
        } else { // 이동중
            location = location + delta;
            cout<< "ID: " << id_num << ", moving" << endl;
        }
    }
}

void Person::move_command(Real_Pair destination) {
    if(health <= 0) {
        cout<<"I'm dead - can't move (id: "<< id_num <<")"<<endl;
    } else {
        /*
        목적지 좌표를 destination 멤버 변수에 저장
        is_move 플래그를 true로 설정
        delta 값 계산, 멤버 변수에 저장.
            delta = (destination - location)*(speed / distance(destination,location))
            이 delta 변수는 x축과 y축의 매 시간별 이동량을 의미
            한번 계산 후 매 이동시 좌표 계산을 위해 재사용됨
        객체는 주어진 속도로 목적지를 향해 직선으로 이동
        매 시간별 (x,y) 값의 변화는 이동 속도와 목적지까지의 거리의 비율에 비례
        */
        
        // 목적지 좌표를 destination 멤버 변수에 저장하는 코드 작성할것 -> 작성 하였음. 아래에서 서술함.
            // 함수 인자로 목표 좌표를 저장하고 있는 Real_Pair 클래스를 받아서
            // Person 클래스의 멤버 변수인 destination에 저장
        this->destination = destination;
        is_moving = true;
        delta = (destination - location)*(speed / distance(destination,location));

    }
}

void Person::set_load(double in_load) {
    cout<< "I can't carry a load" << endl;
}

void Person::display_status() {
    cout << "Name : " << name << endl;
}

void Person::save(ofstream & outfile) {
/*
이 함수는 모든 멤버 변수들의 값을 제공된 파일에 기록함. 클래스의 타입을 표시하는 code 문자를 가장 먼저 기록한다.
world_ptr 값은 파일에 기록하지 않는다.
(왜 world_ptr 값은 기록하지 않는 것일까?)
*/
    // 파일 에러 체크
    if(!outfile.is_open()) {
        cerr<<"Error, Failed to open file for save data at line "<< __LINE__ <<" in "<< __FILE__ <<"\n";
        return;
    }

    // 정보 저장
    // outfile<< code << delta << id_num << speed << location << destination << health << is_moving << endl;
    /*
    Person 클래스에서 저장해야 할 멤버 변수들
    private:
        Real_Pair delta; // 객체가 이동중에 있을 때, 그 객체의 매 시뮬레이션 시간별 x와 y 좌표 변화량
    protected:
        int id_num; // 객체를 유일하게 나타내는 식별자
        double speed; // 객체가 매 시각마다 이동하는 속도
        Real_Pair location; // 게임보드 이차원 평면상의 객체의 현재 위치
        Real_Pair destination; // 객체가 이동할 경우 최종 목적지의 위치 좌표
        int health; // 이 값이 0이 되면 그 객체는 "죽게 된다"
        bool is_moving; // 객체가 현재 이동중인지 정지 상태인지를 표시함. 이 값이 true 이면 이동중임
        char code; // Person 객체의 타입을 표시해주는 한 문자 출력전용 목적, 기본 초기값은 '?'
    */
    outfile << code << endl; // Person 객체의 타입을 표시해주는 한 문자 출력전용 목적, 기본 초기값은 '?'
    outfile << delta << endl; // 객체가 이동중에 있을 때, 그 객체의 매 시뮬레이션 시간별 x와 y 좌표 변화량
    outfile << id_num << endl; // 객체를 유일하게 나타내는 식별자
    outfile << speed << endl; // 객체가 매 시각마다 이동하는 속도
    outfile << location << endl; // 게임보드 이차원 평면상의 객체의 현재 위치
    outfile << destination << endl; // 객체가 이동할 경우 최종 목적지의 위치 좌표
    outfile << health << endl; // 이 값이 0이 되면 그 객체는 "죽게 된다"
    outfile << is_moving << endl; // 객체가 현재 이동중인지 정지 상태인지를 표시함. 이 값이 true 이면 이동중임
    outfile << name << endl; // 객체의 이름, string 타입의 변수

    // 파일 닫기 -> 여기서 진행하지 않는다.

}

void Person::restore(ifstream & infile) {
/*
이 함수는 제공된 파일로부터 멤버 변수들의 값을 읽어들인다. 단, 이 함수를 호출하기 전에
Game_World 객체의 restore 함수가 이미 읽어들인 code 문자는 제외하고 읽는다.
world_ptr의 값도 읽어들이지 않는다. (기본값은 0이다.)
*/
/*
저장한 순서에 맞게 읽는다.
    outfile << code << endl; // Person 객체의 타입을 표시해주는 한 문자 출력전용 목적, 기본 초기값은 '?'
    outfile << delta << endl; // 객체가 이동중에 있을 때, 그 객체의 매 시뮬레이션 시간별 x와 y 좌표 변화량
    outfile << id_num << endl; // 객체를 유일하게 나타내는 식별자
    outfile << speed << endl; // 객체가 매 시각마다 이동하는 속도
    outfile << location << endl; // 게임보드 이차원 평면상의 객체의 현재 위치
    outfile << destination << endl; // 객체가 이동할 경우 최종 목적지의 위치 좌표
    outfile << health << endl; // 이 값이 0이 되면 그 객체는 "죽게 된다"
    outfile << is_moving << endl; // 객체가 현재 이동중인지 정지 상태인지를 표시함. 이 값이 true 이면 이동중임
*/
    // 파일 에러 체크
    if(!infile.is_open()) {
        cerr<<"Error, Failed to open file for save data at line "<< __LINE__ <<" in "<< __FILE__ <<"\n";
        return;
    }

    // infile >> code; // 이건 빼야 하나. 코드 읽음 -> 적절한 객체 생성 -> 그 객체의 restore 함수 호출. 이렇게 돼야 될거 같은데
    infile >> delta;
    infile >> id_num;
    infile >> speed;
    infile >> location;
    infile >> destination;
    infile >> health;
    infile >> is_moving;
    infile >> name;

}

void Person::attack_command(int target_id) {
    cout<< "I can't attack the enemy" << endl;
}

void Person::receive_attack(int attacker_id, int attack_point) {
    if(health - attack_point > 0) {
        cout<< "Outch!" << endl;
        health -= attack_point;
    } else {
        health = 0;
    }
}
