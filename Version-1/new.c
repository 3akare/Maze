#include "main.h"
float px, py, pa, pdy, pdx;

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
void init(void)
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
	drawPlayer();
	drawRays2D();
	glutSwapBuffers(); /* push data from back buffer to the front buffer */
}

void drawPlayer()
{
	/* Set Point and Line color to Yellow */
	glColor3f(1, 1, 0);
	/* Set point size to 8px */
	glPointSize(8);
	/* Set line width to 4px */
	glLineWidth(4);
	glBegin(GL_POINTS);
	/* Draw point (to signify player) */
	glVertex2i(px, py);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(px, py);
	/* Draw Line (to signify player's direction) */
	glVertex2i(px + pdx * 20, py + pdy * 20);
	glEnd();
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
 * FixAng - reset @a to 0, when it less than 0 or above 359
 * @a: int
 * Return: float
 */

float FixAng(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

void buttons(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		pa += SPEED;
		pa = FixAng(pa);
		pdx = cos(degToRad(pa));
		pdy = -sin(degToRad(pa));
	}
	if (key == 'd')
	{
		pa -= SPEED;
		pa = FixAng(pa);
		pdx = cos(degToRad(pa));
		pdy = -sin(degToRad(pa));
	}
	if (key == 'w')
	{
		px += pdx * SPEED;
		py += pdy * SPEED;
	}
	if (key == 's')
	{
		px -= pdx * SPEED;
		py -= pdy * SPEED;
	}
	glutPostRedisplay();
	/* repost new frame (player position) after key is pressed */
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
	glutInit(&argc, argv); /* Initialize OpenGL */
	OpenGl_init();
	init();
	glutDisplayFunc(display); /* handles all display functions */
	glutKeyboardFunc(buttons); /* handles all pressed keys */
	glutMainLoop(); /* main game loop */
	return (true);
}
