CC = g++
SRC = Real_Pair.cpp Person.cpp Peasant.cpp Warrior.cpp Soldier.cpp Archer.cpp BoardView.cpp Game_World.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = War_Game

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

%.o: %.cpp %.h
	$(CC) -c $<

clean:
	del $(OBJ) War_Game.exe Game.log