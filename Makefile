all: build

build:
	gcc -g -lSDL2 -lSDL2_image main.c -o main
	./main
