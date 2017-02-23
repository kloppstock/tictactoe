LIBS=
TARGET=tictactoe

CC=g++
CFLAGS=-O2 -Wall -Wextra -std=c++11

SRC=$(wildcard src/*.cpp) $(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
DEP=$(SRC:.cpp=.d)

.PHONY: clean all
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CC) -c -MMD $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ) $(TARGET) $(DEP)

-include $(DEP)
