#include <stdio.h>
#include <SDL.h>
#include <math.h>

#define WIDTH 1024
#define HEIGHT 1024
#define PI 3.1415926535
#define PLAYERSPEED 3.5
//
// MAP
//

float degToRad(int a)
{ 
    return a * M_PI/180.0;
}

int FixAng(int a){
    if(a > 359)
        a -= 360;
    if( a < 0 )
        a += 360; 
    return a;
}

int mapX = 8, mapY = 8, mapS = 64;
int map[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 1, 0, 1,
    1, 0, 1, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

void ray_casting(SDL_Renderer **renderer, float px, float py, float pa) {
    int r, mx, my, mp, dof, side, wall_angle;
    float vx, vy, rx, ry, ra, xo, yo, disV, disH;

    ra = FixAng(pa + 30); // ray set back 30 degrees

    for (r = 0; r < 60; r++) {
        //---Vertical---
        wall_angle = 0;
        dof = 0;
        side = 0;
        disV = 100000;
        float Tan = tan(degToRad(ra));
        if (cos(degToRad(ra)) > 0.001) {
            rx = (((int) px >> 6) << 6) + 64;
            ry = (px - rx) * Tan + py;
            xo = 64;
            yo = -xo * Tan;
        } else if (cos(degToRad(ra)) < -0.001) {
            rx = (((int) px >> 6) << 6) - 0.0001;
            ry = (px - rx) * Tan + py;
            xo = -64;
            yo = -xo * Tan;
        } else {
            rx = px;
            ry = py;
            dof = 8;
        } // looking up or down. no hit

        while (dof < 8) {
            mx = (int) (rx) >> 6;
            my = (int) (ry) >> 6;
            mp = my * mapX + mx;
            if (mp > 0 && mp < mapX * mapY && map[mp] == 1) {
                dof = 8;
                disV = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py); // hit
            } else {
                rx += xo;
                ry += yo;
                dof += 1;
            } // check next horizontal
        }
        vx = rx;
        vy = ry;

        //---Horizontal---
        dof = 0;
        disH = 100000;
        Tan = 1.0 / Tan;
        if (sin(degToRad(ra)) > 0.001) {
            ry = (((int) py >> 6) << 6) - 0.0001;
            rx = (py - ry) * Tan + px;
            yo = -64;
            xo = -yo * Tan;
        } else if (sin(degToRad(ra)) < -0.001) {
            ry = (((int) py >> 6) << 6) + 64;
            rx = (py - ry) * Tan + px;
            yo = 64;
            xo = -yo * Tan;
        } else {
            rx = px;
            ry = py;
            dof = 8;
        } // looking straight left or right

        while (dof < 8) {
            mx = (int) (rx) >> 6;
            my = (int) (ry) >> 6;
            mp = my * mapX + mx;
            if (mp > 0 && mp < mapX * mapY && map[mp] == 1) {
                dof = 8;
                disH = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py); // hit
            } else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        SDL_SetRenderDrawColor(*renderer, 195, 20, 0, SDL_ALPHA_OPAQUE);
        if (disV < disH) {
            rx = vx;
            ry = vy;
            disH = disV;
            wall_angle = 1;
            SDL_SetRenderDrawColor(*renderer, 253, 14, 0, SDL_ALPHA_OPAQUE); // horizontal hit first
        }
        SDL_RenderDrawLine(*renderer, px, py, rx, ry); // draw 2D ray

        int ca = FixAng(pa - ra);
        disH = disH * cos(degToRad(ca));
        int lineH = (mapS * 320) / (disH);
        if (lineH > 320) {
            lineH = 320;
        }
        int lineOff = 160 - (lineH >> 1);

        SDL_Rect wall = {r * 8 + 530, lineOff, 8, lineH};
        if(wall_angle == 1)
            SDL_SetRenderDrawColor(*renderer, 253, 14, 0, SDL_ALPHA_OPAQUE);
        else
            SDL_SetRenderDrawColor(*renderer, 195, 20, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(*renderer, &wall); // draw vertical wall

        ra = FixAng(ra - 1);
    }
}



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
    SDL_RenderClear(*Renderer);
}
void DrawPlayer(SDL_Renderer **Renderer, float px, float py, float pdx, float pdy, float pa)
{
    SDL_Rect sdlRect = {px - 10 , py -10, 20, 20};

    SDL_SetRenderDrawColor(*Renderer, 255, 255, 0, 255);
    SDL_RenderDrawPoint(*Renderer, px, py);
    SDL_RenderDrawLine(*Renderer, px, py, px+pdx*50, py+pdy*50);
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
    int numPixelsToMovePerFrame = (WIDTH/40)/100;
    float px, py, pdx, pdy, pa;

    //line
    px = 80;
    py = 80;
    pa = 0;
    pdx = cos(degToRad(pa));
    pdy = -sin(degToRad(pa));

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
            px += pdx*PLAYERSPEED;
            py += pdy*PLAYERSPEED;
        }
        if (leftArrowDown)
        {
            pa += PLAYERSPEED;
            pa = FixAng(pa);
            pdx = cos(degToRad(pa));
            pdy = -sin(degToRad(pa));
        }
        if (downArrowDown)
        {
            px -= pdx*PLAYERSPEED;
            py -= pdy*PLAYERSPEED;
        }
        if (rightArrowDown)
        {
            pa -= PLAYERSPEED;
            pa = FixAng(pa);
            pdx = cos(degToRad(pa));
            pdy = -sin(degToRad(pa));
        }
        ClearBackground(&Renderer);
        DrawMap(&Renderer);
        DrawPlayer(&Renderer, px, py, pdx, pdy, pa);
        ray_casting(&Renderer, px, py, pa);
        SDL_RenderPresent(Renderer);
    }
    closeProgram(&Window, &Renderer);
}