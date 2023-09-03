compile:
	g++ index.cpp -o template.out -I/usr/include/SDL2 -D_REENTRANT -lSDL2

all: compile
	./template.out