all: build

build:
	gcc -g -lSDL2 -lSDL2_image main3.c -o main
	./main
