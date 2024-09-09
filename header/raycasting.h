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
/* 60 degrees converted to radians (π/3 radians) */

/* Declare the map array */
extern int map[MAP_HEIGHT][MAP_WIDTH];

/* Function prototypes */
void render(SDL_Renderer *renderer, double playerX, double playerY, double playerAngle);
int handle_events(SDL_Event *event);

/* For mouse movement */
void handleMouseMotion(SDL_Event *event, double *playerAngle);
/* For keyboard input and movement */
void handleKeyboardInput(SDL_Event *event, double *playerX, double *playerY, double *playerAngle);

#endif /* RAYCASTING_H */
