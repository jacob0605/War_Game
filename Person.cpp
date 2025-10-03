#include <iostream>
#include <fstream>
#include <cmath>
#include "Person.h"

using namespace std;

/**
 * Person class constructor
 * @param w_ptr world pointer
 */
Person::Person(Game_World* w_ptr) {
    baseData.world_ptr = w_ptr;
}

Person::Person(Game_World* w_ptr, char c, int id, double in_x, double in_y, const string& _name) {
    baseData.code = c;
    baseData.id_num = id;
    baseData.name = _name;
    // baseData.health;
    // baseData.speed;
    // baseData.is_moving;
    baseData.location = Real_Pair(in_x, in_y);
    // baseData.destination;
    // baseData.delta;
    baseData.world_ptr = w_ptr;
}

void Person::update_location() {
    if (baseData.is_moving == true) {                                                                                                                                       // 객체가 이동중이라면 == is_moving의 값이 true임
        if ((abs(baseData.destination.x - baseData.location.x) <= abs(baseData.delta.x)) && (abs(baseData.destination.y - baseData.location.y) <= abs(baseData.delta.y))) { // 곧 도착
            baseData.location = baseData.destination;
            cout << "ID: " << baseData.id_num << ", arrived" << endl;
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
            baseData.delta.x = 0;
            baseData.delta.y = 0;
            baseData.is_moving = false;
        } else { // 이동중
            baseData.location = baseData.location + baseData.delta;
            cout << "ID: " << baseData.id_num << ", moving" << endl;
        }
    }
}

void Person::move_command(Real_Pair destination) {
    if (baseData.health <= 0) {
        cout << "I'm dead - can't move (id: " << baseData.id_num << ")" << endl;
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
        this->baseData.destination = destination;
        baseData.is_moving = true;
        baseData.delta = (baseData.destination - baseData.location) * (baseData.speed / distance(baseData.destination, baseData.location));
    }
}

void Person::set_load(double in_load) {
    cout << "I can't carry a load" << endl;
}

void Person::display_status() {
    cout << "Name : " << baseData.name << endl;
}

void Person::save(ofstream& outfile) {
    /*
    이 함수는 모든 멤버 변수들의 값을 제공된 파일에 기록함. 클래스의 타입을 표시하는 code 문자를 가장 먼저 기록한다.
    world_ptr 값은 파일에 기록하지 않는다.
    (왜 world_ptr 값은 기록하지 않는 것일까?)
    */
    // 파일 에러 체크
    if (!outfile.is_open()) {
        cerr << "Error, Failed to open file for save data at line " << __LINE__ << " in " << __FILE__ << "\n";
        return;
    }

    // 정보 저장
    baseData.save(outfile);

    // 파일 닫기 -> 여기서 진행하지 않는다.
}

void Person::restore(ifstream& infile) {
    // 파일 에러 체크
    if (!infile.is_open()) {
        cerr << "Error, Failed to open file for save data at line " << __LINE__ << " in " << __FILE__ << "\n";
        return;
    }
    baseData.restore(infile);
}

void Person::attack_command(int target_id) {
    cout << "I can't attack the enemy" << endl;
}

void Person::receive_attack(int attacker_id, int attack_point) {
    if (baseData.health > attack_point) {
        cout << "Outch!" << endl;
        baseData.health -= attack_point;
    } else {
        baseData.health = 0;
    }
}
