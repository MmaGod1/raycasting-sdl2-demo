#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

/* Screen dimensions */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/* Map dimensions */
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

/**
 * struct Camera - Represents the player's camera.
 * @pos_x: Camera's position in the x direction.
 * @pos_y: Camera's position in the y direction.
 * @dir_x: Camera's direction in the x direction.
 * @dir_y: Camera's direction in the y direction.
 * @plane_x: Camera's plane in the x direction.
 * @plane_y: Camera's plane in the y direction.
 */
typedef struct Camera
{
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} Camera;

/* Function declarations */
int initialize_sdl(SDL_Window **window, SDL_Renderer **renderer);
void game_loop(SDL_Renderer *renderer, Camera *camera, int map[MAP_HEIGHT][MAP_WIDTH]);

/* Rendering functions */
void calculate_side_distance(Camera *camera, double ray_dir_x, double ray_dir_y,
                             double *side_dist_x, double *side_dist_y, int *step_x, int *step_y);
void render_column(SDL_Renderer *renderer, int x, int draw_start, int draw_end, int side);
void render_walls(SDL_Renderer *renderer, Camera *camera, int map[MAP_HEIGHT][MAP_WIDTH]);

/* Movement and rotation functions */
void move_forward(Camera *camera, int map[MAP_HEIGHT][MAP_WIDTH], double move_speed);
void move_backward(Camera *camera, int map[MAP_HEIGHT][MAP_WIDTH], double move_speed);
void rotate_left(Camera *camera, double rot_speed);
void rotate_right(Camera *camera, double rot_speed);

#endif /* RAYCASTING_H */
