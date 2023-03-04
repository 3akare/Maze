#include <stdio.h>
#include <SDL.h>
#include <math.h>

#define WIDTH 1024
#define HEIGHT 1024
#define PI 3.1415926535
//
// MAP
//

int mapX = 8, mapY = 8, mapS = 64;
int map[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

void DrawMap(SDL_Renderer **Renderer)
{
    int x, y;
    SDL_Rect Rect;
    Rect.w = (WIDTH/2 - (mapX - 1)) / mapX;
    Rect.h = (HEIGHT/2 - (mapY - 1)) / mapY;
    Rect.x = 0;
    Rect.y = 0;

    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            if(map[y*mapX+x] == 1)
                SDL_SetRenderDrawColor(*Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            else
                SDL_SetRenderDrawColor(*Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            Rect.x = x * (Rect.w + 1);
            Rect.y = y * (Rect.h + 1);
            SDL_RenderFillRect(*Renderer, &Rect);
        }
    }
}

int init(SDL_Window **window, SDL_Renderer **renderer)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Couldn't Initialise SDL: %s\n", SDL_GetError());
        return (0);
    }
    *window = SDL_CreateWindow("Library Assault", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
        fprintf(stderr, "Couldn't Create Window: %s\n", SDL_GetError());
        return (0);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        fprintf(stderr, "Couldn't Create Renderer: %s\n", SDL_GetError());
        return (0);
    }
    pd_x = cos(p_a) * 5;
    pd_y = sin(p_a) * 5;
    return (1);
};

void closeProgram(SDL_Window **window, SDL_Renderer **renderer)
{
    SDL_DestroyWindow(*window);
    SDL_DestroyRenderer(*renderer);
    SDL_Quit();
}

void ClearBackground(SDL_Renderer **Renderer)
{
    SDL_SetRenderDrawColor(*Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); //Set background color
    SDL_RenderClear(*Renderer); //I dont know yet
}
void DrawPlayer(SDL_Renderer **Renderer, SDL_Rect sdlRect)
{
    SDL_SetRenderDrawColor(*Renderer, 255, 255, 0, SDL_ALPHA_OPAQUE); //Set background color
    SDL_RenderFillRect(*Renderer, &sdlRect);
}

int main(int argc, char *argv[])
{
    SDL_Window *Window;
    SDL_Renderer *Renderer;
    SDL_Event event;
    int appIsRunning = 1;
    int upArrowDown = 0;
    int leftArrowDown = 0;
    int downArrowDown = 0;
    int rightArrowDown = 0;
    int numPixelsToMovePerFrame = (WIDTH/40)/4;
    SDL_Rect sdlRect;
    sdlRect.w = WIDTH/80;
    sdlRect.h = HEIGHT/80;
    sdlRect.x = 80;
    sdlRect.y = 80;

    if(!init(&Window, &Renderer))
    {
        fprintf(stderr, "Initialization Failed: %s\n", SDL_GetError());
        return(0);
    }
     while(appIsRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                appIsRunning = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_UP)
                {
                    upArrowDown = 1;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
                {
                leftArrowDown = 1;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
                {
                downArrowDown = 1;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                {
                rightArrowDown = 1;
                }
            }
             else if (event.type == SDL_KEYUP)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_UP)
                {
                upArrowDown = 0;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
                {
                leftArrowDown = 0;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
                {
                downArrowDown = 0;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                {
                rightArrowDown = 0;
                }
            }
        }
        if (upArrowDown)
        {
            p_x -= pd_x; p_y -= pd_y;
            sdlRect.y -= numPixelsToMovePerFrame;
        }
        if (leftArrowDown)
        {
            sdlRect.x -= numPixelsToMovePerFrame;
        }
        if (downArrowDown)
        {
            sdlRect.y += numPixelsToMovePerFrame;
        }
        if (rightArrowDown)
        {
            sdlRect.x += numPixelsToMovePerFrame;
        }
        ///Keep Player in the Screen//
        if (sdlRect.x < 0)
        {
            sdlRect.x = 0;
        }
        else if (sdlRect.x + sdlRect.w - 1 >= WIDTH)
        {
            sdlRect.x = WIDTH - sdlRect.w;
        }
        if (sdlRect.y < 0)
        {
            sdlRect.y = 0;
        }
        else if (sdlRect.y + sdlRect.h - 1 >= HEIGHT)
        {
            sdlRect.y = HEIGHT - sdlRect.h;
        }
        ClearBackground(&Renderer);
        DrawMap(&Renderer);
        DrawPlayer(&Renderer, sdlRect);
        SDL_RenderPresent(Renderer);
    }
    closeProgram(&Window, &Renderer);
}