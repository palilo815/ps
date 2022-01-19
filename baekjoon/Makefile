# compiler
CC = g++

# compiler flags:
CFLAGS  = -std=c++20 -Dpalilo -lm -Wall -O2

all: a.cpp
	clang-format -i a.cpp
	$(CC) $(CFLAGS) -o a a.cpp

clean:
	rm -r tc/*
