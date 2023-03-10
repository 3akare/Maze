#include "main.h"

/**
 * handleKeys - Input handler
 * @key: unsigned char
 * @x: int
 * @y: int
 * @gRenderQuad: bool
 */

void handleKeys(unsigned char key, int x, int y, bool gRenderQuad)
{
	x--, y--;
	x++, y++;
	/* Toggle quad */
	if (key == 'q')
	{
		gRenderQuad = !gRenderQuad;
	}
}

/**
 * update - Per frame update
 */

void update(void)
{
	/* No per frame update needed */
}

/**
 * render - Renders quad to screen
 * @gRenderQuad: bool
*/

void render(bool gRenderQuad)
{
	/* Clear color buffer */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Render quad */
	if (gRenderQuad)
	{
		glBegin(GL_QUADS);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f(0.5f, -0.5f);
			glVertex2f(0.5f, 0.5f);
			glVertex2f(-0.5f, 0.5f);
		glEnd();
	}
}

/**
 * close - Frees media and shuts down SDL
 * @gWindow: Address of Window
 */

void close(SDL_Window **gWindow)
{
	/* Destroy window	 */
	SDL_DestroyWindow(*gWindow);
	gWindow = NULL;

	/* Quit SDL subsystems */
	SDL_Quit();
}

/**
 * main - Main Entry
 * @argc: argument count
 * @args: argument value
 * Return: 0
 */
int main(__attribute__((unused))int argc, __attribute__((unused))char *args[])
{
	SDL_Window *gWindow = NULL;
	SDL_GLContext gContext = NULL;
	bool gRenderQuad = true;

	/* Start up SDL and create window */
	if (!init(&gWindow, gContext))
		fprintf(stderr, "Failed to initialize!\n");
	else
	{
		bool quit = false; /* Main loop flag */
		SDL_Event e; /* Event handler */
		/* Enable text input */
		SDL_StartTextInput();
		/* While application is running */
		while (!quit)
		{
			/* Handle events on queue */
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT) /* User requests quit */
					quit = true;
			}
			render(gRenderQuad); /* Render quad */
			SDL_GL_SwapWindow(gWindow); /* Update screen */
		}
		/* Disable text input */
		SDL_StopTextInput();
	}
	/* Free resources and close SDL */
	close(&gWindow);
	return (0);
}
