#include "main.h"

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


/**
 * drawPlayer - Draws play in map
 */

void drawPlayer(void)
{
	/* Set Point and Line color to Yellow */
	glColor3f(1, 1, 0);
	/* Set point size to 8px */
	glPointSize(8);
	/* Set line width to 4px */
	glLineWidth(4);
	glBegin(GL_POINTS);
	/* Draw point (to signify player) */
	lVertex2i(px, py);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(px, py);
	/* Draw Line (to signify player's direction) */
	glVertex2i(px + pdx * 20, py + pdy * 20);
	glEnd();
}

/**
 * drawMap2D - Draws 2D map
*/

void drawMap2D(void)
{
	int x, y, xo, yo;
	int mapW[] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	};

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
			glVertex2i(0 + xo + 1, mapS + yo - 1);
			glVertex2i(mapS + xo - 1, mapS + yo - 1);
			glVertex2i(mapS + xo - 1, 0 + yo + 1);
			glEnd();
		}
	}
}
