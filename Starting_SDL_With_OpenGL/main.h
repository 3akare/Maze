#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <math.h>


/* OpenGL Headers */
#include <SDL_opengl.h>
#include <glu.h>



/* Screen dimension constants */
#define WI 640
#define HE 480
#define X (WI / 4)
#define Y (HE / 4)

/* Starts up SDL, creates window, and initializes OpenGL */
bool init(SDL_Window **gWindow, SDL_GLContext gContext);
/* Initializes matrices and clear color */
bool initGL(void);
/* Input handler */
void handleKeys(unsigned char key, int x, int y, bool gRenderQuad);
/* Per frame update */
void update(void);
/* Renders quad to the screen */
void render(bool gRenderQuad);
/* Frees media and shuts down SDL */
void close(SDL_Window **gWindow);
/* The window we'll be rendering to */


#endif
