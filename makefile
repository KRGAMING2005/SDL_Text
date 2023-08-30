compile:
	g++ main.cpp -I/usr/include/SDL2 -D_REENTRANT -lSDL2

all: compile
	./a.out