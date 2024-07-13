
#include <iostream>
#include <fstream>
#include "Peasant.h"
#include "Soldier.h"
#include "Archer.h"
#include "Game_World.h"

#define SAVE_FILE "objwar.svd" // 저장할 파일의 이름
#define MAX_OBJECTS_COUNT 10 // 생성할 수 있는 총 객체의 수를 메크로로 설정, 값은 10으로 설정

using namespace std;

Game_World::Game_World() {
    for(int i=0; i<MAX_OBJECTS_COUNT; i++) {
        objptr[i] = nullptr;
    }
    max_num_objects = MAX_OBJECTS_COUNT; // 생성할 수 있는 객체의 총 개수, 기본값 10
    num_objects = 0; // 현재 존재하는 객체의 수, 기본값 0
}

Game_World::~Game_World() {
    clear();
    #ifdef _DEBUG
        cout<< "Game_World destructor called" << endl; // 확인용 코드
    #endif // _DEBUG
}

void Game_World::set_num_objects(int num) {
    this->num_objects = num;
}

bool Game_World::has_space() {
    // 추가의 객체를 위한 포인터를 저장할 장소가 배열에 남아 있는지 점검하여 true/false를 반환한다.
    if(num_objects < max_num_objects) { // 현재 객체의 수 < 존재 가능한 총 객체의 수
        return true;
    } else {
        return false;
    }
}

void Game_World::add_object(Person *ptr) { // 완성할 것, 완성한 듯?
    // 주어진 객체의 포인터 값을 포인터 배열의 다음 빈자리에 저장한다.
    // 만약 빈자리가 없으면 false를 반환한다.
    /*
    ***** 메모 *****
    메모리 반납을 소멸자를 활용하면 되겠지 라고 교수님이 말했었음.
    따로 delete를 써서 메모리 반납을 해주는 방법이 아니라 소멸자에 delete를 넣으면 어떻게 될까?
    아니다.
    반납할때 소멸자를 호출하는데 호출하면 반납한다는건 말이 안되는거 같은데

    함수의 타입을 bool에서 void로 바꿨고, Person * ptr 라는 인자를 없앨까

    project_03 폴더 밑에 있는 test 폴더 속 ptr_test02.cpp에서 이 문제 해결함.
    동적 할당한 메모리를 인자로 넘겨받아 배열에 저장하고 동적 할당했던 함수가 종료되면
    할당한 메모리에 대한 반납은 배열에서 책임지게 됨
    */
    if(has_space()) {
        if(objptr[num_objects] == nullptr) {
            objptr[num_objects] = ptr;
            cout<< "\tmemory allocated to objptr["<< num_objects << "]" << endl; // 확인용 코드
            cout<< "\tbefore memory allocate, num_objects is " << num_objects << endl; // 확인용 코드
            num_objects++;
            cout<< "\tafter memory allocate, num_objects is " << num_objects << endl; // 확인용 코드
        }

    } else {
        if(ptr != nullptr) {
            delete ptr;
            ptr = nullptr;
        }
        cout<< "there is no space to add new object" << endl;
    }
}

void Game_World::save() { // 정보 저장 파트 작성할 것.
    // 현재 게임상에 존재하는 모든 객체의 타입과 정보를 "objwar.svd" 파일에 저장한다.

    // 파일 열기 및 에러 체크
    ofstream saveFile(SAVE_FILE);
    if(!saveFile.is_open()) {
        cerr<<"Error, Failed to open file "<< SAVE_FILE <<" at line "<< __LINE__ <<" in "<< __FILE__ <<"\n";
        return;
    }

    // 정보 저장
        /*
        파일을 열고 반복문을 사용해서 최대 10개의 객체에 대한 정보들을 순서대로 저장.
        각 객체의 save 함수 호출
        */
        // saveFile<< max_num_objects << endl; // 생성 가능한 총 객체의 수 저장
        saveFile<< num_objects << endl; // 현재 생성된 객체의 수 저장
        for(int i=0; i<max_num_objects; i++) {
            if(objptr[i] != nullptr) {
                objptr[i]->save(saveFile);
            }
        }

    // 파일 닫기
    saveFile.close();
}

void Game_World::restore() {
    // clear() 함수를 이용해서 현재의 모든 객체를 삭제한 뒤에, 
    // "objwar.svd" 파일에서 읽어들인 객체들을 게임상에 원상태로 복귀한다.
    clear();
    ifstream saveFile(SAVE_FILE);
    if(!saveFile.is_open()) {
        cerr<<"Error, Failed to open file "<< SAVE_FILE <<" at line "<< __LINE__ <<" in "<< __FILE__ <<"\n";
        return;
    }

    char type;
    saveFile >> num_objects;
    for(int i=0; i<num_objects; i++) {
        saveFile >> type;
        switch(type) {
            case 'P': objptr[i] = new Peasant(this); break;
            case 'S': objptr[i] = new Soldier(this); break;
            case 'A': objptr[i] = new Archer(this); break;
            default: objptr[i] = new Peasant(this); break;
        }
        objptr[i]->restore(saveFile);
    }

    saveFile.close();
}

void Game_World::clear() {
    // 현재 게임 상의 모든 객체들을 위한 메모리를 시스템에 반환하고 
    // 포인터 배열의 모든 원소의 값을 NULL로 리셋하고, 객체의 개수를 0으로 설정한다.
    for(int i=0; i<max_num_objects; i++) {
        if(objptr[i] != nullptr) {
            delete objptr[i];
            objptr[i] = nullptr;
        }
    }
    num_objects = 0;
}