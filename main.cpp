#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cctype>

#include "Console.h"

#include "Peasant.h"
#include "Soldier.h"
#include "Archer.h"
#include "main.h"
#include <conio.h>

#define maxsize 20

#define FILE_NAME "objwar.svd"
#define GAME_LOG_FILE "Game.log"

using namespace std;

// 프로그램 컴파일 및 실행 방법

// 방법 1. 각각 컴파일하고 실행 파일을 만들어서 실행
// g++ -c Real_Pair.cpp
// g++ -c Person.cpp
// g++ -c Peasant.cpp
// g++ -c Warrior.cpp
// g++ -c Soldier.cpp
// g++ -c Archer.cpp
// g++ -c BoardView.cpp
// g++ -c Game_World.cpp
// g++ -c main.cpp
// g++ Real_Pair.o Person.o Peasant.o Warrior.o Soldier.o Archer.o BoardView.o Game_World.o main.o -o War_Game
// ./War_Game

// 방법 2. 한번에 컴파일하면서 실행파일 생성
// g++ Real_Pair.cpp Person.cpp Peasant.cpp Warrior.cpp Soldier.cpp Archer.cpp BoardView.cpp Game_World.cpp main.cpp -o War_Game

// 방법 3. make 활용
// 방법 공부하여 적어둘것
// mingw32-make
// 위에 적은게 컴파일 및 실행파일 생성하는거
// mingw32-make clean
// 이건 생성한 실행파일들 지우는거



