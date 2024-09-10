#include <SDL2/SDL.h>
#include <math.h>
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

int showMap = 1; // Ensure this is set to non-zero

/* Function to draw the map */
void drawMap(SDL_Renderer *renderer, double playerX, double playerY, double playerAngle) {
    const int cellSize = 20;

    // Loop through the map and draw each cell
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect rect;
            rect.x = x * cellSize;
            rect.y = y * cellSize;
            rect.w = cellSize;
            rect.h = cellSize;

            // Set color based on whether it's a wall or empty space
            if (map[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Wall color (red)
            } else {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Empty space color (gray)
            }
            SDL_RenderFillRect(renderer, &rect);  // Draw the cell
        }
    }

    // Draw the player on the map
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Player color (blue)
    SDL_Rect playerRect = {
        (int)(playerX * cellSize - 5), 
        (int)(playerY * cellSize - 5), 
        10, 10
    };
    SDL_RenderFillRect(renderer, &playerRect);

    // Draw the player's line of sight
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Line color (green)
    SDL_RenderDrawLine(renderer,
                       (int)(playerX * cellSize), (int)(playerY * cellSize),
                       (int)((playerX + cos(playerAngle) * 5) * cellSize),
                       (int)((playerY + sin(playerAngle) * 5) * cellSize));
}

/* Function to perform raycasting */
void performRaycasting(SDL_Renderer *renderer, double playerX, double playerY, double playerAngle) {
    const int numRays = 60; // Number of rays to cast
    const double angleStep = M_PI / 3 / numRays; // Angle between rays
    const int screenWidth = 640; // Width of the screen
    const int screenHeight = 480; // Height of the screen

    for (int i = 0; i < numRays; i++) {
        double rayAngle = playerAngle - M_PI / 6 + i * angleStep;
        double rayX = playerX;
        double rayY = playerY;
        double stepSize = 0.1;
        double distance = 0;
        int hit = 0;

        while (!hit && rayX >= 0 && rayY >= 0 && rayX < MAP_WIDTH && rayY < MAP_HEIGHT) {
            int mapX = (int)rayX;
            int mapY = (int)rayY;

            if (map[mapY][mapX] == 1) {
                hit = 1;
                distance = sqrt((rayX - playerX) * (rayX - playerX) + (rayY - playerY) * (rayY - playerY));
            } else {
                rayX += cos(rayAngle) * stepSize;
                rayY += sin(rayAngle) * stepSize;
            }
        }

        // Draw the ray
        double scale = 200 / (distance + 0.1); // Scale to fit the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Ray color (white)
        SDL_RenderDrawLine(renderer,
                           (int)(screenWidth / 2 + i * (screenWidth / numRays)), 0,
                           (int)(screenWidth / 2 + i * (screenWidth / numRays)), (int)(screenHeight - scale));
    }
}

/* Updated render function to include map drawing and 3D raycasting */
void render(SDL_Renderer *renderer, double playerX, double playerY, double playerAngle) {
    // Clear the screen with a black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the map if enabled
    if (showMap) {
        drawMap(renderer, playerX, playerY, playerAngle);
    }

    // Perform raycasting
    performRaycasting(renderer, playerX, playerY, playerAngle);

    // Present the final frame
    SDL_RenderPresent(renderer);
}
