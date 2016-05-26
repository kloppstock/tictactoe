CC = g++
LIBS = 
CFLAGS = -O2 -Wall -Wextra
FILES = main.cpp src/Board.cpp src/HumanPlayer.cpp src/RandomPlayer.cpp
O_FILES = main.o src/Board.o src/HumanPlayer.o src/RandomPlayer.o

TARGET = tictactoe

build: $(FILES)
	$(CC) -o $(TARGET) $(FILES) $(LIBS) $(CFLAGS)

clean:
	rm -f $(O_FILES)
	rm -f $(TARGET)

rebuild: clean build
