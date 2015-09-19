all: build

build:
	gcc -g --std=c99 -lSDL2 -lSDL2_image main.c sdl_functions.c -o main
	./main twi.png

test:
	gcc -g --std=c99 -lSDL2 -lm -lSDL2_image array.c test_edge.c path.c sdl_functions.c -o test
	
clean:
	rm main
