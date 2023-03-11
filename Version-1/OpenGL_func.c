#include "main.h"

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
 * RaySetUp - Sets up casting background by drawing 2 shades of blue
 * to differentiate sky from gound
 */

void RaySetUp(void)
{
	/* Sky */
	glColor3f(0, 1, 1);
	glBegin(GL_QUADS);
	glVertex2i(526, 0);
	glVertex2i(1006, 0);
	glVertex2i(1006, 160);
	glVertex2i(526, 160);
	glEnd();

	/* Ground */
	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
	glVertex2i(526, 160);
	glVertex2i(1006, 160);
	glVertex2i(1006, 320);
	glVertex2i(526, 320);
	glEnd();
}
