#include "main.h"

int mapW[]=           //the map array. Edit to change level but keep the outer walls
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
};


/**
 * OpenGl_init - Initialize OpenGL
 */

void OpenGl_init(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WID, HEI); /* Initialize Window size*/
	glutCreateWindow("Version 1"); /* Create Window, and Add window title */	
}

/**
 * init - Sets Player postioning
 * px: player pos on x-axis
 * py: player pos o y-axis
 * pa: player angle
 * pdy:  float
 * pdx: float 
 */
void init(float px, float py, float pa, float pdy, float pdx)
{
	glClearColor(0.3, 0.3, 0.3, 0); /* clear and set screen to grey */
	gluOrtho2D(0, WID, HEI, 0);
	px = 150;
	py = 400;
	pa = 90;
	pdx = cos(degToRad(pa));
	pdy = -sin(degToRad(pa));
}

/**
 * degToRad - Converts angles from deg to rad
 * a: int
 * Return: float
 */

float degToRad(int a)
{
	return (a * M_PI/180.0);
}

/**
 * display - draws map and rays
 */

void display(void)
{
	/* Clear the buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap2D();
	// drawRays2D();
	glutSwapBuffers(); /* push data from back buffer to the front buffer */
}

void drawMap2D()
{
	int x, y, xo, yo;

	for (y = 0; y < mapX; y++)
	{
		for (x = 0; x < mapX; x++)
		{
			if (mapW[y * mapX + x] == 1)
				glColor3f(1, 1, 1); /* if 1 draw a white box */
			else
				glColor3f(0, 0, 0); /* else draw a black box */
			xo = x * mapS;
			yo = y * mapS;
			/* Set Dimensions of the Map */
			glBegin(GL_QUADS);
			glVertex2i(0 + xo + 1, 0 + yo + 1);
			glVertex2i(0 + xo + 1, mapS + yo -1);
			glVertex2i(mapS + xo - 1, mapS + yo - 1);
			glVertex2i(mapS + xo- 1, 0 + yo + 1);
			glEnd();
		}
	}
}
/**
 * main - Main Entry Point
 * @argc: Commandline Count
 * @argv: Commandline Values
 *
 * Return: Always Successful
 */

int main(int argc, char *argv[])
{
	float px, py, pa, pdy, pdx;
	glutInit(&argc, argv); /* Initialize OpenGL */
	OpenGl_init();
	init(px, py, pa, pdx, pdy);
	glutDisplayFunc(display); /* handles all display functions */
	// glutKeyboardFunc(Buttons); /* handles all pressed keys */
	glutMainLoop(); /* main game loop */
	return (true);
}
