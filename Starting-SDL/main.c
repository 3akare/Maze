#include "main.h"

/**
 * main - Main Entry of SDL program
 * @ac: commandline arguments count
 * @av: commandline arguments value
 * Return: Always Successful
 */

int main(__attribute__((unused)) int ac, __attribute__((unused)) char *av[])
{
	SDL_Window *gWindow = NULL;
	SDL_Renderer *gRenderer = NULL;
	SDL_Event event;
	SDL_KeyboardEvent key;
	int status = 1;

	init(&gWindow, &gRenderer);
	while (status)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					status = 0;
				case SDL_KEYDOWN:
					key = event.key;
					if (key.keysym.scancode == 0x29)
						status = 0;
			}
		}
	}
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
	return (0);
}

/**
 * init - SDL Initialization function
 * @window: SDL_Window variable
 * @renderer: SDL_Rendere variable
 * Return: 0 in fail, 1 on success
 */
int init(SDL_Window **window, SDL_Renderer **renderer)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
		return (0);
	}

	*window = SDL_CreateWindow("Test", XPOS, YPOS, WID, HEI, SDL_WINDOW_SHOWN);
	return (0);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
		return (0);
	}
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
		return (0);
	}
	return (1);
}
