all: build

build:
	gcc -lSDL2 -lSDL2_image main3.c -o main
	./main
