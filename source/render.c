#include <SDL2/SDL.h>
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

/* Function to draw the map */
void drawMap(SDL_Renderer *renderer, double playerX, double playerY, double playerAngle) {
    const int cellSize = 20;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect rect;
            rect.x = x * cellSize;
            rect.y = y * cellSize;
            rect.w = cellSize;
            rect.h = cellSize;

            if (map[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Wall color
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Empty space color
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Draw the player's line of sight
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Line color
    SDL_RenderDrawLine(renderer, playerX * cellSize, playerY * cellSize,
                       (playerX + cos(playerAngle) * 10) * cellSize,
                       (playerY + sin(playerAngle) * 10) * cellSize);
}

/* Updated render function to include map drawing and 3D raycasting */
void render(SDL_Renderer *renderer, double playerX, double playerY, double playerAngle) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the map if enabled
    if (showMap) {
        drawMap(renderer, playerX, playerY, playerAngle);
    }

    // Add raycasting-based rendering code here (original content from the first render function)

    SDL_RenderPresent(renderer);
}
