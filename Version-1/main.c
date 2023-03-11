#include "main.h"

/**
 * drawRay2D - Draw 2D rays, then cast them as walls by converting distance into height
 */

void drawRays2D()
{
	int r, mx, my, mp, dof;
	float vx, vy, rx, ry, ra, xo, yo, disV, disH, Tan;
	int ca, lineH, lineOff;

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

	RaySetUp();
	ra=FixAng(pa + 30); /* ray set back 30 degrees */
	for (r = 0; r < 60; r++)
	{
		/* ---Vertical--- */
		dof = 0;
		disV = 100000;
		Tan = tan(degToRad(ra));
		if(cos(degToRad(ra)) > 0.001)
		{
			rx = (((int)px >> 6) << 6) + 64;
			ry = (px - rx) * Tan + py;
			xo = 64;
			yo =- xo * Tan;
		} /* looking left */
		else if(cos(degToRad(ra)) < -0.001)
		{
			rx = (((int)px >> 6) << 6) - 0.0001; ry=(px-rx)*Tan+py;
			xo = -64;
			yo = -xo * Tan;
		} /* looking right */
  		else 
		{
			rx = px;
			ry = py;
			dof = 8;
		} /* looking up or down. no hit */
		while (dof<8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && mapW[mp] == 1)
			{
				dof = 8;
				disV = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra))*(ry-py);
			} /* hit */
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			} /* check next horizontal */
		}
		vx = rx;
		vy = ry;
		/* ---Horizontal--- */
		dof = 0;
		disH = 100000;
		Tan = 1.0 / Tan;
		if(sin(degToRad(ra)) > 0.001)
		{
			ry = (((int)py >> 6) << 6) - 0.0001;
			rx = (py - ry) * Tan + px;
			yo = -64;
			xo =- yo * Tan;
		} /* looking up */
		else if (sin(degToRad(ra)) < -0.001)
		{
			ry = (((int)py >> 6) << 6) + 64;
			rx = (py - ry) * Tan + px;
			yo = 64;
			xo =- yo * Tan;
		} /* looking down */
		else
		{
			rx = px;
			ry = py;
			dof = 8;
		} /* looking straight left or right */
		while(dof < 8)
		{ 
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && mapW[mp] == 1)
			{
				dof = 8;
				disH = cos(degToRad(ra)) * (rx - px) -sin(degToRad(ra)) * (ry - py);
			} /* hit */
			else
			{
				rx += xo;
				ry += yo;
				dof+=1;
			} /* check next horizontal */
		}
		glColor3f(0,0.8,0);
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disH = disV;
			glColor3f(0,0.6,0);
		} /* horizontal hit first */
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex2i(px,py);
		glVertex2i(rx,ry);
		glEnd(); /* draw 2D ray */

		ca = FixAng(pa - ra);
		disH = disH * cos(degToRad(ca)); /* fix fisheye */
		lineH = (mapS * 320) / (disH);
		if(lineH > 320)
		{
			lineH = 320;
		} /* line height and limit */
		lineOff = 160 - (lineH >> 1); /* line offset */
		glLineWidth(8);
		glBegin(GL_LINES);
		glVertex2i(r * 8 + 530,lineOff);
		glVertex2i(r * 8 + 530,lineOff + lineH);
		glEnd(); /* draw vertical wall */
		ra = FixAng(ra - 1);                                                              //go to next ray
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
	glutInit(&argc, argv); /* Initialize OpenGL */
	OpenGl_init();
	init();
	glutDisplayFunc(display); /* handles all display functions */
	glutKeyboardFunc(buttons); /* handles all pressed keys */
	glutMainLoop(); /* main game loop */
	return (true);
}
