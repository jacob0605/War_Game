#ifndef __MAIN__
#define __MAIN__

#include <fstream>

#include "BoardView.h"
#include "Game_World.h"

void draw_board(BoardView& b1, Game_World& G1);
void do_move_command(std::ofstream& log_file, Game_World& G1);
void set_load_to_Peasant(std::ofstream& log_file, Game_World& G1);
void show_status(std::ofstream& log_file, Game_World& G1);
void go_command(std::ofstream& log_file, Game_World& G1);
void add_command(std::ofstream& log_file, Game_World& G1);
void save_data(std::ofstream& log_file, Game_World& G1);
void load_data(std::ofstream& log_file, Game_World& G1);
void attack(std::ofstream& log_file, Game_World& G1);
void display_all(std::ofstream& log_file, Game_World& G1);
void show_command_list();

#endif // __MAIN__
