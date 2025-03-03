

#ifndef __MAIN__
#define __MAIN__

// #include "Real_Pair.h"
// #include "Person.h"
// #include "Peasant.h"
// #include "Soldier.h"
#include "BoardView.h"
#include "Game_World.h"

bool is_right_id(Game_World & G1, int id); // 입력한 id가 올바른 입력인지 검사

// 게임 보드 출력
void draw_board(BoardView& b1, int& time, Game_World & G1);
// 명령어 관련 함수들
// m : move
void do_move_command(std::ofstream & log_file, Game_World & G1); // 이동 명령 함수
// c : carry
void set_load_to_Peasant(std::ofstream & log_file, Game_World & G1);
// s : show status
void show_status(std::ofstream & log_file, Game_World & G1);
// g : go
void go_command(std::ofstream & log_file, int& time, Game_World & G1);
// z : zoom
// o : original
// r : resize
// n : new
void add_command(std::ofstream & log_file, Game_World & G1);
void dynamic_memory_allocate(std::ofstream & log_file, Game_World & G1, const std::string& _name, char type, double x = 0, double y = 0);
// v : save
void save_data(std::ofstream & log_file, Game_World & G1);
// l : load
void load_data(std::ofstream & log_file, Game_World & G1);
// a : attack
void attack(std::ofstream & log_file, Game_World & G1);
// h : help
void show_command_list(); // 명령어 목록 출력용 함수
// q : quit

#endif // __MAIN__