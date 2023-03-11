#include "main.h"

/**
 * FixAng - reset @a to 0, when it less than 0 or above 359
 * @a: int
 * Return: float
 */

float FixAng(int a)
{
	return (a > 359 ? a - 360 : a < 0 ? a + 360 : a);

}

/**
 * degToRad - Converts angles from deg to rad
 * @a: int
 * Return: float
 */

float degToRad(int a)
{
	return (a * M_PI / 180.0);
}