int main() { // 

    // cout<<endl<< "Cpp camp homework project#3 made by Youngjun Shim (22199422)" <<endl<<endl;

    BoardView b1;
    // b1.clear();

    // Peasant o1(1, 1, 1), o2(2, 5, 1);
    // o1 는 Peasant 객체이고, ID = 1, location = (1,1)
    // o2 는 Peasant 객체이고, ID = 2, location = (5,1)

    // Soldier o3(3, 1, 10), o4(4, 5, 10);
    // o3 는 Soldier 객체이고, ID = 3, location = (1,10)
    // o4 는 Soldier 객체이고, ID = 4, location = (5,10)

    Game_World g1;

    ofstream log_file(GAME_LOG_FILE);
    if(!log_file.is_open()) { // 에러 체크
        cerr<<"Error, Failed to open file "<< GAME_LOG_FILE <<" at line "<< __LINE__ <<" in "<< __FILE__ <<"\n";
        return 0;
    }

    cout<<endl<< "Cpp camp homework project#3 made by Youngjun Shim (22199422)" <<endl<<endl;
    log_file<<endl<< "Cpp camp homework project#3 made by Youngjun Shim (22199422)" <<endl<<endl;

    cout<< "Game Start!" <<endl;
    log_file<< "Game Start!" <<endl;

    // // 파일 닫기 -> 프로그램 종료 시 파일 닫음.
    // log_file.close();

    bool flag = true; // 반복문 제어용 bool 변수
    char command; // 명령어 입력용 변수
    int scale = 0; // 게임보드 스케일 변경용 변수
    int size = 0; // 게임보드 사이즈 변경용 변수
    int time = 1; // 시뮬레이터 시각, 기본값 1로 설정
    double x=0, y=0;
    bool shouldStop = true;
    while(flag) {
        shouldStop = true;
        // cout<<endl;
        // cout<<"Time: "<<time<<endl; // 시뮬레이터 시각 출력
        // b1.clear();
        // b1.plot(o1);
        // b1.plot(o2);
        // b1.plot(o3);
        // b1.plot(o4);
        // b1.draw(); // 게임보드 출력
        // cout<<endl;
        Console::clrscr();
        Console::gotoxy(1, 1);
        #ifdef _DEBUG
            cout<<"DEBUG keyword: true"<<endl;
        #endif // _DEBUG
        draw_board(b1, time, g1);
        cout<<"Enter command(press 'h' to view command list): ";
        cin>> command; // 명령어 입력
        command = tolower(command); // 대문자로 입력시 소문자로 전환
        switch(command) { // 각 명령어 작동 확인시 cout<<"command (command)"<<endl; 주석처리할것.
            case 'm': // "move" 명령어, id_num = ID인 객체의 위치를 (x,y)로 이동
                #ifdef _DEBUG
                    cout<<"command m"<<endl;
                #endif // _DEBUG
                do_move_command(log_file, g1);
                break;
            case 'c': // "carry" 명령어, id_num = ID인 객체에 w란 양의 부하를 인가
                #ifdef _DEBUG
                    cout<<"command c"<<endl;
                #endif // _DEBUG
                set_load_to_Peasant(log_file, g1);
                break;
            case 's': // "show status" 명령어, id_num = ID인 객체의 상태를 출력
                #ifdef _DEBUG
                    cout<<"command s"<<endl;
                #endif // _DEBUG
                // cout<<"command s"<<endl;
                show_status(log_file, g1);
                break;
            case 'g': // "go" 명령어, 시뮬레이터의 시각을 한단계 전진
                #ifdef _DEBUG
                    cout<<"command g"<<endl;
                #endif // _DEBUG
                // time++;
                go_command(log_file, time, g1);
                break;
            case 'z': // "zoom" 명령어, 게임보드의 출력 눈금 축적을 s로 설정
                #ifdef _DEBUG
                    cout<<"command z"<<endl;
                #endif // _DEBUG
                cin>> scale;
                b1.set_scale (scale); // BoardView의 스케일을 s로 설정
                break;
            case 'o': // "origin" 명령어, 게임보드의 원점을 (x,y)로 설정
                #ifdef _DEBUG
                    cout<<"command o"<<endl;
                #endif // _DEBUG
                cin>> x >> y;
                b1.set_origin(x,y);
                break;
            case 'r': // "resize" 명령어, 한 눈금의 크기를 s로 설정
                #ifdef _DEBUG
                    cout<<"command r"<<endl;
                #endif // _DEBUG
                cin>> size;
                b1.set_size(size); // 출력되는 화면의 크기를 s로 설정
                break;
            case 'n': // "new" 명령어, 새 객체를 추가
                #ifdef _DEBUG
                    cout<<"command n"<<endl;
                #endif // _DEBUG
                add_command(log_file, g1);
                break;
            case 'v': // "save" 명령어, 현재 게임의 상태를 파일에 저장
                #ifdef _DEBUG
                    cout<<"command v"<<endl;
                #endif // _DEBUG
                save_data(log_file, g1);
                break;
            case 'l': // "load" 명령어, 이전에 파일에 저장한 내용을 불러들여 게임을 이전 상태로 복귀
                #ifdef _DEBUG
                    cout<<"command l"<<endl;
                #endif // _DEBUG
                load_data(log_file, g1);
                break;
            case 'a': // "attack" 명령어, id1의 객체로 하여금 id2 객체를 공격하도록 명령을 내린다
                #ifdef _DEBUG
                    cout<<"command a"<<endl;
                #endif // _DEBUG
                attack(log_file,g1);
                break;
            case 'h': // 명령어 리스트 보기용, 게임에 주로 있는 help 명령어
                #ifdef _DEBUG
                    cout<<"command h"<<endl;
                #endif // _DEBUG
                show_command_list();
                break;
            case 'q': // "quit" 명령어, 프로그램 종료
                #ifdef _DEBUG
                    cout<<"command q"<<endl;
                #endif // _DEBUG
                cout<<"quit program"<<endl;
                log_file<<"quit program"<<endl;
                // 메모리 반납
                g1.clear();
                // 파일 닫기
                log_file.close();
                flag = false;
                shouldStop = false;
                break;
            // case 't': // 기능 작동 확인용 임시 명령어
            //     cout<<"command t"<<endl;
            //     break;
            default: // 주어진 명령어 이외의 입력 시 작동.
                cout<<"wrong input, enter right command"<<endl;
                cout<<"input 'h' to show command list"<<endl;
                break;
        } // switch(command) 끝

        if(shouldStop) {
            cout<<"Enter 'tab' to continue\n";
            while (true) {
                command = _getch(); // 입력 대기
                if (command == '\t') { // 탭 키를 입력하면 while 루프를 벗어나고 다시 게임 보드 출력
                    break;
                }
            }
        } // if(shouldStop) 끝

    } // while(flag) 끝

    return 0;
} // main() 끝

