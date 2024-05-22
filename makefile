CC = g++
SRC_DIR = .  # 소스 파일이 있는 디렉터리
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = War_Game

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) -c $<

clean:
	del $(OBJ) War_Game.exe