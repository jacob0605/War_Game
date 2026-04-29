#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>

#include "Archer.h"
#include "Observer.h"
#include "Peasant.h"
#include "Soldier.h"
#include "bad_input.h"
#include "main.h"

#define GAME_LOG_FILE "Game.log"

using namespace std;

namespace {

int read_int_or_throw(const char* message) {
    int value = 0;
    if (!(cin >> value)) {
        throw bad_input(message);
    }
    return value;
}

double read_double_or_throw(const char* message) {
    double value = 0.0;
    if (!(cin >> value)) {
        throw bad_input(message);
    }
    return value;
}

Person* require_object(Game_World& world, int id) {
    Person* person = world.get_object_ptr(id);
    if (person == nullptr) {
        throw bad_input("No object has that ID");
    }
    return person;
}

} // namespace

int main() {
    BoardView board;
    Game_World world;
    ofstream log_file(GAME_LOG_FILE);

    if (!log_file.is_open()) {
        cerr << "Error, Failed to open file " << GAME_LOG_FILE << endl;
        return 1;
    }

    cout << "\nCpp camp homework project#4\n" << endl;
    cout << "Game Start!" << endl;

    bool running = true;
    while (running) {
        draw_board(board, world);
        cout << "Enter command(press 'h' to view command list): ";

        try {
            char command = '\0';
            if (!(cin >> command)) {
                break;
            }

            command = static_cast<char>(tolower(static_cast<unsigned char>(command)));
            switch (command) {
                case 'm':
                    do_move_command(log_file, world);
                    break;
                case 'c':
                    set_load_to_Peasant(log_file, world);
                    break;
                case 's':
                    show_status(log_file, world);
                    break;
                case 'g':
                    go_command(log_file, world);
                    break;
                case 'z':
                    board.set_scale(read_double_or_throw("Scale must be a number"));
                    break;
                case 'o': {
                    double x = read_double_or_throw("Origin x must be a number");
                    double y = read_double_or_throw("Origin y must be a number");
                    board.set_origin(x, y);
                    break;
                }
                case 'r':
                    board.set_size(read_int_or_throw("Board size must be an integer"));
                    break;
                case 'n':
                    add_command(log_file, world);
                    break;
                case 'v':
                    save_data(log_file, world);
                    break;
                case 'l':
                    load_data(log_file, world);
                    break;
                case 'a':
                    attack(log_file, world);
                    break;
                case 'd':
                    display_all(log_file, world);
                    break;
                case 'h':
                    show_command_list();
                    break;
                case 'q':
                    cout << "quit program" << endl;
                    log_file << "quit program" << endl;
                    running = false;
                    break;
                default:
                    throw bad_input("Wrong command");
            }
        } catch (const bad_input& e) {
            cout << e.what() << endl;
            cout.flush();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    world.clear();
    return 0;
}

void draw_board(BoardView& board, Game_World& world) {
    cout << "\nTime: " << world.get_time() << endl;
    board.clear();
    world.generate_display(board);
    board.draw();
    cout << endl;
}

void do_move_command(ofstream& log_file, Game_World& world) {
    const int id = read_int_or_throw("ID must be an integer");
    const double x = read_double_or_throw("x must be a number");
    const double y = read_double_or_throw("y must be a number");

    Person* person = require_object(world, id);
    person->move_command(Real_Pair(x, y));
    cout << "Move id: " << id << " to " << x << ',' << y << endl;
    log_file << "Move id: " << id << " to " << x << ',' << y << endl;
}

void set_load_to_Peasant(ofstream& log_file, Game_World& world) {
    const int id = read_int_or_throw("ID must be an integer");
    const double load = read_double_or_throw("Load must be a number");

    Person* person = require_object(world, id);
    person->set_load(load);
    log_file << "Set load " << load << " to " << id << endl;
}

void show_status(ofstream& log_file, Game_World& world) {
    const int id = read_int_or_throw("ID must be an integer");
    Person* person = require_object(world, id);
    person->display_status();
    log_file << "Show ID(" << id << ") status" << endl;
}

void go_command(ofstream& log_file, Game_World& world) {
    world.advance_time();
    world.update_all_objects();
    cout << "Game proceed" << endl;
    log_file << "Game proceed" << endl;
}

void add_command(ofstream& log_file, Game_World& world) {
    char type = '\0';
    double x = 0.0;
    double y = 0.0;
    string name;

    if (!(cin >> type >> x >> y >> name)) {
        throw bad_input("new command format: n <type> <x> <y> <name>");
    }

    type = static_cast<char>(toupper(static_cast<unsigned char>(type)));
    const int id = world.get_new_ID();
    Person* ptr = nullptr;

    switch (type) {
        case 'P':
            ptr = new Peasant(&world, id, x, y, name);
            break;
        case 'S':
            ptr = new Soldier(&world, id, x, y, name);
            break;
        case 'A':
            ptr = new Archer(&world, id, x, y, name);
            break;
        case 'O':
            ptr = new Observer(&world, id, x, y, name);
            break;
        default:
            throw bad_input("Type must be one of P, S, A, O");
    }

    world.add_object(ptr);
    cout << "Make new character, type: " << type << " at " << x << ", " << y << endl;
    log_file << "Make new character, type: " << type << " at " << x << ", " << y << endl;
}

void save_data(ofstream& log_file, Game_World& world) {
    world.save();
    cout << "Save game data" << endl;
    log_file << "Save game data" << endl;
}

void load_data(ofstream& log_file, Game_World& world) {
    world.restore();
    cout << "Load game data" << endl;
    log_file << "Load game data" << endl;
}

void attack(ofstream& log_file, Game_World& world) {
    const int attacker_id = read_int_or_throw("Attacker ID must be an integer");
    const int target_id = read_int_or_throw("Target ID must be an integer");

    Person* attacker = require_object(world, attacker_id);
    require_object(world, target_id);
    attacker->attack_command(target_id);
    log_file << "Attack " << attacker_id << " -> " << target_id << endl;
}

void display_all(ofstream& log_file, Game_World& world) {
    world.display_all_objects();
    log_file << "Display all objects" << endl;
}

void show_command_list() {
    cout << endl;
    cout << "m ID x y : move command" << endl;
    cout << "c ID w   : carry command" << endl;
    cout << "s ID     : show status" << endl;
    cout << "d        : display all objects" << endl;
    cout << "g        : advance time" << endl;
    cout << "z s      : zoom" << endl;
    cout << "o x y    : set origin" << endl;
    cout << "r s      : resize board" << endl;
    cout << "n T x y name : create object (T=P/S/A/O)" << endl;
    cout << "v        : save" << endl;
    cout << "l        : load" << endl;
    cout << "a id1 id2: attack" << endl;
    cout << "q        : quit" << endl;
    cout << endl;
}
