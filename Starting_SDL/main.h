#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#define WID 1024 /* window width */
#define HEI  512 /* window height */
#define XPOS (WID / 4)
#define YPOS (HEI / 4)

int init(SDL_Window **window, SDL_Renderer **renderer);

#endif