bool is_right_id(Game_World & G1, int id) { // 입력한 id가 적절한 id인지 검사하는 함수
    /*
    입력한 아이디가 적절한 숫자인 경우 true를 리턴
    그렇지 않은 경우 false를 리턴함.
        부적절한 id임을 알리는 메시지 출력
    이 함수를 if문의 조건문으로 사용하며, !를 붙여 부적절한 입력인 경우에만 작동.
    */
    int max_num = G1.get_num_objects();
    if(0<=id && id<max_num) { // 적절한 id
        return true;
    } else {
        if(max_num == 0) {
            cout<< "There is no character, make new one" << endl;
        } else {
            cout<< "Wrong ID, max ID is " << max_num << endl;
        }
        return false;
    }
}

// void draw_board(BoardView& b1, int& time, Peasant& o1, Peasant& o2, Soldier& o3, Soldier& o4) {
//     cout<<endl;
//     cout<<"Time: "<<time<<endl; // 시뮬레이터 시각 출력
//     b1.clear();
//     b1.plot(o1);
//     b1.plot(o2);
//     b1.plot(o3);
//     b1.plot(o4);
//     b1.draw(); // 게임보드 출력
//     cout<<endl;
// }

void draw_board(BoardView& b1, int& time, Game_World & G1) {
    int num = G1.get_num_objects();
    cout<<endl;
    cout<<"Time: "<<time<<endl; // 시뮬레이터 시각 출력
    b1.clear();
    for(int i=0; i<num; i++) {
        b1.plot(G1.get_object_ptr(i));
    }
    b1.draw(); // 게임보드 출력
    cout<<endl;
}

// void do_move_command(Peasant& o1, Peasant& o2, Soldier& o3, Soldier& o4) {
//     cout<<"Enter ID x y: ";
//     int id_num=0;
//     double x=0, y=0;
//     cin>> id_num >> x >> y;
//     Real_Pair c(x,y);
//     switch(id_num) {
//         case 1: o1.move_command(c); break;  
//         case 2: o2.move_command(c); break; 
//         case 3: o3.move_command(c); break;  
//         case 4: o4.move_command(c); break;
//         default: cout<<"Wrong id"<<endl; break;
//     }
// }

void do_move_command(ofstream & log_file, Game_World & G1) {
    // cout<<"Enter ID x y: ";
    int id_num=0;
    double x=0, y=0;
    cin>> id_num >> x >> y;
    Real_Pair c(x,y);
    if( !(is_right_id(G1, id_num)) ) {
        return;
    }
    cout<< "Move id: " << id_num << " to " << x << ',' << y << endl;
    log_file<< "Move id: " << id_num << " to " << x << ',' << y << endl;
    // id_num --; // id 번호보다 대상의 인덱스가 1 작음.
    // id 0부터 시작함. 인덱스랑 같음. 따라서 감소시킬 필요 없음. 정확히는 감소 시키면 안됨.
    G1.get_object_ptr(id_num)->move_command(c);

}

// void set_load_to_Peasant(Peasant& o1, Peasant& o2) {
//     cout<<"Enter ID w: ";
//     int id_num = 0;
//     double w = 0;
//     cin>> id_num >> w;
//     switch(id_num) {
//         case 1: o1.set_load(w); break;
//         case 2: o2.set_load(w); break;
//         default: cout<<"Wrong id"<<endl; break;
//     }
// }

