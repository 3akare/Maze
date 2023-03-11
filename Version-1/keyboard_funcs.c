#include "main.h"

/**
 * buttons - Handles pressing of keys
 * @key: char
 * @x: unused
 * @y: unused
 */

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
	(void)x;
	(void)y;
	glutPostRedisplay();
	/* repost new frame (player position) after key is pressed */
}
