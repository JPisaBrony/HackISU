#ifndef HEADERS_AND_GLOBALS
#define HEADERS_AND_GLOBALS

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "image.h"
 
// event pooling
SDL_Event event;
// main window
SDL_Window *window = NULL;
// main screen
SDL_Surface *screen = NULL;
 
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

#include "sdl_functions_prototypes.h"
#include "sdl_functions.h"

#endif
