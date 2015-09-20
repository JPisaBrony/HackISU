all: build

build:
	gcc -g --std=c99 -lSDL2 -lm -lSDL2_image array.c path.c sdl_functions.c main.c -o coloranalayzer

test:
	gcc -g --std=c99 -lSDL2 -lm -lSDL2_image array.c test_edge.c path.c sdl_functions.c -o test
	
clean:
	rm coloranalayzer
