#include "raycasting.h"

/* Define the map dimensions */
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

/* Define the map array */
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  /* Top border */
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},  /* Mixed walls and open spaces */
    {1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}   /* Bottom border */
};

/* Function to render the scene using raycasting */
void render(SDL_Renderer *renderer, double playerX, double playerY, double playerAngle)
{
    int x;
    double rayAngle, distanceToWall, stepSize = 0.1;
    int lineHeight, drawStart, drawEnd, hit, testX, testY;
    int isVerticalHit;  /* Track if the wall hit is vertical (N/S) or horizontal (E/W) */

    for (x = 0; x < SCREEN_WIDTH; x++)
    {
        rayAngle = (playerAngle - FOV / 2.0) + (x / (double)SCREEN_WIDTH) * FOV;
        rayAngle *= (M_PI / 180.0);  // Convert degrees to radians
        distanceToWall = 0;
        hit = 0;
        isVerticalHit = 0;

        while (!hit && distanceToWall < 30)
        {
            distanceToWall += stepSize;
            testX = (int)(playerX + cos(rayAngle) * distanceToWall);
            testY = (int)(playerY + sin(rayAngle) * distanceToWall);

            if (testX < 0 || testX >= MAP_WIDTH || testY < 0 || testY >= MAP_HEIGHT)
            {
                hit = 1;
                distanceToWall = 30;
            }
            else if (map[testY][testX] == 1)
            {
                hit = 1;

                /* Determine if the hit was vertical (N/S) or horizontal (E/W) */
                if (fabs(cos(rayAngle)) > fabs(sin(rayAngle)))
                    isVerticalHit = 1;  /* More horizontal movement -> Vertical wall (N/S) */
            }
        }

        lineHeight = (int)(SCREEN_HEIGHT / distanceToWall);
        drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;

        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); /* Sky color */
        SDL_RenderDrawLine(renderer, x, 0, x, drawStart);

        /* Set wall color depending on its orientation */
        if (isVerticalHit)
            SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255); /* Wall facing N/S */
        else
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); /* Wall facing E/W */

        SDL_Rect wallRect = {x, drawStart, 1, drawEnd - drawStart};
        SDL_RenderFillRect(renderer, &wallRect);

        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); /* Floor color */
        SDL_RenderDrawLine(renderer, x, drawEnd, x, SCREEN_HEIGHT);
    }
}
