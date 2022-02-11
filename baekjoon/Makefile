# compiler
CC = g++

# compiler flags:
CFLAGS  = -std=c++20 -Dpalilo -lm -Wall -O2

all: src/main.cpp
	clang-format -i src/main.cpp
	$(CC) $(CFLAGS) -o main src/main.cpp

clean:
	rm -r tc/*
