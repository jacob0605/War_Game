cmake_minimum_required(VERSION 3.10.0)
project(test_make VERSION 0.1.0 LANGUAGES C CXX)

add_executable(test_make Archer.cpp BoardView.cpp Console.cpp Game_World.cpp main.cpp Peasant.cpp Person.cpp Real_Pair.cpp Soldier.cpp Warrior.cpp)

include(CTest)
enable_testing()

