# compiler
CC = g++

# bits/stdc++.h (check the version (11.?)
# /usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits

# rename files
# for i in *.txt; do mv -- "$i"  "${i%.txt}.out"; done

# compiler flags:
CFLAGS	= -Dpalilo -std=c++20 -O2 -lm -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion

all: src/main.cpp
	clang-format -i src/main.cpp
	$(CC) $(CFLAGS) -o main src/main.cpp

clean:
	rm -r tc/*