void set_load_to_Peasant(ofstream & log_file, Game_World & G1) {
    // cout<<"Enter ID w: ";
    int id_num = 0;
    double w = 0;
    cin>> id_num >> w;
    if( !(is_right_id(G1, id_num)) ) { // id 입력에 대한 검사
        return;
    }
    cout<< "Set load " << w << " to " << id_num << endl;
    log_file<< "Set load " << w << " to " << id_num << endl;
    // id_num--; // id 번호보다 index가 1 작음. 따라서 인덱스로 사용하기 위해 id_num의 값을 1 감소
    // id 0부터 시작함. 인덱스랑 같음. 따라서 감소시킬 필요 없음. 정확히는 감소 시키면 안됨.
    G1.get_object_ptr(id_num)->set_load(w);
}

// void show_status(Peasant& o1, Peasant& o2, Soldier& o3, Soldier& o4) {
//     cout<<"Enter ID: ";
//     int id_num = 0;
//     cin>> id_num;
//     switch(id_num) {
//         case 1: o1.display_status(); break;  
//         case 2: o2.display_status(); break; 
//         case 3: o3.display_status(); break;  
//         case 4: o4.display_status(); break;
//         default: cout<<"Wrong id"<<endl; break;
//     }
// }

void show_status(ofstream & log_file, Game_World & G1) {
    // cout<<"Enter ID: ";
    int id_num = 0;
    cin>> id_num;
    if( !(is_right_id(G1, id_num)) ) { // id 입력에 대한 검사
        return;
    }
    cout<< "Show ID(" << id_num << ") status" << endl;
    log_file<< "Show ID(" << id_num << ") status" << endl;
    // id_num--; // id 번호보다 index가 1 작음. 따라서 인덱스로 사용하기 위해 id_num의 값을 1 감소
    // id 0부터 시작함. 인덱스랑 같음. 따라서 감소시킬 필요 없음. 정확히는 감소 시키면 안됨.
    G1.get_object_ptr(id_num)->display_status();
}

// void go_command(int& time, Peasant& o1, Peasant& o2, Soldier& o3, Soldier& o4) {
//     /*
//     시뮬레이터 시각 전진 시키는 명령어
//     시간 변수 값 1 증가
//     각 객체들의 상태 갱신
//     */
//     time++;
//     o1.update();
//     o2.update();
//     o3.update();
//     o4.update();
// }

void go_command(ofstream & log_file, int & time, Game_World & G1) {
    /*
    시뮬레이터 시각 전진 시키는 명령어
    시간 변수 값 1 증가
    각 객체들의 상태 갱신
    */
    time++;
    // o1.update();
    // o2.update();
    // o3.update();
    // o4.update();
    cout<< "Game proceed" << endl;
    log_file<< "Game proceed" << endl;
    for(int i=0; i<G1.get_num_objects(); i++) {
        G1.get_object_ptr(i)->update();
    }
}

void dynamic_memory_allocate(ofstream & log_file, Game_World & G1, const string& _name, char type, double x, double y) {
    
    // add_command 함수에서 메모리 동적 할당 부분만 여기로 옮길 예정
    // 함수의 타입을 void로 해서 하는게 좋을까 아니면 Person * 타입으로 해서 리턴값을 가지게 하는 게 좋을까.
    // void로 하고 메모리 동적 할당 후 바로 G1의 add_object에 인자로 넘겨서 추가하는게 좋을듯.

    #ifdef _DEBUG
        cout<< "Dynamic memory allocate function called" << endl;
    #endif // _DEBUG
    log_file<< "Dynamic memory allocate function called" << endl;

    Person * ptr = nullptr;
    int id = G1.get_num_objects();
    bool is_success = false;

    switch(type) {
        case 'P': 
            ptr = new Peasant(&G1, id, x, y, _name); 
            if(ptr==nullptr) {
                cerr<<"Failed to allocate memory in Line " << __LINE__ << " of " << __FILE__ << endl;
                //exit(-1);
                return;
            }
            is_success = true;
            cout<< "Make new character, type: " << type << " at " << x << ", " << y << endl;
            log_file<< "Make new character, type: " << type << " at " << x << ", " << y << endl;
            break; // Peasant 객체 생성
        case 'S': 
            ptr = new Soldier(&G1, id, x, y, _name); 
            if(ptr==nullptr) {
                cerr<<"Failed to allocate memory in Line " << __LINE__ << " of " << __FILE__ << endl;
                // exit(-1);
                return;
            }
            is_success = true;
            cout<< "Make new character, type: " << type << " at " << x << ", " << y << endl;
            log_file<< "Make new character, type: " << type << " at " << x << ", " << y << endl;
            break; // Soldier 객체 생성
        case 'A': 
            ptr = new Archer(&G1, id, x, y, _name); 
            if(ptr==nullptr) {
                cerr<<"Failed to allocate memory in Line " << __LINE__ << " of " << __FILE__ << endl;
                // exit(-1);
                return;
            }
            is_success = true;
            cout<< "Make new character, type: " << type << " at " << x << ", " << y << endl;
            log_file<< "Make new character, type: " << type << " at " << x << ", " << y << endl;
            break; // Archer 객체 생성
        default: 
            cout << "Wrong input, input 'P' or 'S' or 'A'." << endl; 
            log_file<< "Wrong input, failed to make new character, type: " << type << " at " << x << ", " << y << endl;
            break;
    }

    if(is_success) {
        G1.add_object(ptr);
    }
} 

