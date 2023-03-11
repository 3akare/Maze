#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>

/* OPenGL headers */
#include<OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>


#define WID 1024 /* window width */
#define HEI  512 /* window height */
#define XPOS (WID / 4)
#define YPOS (HEI / 4)
#define mapX 8 /* Map width */
#define mapY 8 /* Map height */
#define mapS 64 /* Map Cubic Size */
#define SPEED 10 /* Player speed */

float px, py, pa, pdy, pdx;

void OpenGl_init(void);
void init(void);
float degToRad(int a);
float FixAng(int a);
void display(void);
void drawPlayer(void);
void drawMap2D(void);
void drawRays2D(void);
void RaySetUp(void);
void buttons(unsigned char key, int x, int y);

#endif
