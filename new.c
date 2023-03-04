#include <SDL.h>
#include <math.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

float degToRad(int a) { return a*M_PI/180.0; }
int FixAng(int a){ if(a>359){ a-=360; } if(a<0){ a+=360; } return a; }

float px, py, pdx, pdy, pa;
SDL_Renderer* renderer;

void drawPlayer2D()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect playerRect = { px - 10, py - 10, 20, 20 };
    SDL_RenderDrawRect(renderer, &playerRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawLine(renderer, px, py, px + pdx * 20, py + pdy * 20);
}

void Buttons(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_a:
            pa += 5;
            pa = FixAng(pa);
            pdx = cos(degToRad(pa));
            pdy = -sin(degToRad(pa));
            break;
        case SDLK_d:
            pa -= 5;
            pa = FixAng(pa);
            pdx = cos(degToRad(pa));
            pdy = -sin(degToRad(pa));
            break;
        case SDLK_w:
            px += pdx * 5;
            py += pdy * 5;
            break;
        case SDLK_s:
            px -= pdx * 5;
            py -= pdy * 5;
            break;
        }
    }
}

int main(int argc, char* args[])
{
    SDL_Window* window = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL2 Player2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    px = SCREEN_WIDTH / 2;
    py = SCREEN_HEIGHT / 2;
    pdx = cos(degToRad(pa));
    pdy = -sin(degToRad(pa));

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            Buttons(e);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawPlayer2D();

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