void add_command(ofstream & log_file, Game_World & G1) {
    /*
    코드 전반적인 수정이 필요함.
    이 함수는 new 명령어를 실행하기 위한 함수로, 
    필요한 정보들을 입력받아 dynamic_memory_allocate 함수에 인자로 전달한다.
    메모리 할당은 dynamic_memory_allocate 함수에서 실행되고
    그 결과 생성된 객체를 G1에 저장하는 일 역시 dynamic_memory_allocate 함수에서 진행한다.
    add_command 함수는 필요한 값들을 입력 받아 dynamic_memory_allocate함수를 호출하는 일만 한다.
    
    이렇게 수정하는 이유는 게임 과정에서 새로운 객체를 추가하는 것과
    load를 통해 새로운 객체를 생성하는 과정에서
    메모리 할당이라는 공통적인 역할은 하나의 함수에서 담당하게 하기 위함이다.

    아래의 내용들은 수정할것.
    */
    char type;
    double x;
    double y;
    string name;

    // cout<< "Enter type('P' or 'S' or 'A') x y" << endl;
    cin >> type >> x >> y >> name;
    type = toupper(type); // 타입을 소문자로 입력할 경우를 대비, 대문자로 전환
    cout<< "type : " << type << ", x = " << x << ", y = " << y << ", name: " << name << endl; // 확인용 코드

    dynamic_memory_allocate(log_file, G1, name, type, x, y);
    
}

void save_data(ofstream & log_file, Game_World & G1) { // 저장

    cout << "Save game data" << endl;
    log_file<< "Save game data" << endl;

    // 파일 열기
    ofstream file(FILE_NAME);
    if(!file.is_open()) { // 에러 체크
        cerr<<"Error, Failed to open file "<< FILE_NAME <<" at line "<< __LINE__ <<" in "<< __FILE__ <<"\n";
        return;
    }

    // 각 객체들의 상태 저장
    int num = G1.get_num_objects();
    file << num << endl;
    for(int i=0; i<num; i++) {
        G1.get_object_ptr(i)->save(file);
    }

    // 파일 닫기
    file.close();
}

// void load_data(ofstream & log_file, Game_World & G1) {

//     cout << "Load game data" << endl;
//     log_file<< "Load game data" << endl;

//     // 파일 열기
//     ifstream file(FILE_NAME);
//     if(!file.is_open()) { // 에러 체크
//         cerr<<"Error, Failed to open file "<< FILE_NAME <<" at line "<< __LINE__ <<" in "<< __FILE__ <<"\n";
//         return;
//     }

//     // 각 객체들의 상태 불러오기
//     int obj_num = 0;
//     file >> obj_num;
//     Person * ptr;
//     // add_new_object(log_file, G1);
//     /*
//     파일에서 code 값을 읽어서 새로운 객체를 생성
//     그 후 해당 객체의 restore 함수 호출
//     */
//     char code = '?';
//     // file >> code;

