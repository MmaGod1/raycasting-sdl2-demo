#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>
#include <math.h>

/* Define screen dimensions */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/* Define map dimensions */
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

/* Define Field of View (FOV) in radians */
#define FOV (60 * (M_PI / 180))

/* Declare the map array */
extern int map[MAP_HEIGHT][MAP_WIDTH];

/* Function prototypes */
void render(SDL_Renderer *renderer, double playerX, double playerY, double playerAngle);
int handle_events(SDL_Event *event);

#endif /* RAYCASTING_H */
