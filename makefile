CC = g++
SRC = Real_Pair.cpp Person.cpp Peasant.cpp Warrior.cpp Soldier.cpp Archer.cpp BoardView.cpp Game_World.cpp main.cpp Console.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = War_Game

# Debug flag
# DEBUG 모드 활성화 방법 : make debug=-DDEBUG 입력
DEBUG += $(debug)
	
# Object files
OBJ_FILES = $(filter-out Console.o, $(OBJ)) Console.o

# PRINT:
# 	@echo "DEBUG is $(debug)"

# Default target
$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^

# Generic rule for other .o files
%.o: %.cpp %.h
	$(CC) -c $< $(DEBUG)

# Specific rule for Console.o with -D_WINDOWS flag
Console.o: Console.cpp Console.h
	$(CC) -c $< -D_WINDOWS $(DEBUG)

clean:
	del $(OBJ) War_Game.exe Game.log

# # Conditional message printing
# ifeq ($(findstring -D_DEBUG, $(DEBUG)), -D_DEBUG)
# 	@echo "Compile with -D_DEBUG keyword"
# endif