CC = g++
SRC = Real_Pair.cpp Person.cpp Peasant.cpp Warrior.cpp Soldier.cpp Archer.cpp Observer.cpp BoardView.cpp Game_World.cpp main.cpp Console.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = War_Game

DEBUG += $(debug)

OBJ_FILES = $(filter-out Console.o, $(OBJ)) Console.o

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^

%.o: %.cpp %.h
	$(CC) -c $< $(DEBUG)

Console.o: Console.cpp Console.h
	$(CC) -c $< -D_WINDOWS $(DEBUG)

clean:
	del $(OBJ) War_Game.exe Game.log