//     // G1.set_num_objects(obj_num);
//     for(int i=0; i<obj_num; i++) {
//         file >> code;
//         dynamic_memory_allocate(log_file, G1, code);
//         G1.get_object_ptr(i)->restore(file);
//     }

//     // 파일 닫기
//     file.close();
// }

void load_data(ofstream & log_file, Game_World & G1) {

    cout << "Load game data" << endl;
    log_file<< "Load game data" << endl;

    // // 파일 열기
    // ifstream file(FILE_NAME);
    // if(!file.is_open()) { // 에러 체크
    //     cerr<<"Error, Failed to open file "<< FILE_NAME <<" at line "<< __LINE__ <<" in "<< __FILE__ <<"\n";
    //     return;
    // }

    // // 각 객체들의 상태 불러오기
    // int obj_num = 0;
    // file >> obj_num;
    // Person * ptr;
    // // add_new_object(log_file, G1);
    // /*
    // 파일에서 code 값을 읽어서 새로운 객체를 생성
    // 그 후 해당 객체의 restore 함수 호출
    // */
    // char code = '?';
    // // file >> code;

    // // G1.set_num_objects(obj_num);
    // for(int i=0; i<obj_num; i++) {
    //     file >> code;
    //     dynamic_memory_allocate(log_file, G1, code);
    //     G1.get_object_ptr(i)->restore(file);
    // }

    G1.restore();

    // // 파일 닫기
    // file.close();
}

void attack(std::ofstream & log_file, Game_World & G1) {
    // cout<< "Enter id1 id2" << endl;
    int id1 = 0;
    int id2 = 0;
    cin>> id1 >> id2;
    if( !(is_right_id(G1, id1) && is_right_id(G1, id2)) ) { // id 입력에 대한 검사
        return;
    }
    G1.get_object_ptr(id1)->attack_command(id2);
}

void show_command_list() {

    cout<<endl;
    cout<<"m ID x y - \"move\" command"<<endl;
    cout<<": This is a command to move the location of an object with id_num = ID to (x,y)."<<endl;
    cout<<endl;

    cout<<"c ID w - \"carry\" command"<<endl;
    cout<<": W is a command for applying a positive load to an object with id_num = ID."<<endl;
    cout<<"Command valid for objects o1 and o2 only; otherwise, message output"<<endl;
    cout<<endl;

    cout<<"s ID - \"show status\" command"<<endl;
    cout<<": It is a command that outputs the state of the object with id_num = ID."<<endl;
    cout<<endl;

    cout<<"g - \"go\" command"<<endl;
    cout<<": It is a command that takes the simulator's perspective to the next level."<<endl;
    cout<<endl;

    cout<<"z s - \"zoom\" command"<<endl;
    cout<<": Set the accumulation of the output scale of the game board to s."<<endl;
    cout<<endl;

    cout<<"o x y - \"original\" command"<<endl;
    cout<<": Set the origin of the game board to (x,y)."<<endl;
    cout<<endl;

    cout<<"r s - \"resize\" command"<<endl;
    cout<<": It is a command that sets the size of a scale to s."<<endl;
    cout<<endl;

    cout<<"n c x y - \"new\" command"<<endl;
    cout<<": Create a new object and add it to Game_World."<<endl;
    cout<<endl;

    cout<<"v - \"save\" command."<<endl;
    cout<<": Save the status of the current game to a file."<<endl;
    cout<<endl;

    cout<<"l - \"load\" command."<<endl;
    cout<<": Command the object of id1 to attack the object of id2."<<endl;
    cout<<endl;

    cout<<"a id1 id2 - \"attack\" command."<<endl;
    cout<<": Bring back the game to its previous state by fetching the previously saved content in the file."<<endl;
    cout<<endl;

    cout<<"q - \"quit\" command"<<endl;
    cout<<": Shut down the program."<<endl;
    cout<<endl;

}