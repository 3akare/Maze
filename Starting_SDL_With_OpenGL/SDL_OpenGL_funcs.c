#include "main.h"

/**
 * init - Starts up SDL, creates window, and initializes OpenGL
 * @gWindow: Address of Window
 * @gContext: OpenGL Context
 * Return: Boolean
 */

bool init(SDL_Window **gWindow, SDL_GLContext gContext)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return (false);
	}
	/* Use OpenGL 2.1 */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	/* Create window */
	*gWindow = SDL_CreateWindow("SDL Tutorial", X, Y, WI, HE, SDL_WINDOW_OPENGL);
	if (gWindow == NULL)
	{
		fprintf(stderr, "Window could'nt be created! %s\n", SDL_GetError());
		return (false);
	}
	/* Create context */
	gContext = SDL_GL_CreateContext(*gWindow);
	if (gContext == NULL)
	{
		fprintf(stderr, "context couldn't be created!: %s\n", SDL_GetError());
		return (false);
	}
	/* Use Vsync */
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		fprintf(stderr, "Warning: Unable to set VSync!: %s\n", SDL_GetError());
		return (false);
	}
	/* Initialize OpenGL */
	if (!initGL())
	{
		fprintf(stderr, "Unable to initialize OpenGL!\n");
		return (false);
	}
	return (true);
}

/**
 * initGL - Initializes matrices and clear color
 * Return: Boolean
 */
bool initGL(void)
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	/* Initialize Projection Matrix */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* Check for error */
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		success = false;
	}

	/* Initialize Modelview Matrix */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Check for error */
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		success = false;
	}

	/* Initialize clear color */
	glClearColor(0.f, 0.f, 0.f, 1.f);

	/* Check for error */
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		success = false;
	}

	return (success);
}
