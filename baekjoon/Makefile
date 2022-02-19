# compiler
CC = g++

# bits/stdc++.h (check the version (11.?)
# /usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits

# compiler flags:
CFLAGS  = -std=c++20 -Dpalilo -lm -Wall -O2

all: src/main.cpp
	clang-format -i src/main.cpp
	$(CC) $(CFLAGS) -o main src/main.cpp

clean:
	rm -r tc/*
