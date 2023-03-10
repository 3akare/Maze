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
 * a; int
 * Return: float
 */

float degToRad(int a)
{
	return (a * M_PI/180.0);
}

/**
 * main - Main Entry Point
 * @argc: Commandline Count
 * @argv: Commandline Values
 *
 * Return: Always Successful
 */

int main(int argc, const char *argv[])
{
	float px, py, pa, pdy, pdx;
	glutInit(&argc, argv); /* Initialize OpenGL */
	OpenGl_init();
	init(px, py, pa, pdx, pdy);
	glutDisplayFunc(display); /* handles all display functions */
	glutKeyboardFunc(Buttons); /* handles all pressed keys */
	glutMainLoop(); /* main game loop */
	return (true);
}
