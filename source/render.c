#include "raycasting.h"

/**
 * calculate_side_distance - Calculates the distance to the next x and y sides.
 * @camera: Pointer to the camera struct.
 * @ray_dir_x: Ray direction in x-axis.
 * @ray_dir_y: Ray direction in y-axis.
 * @side_dist_x: Distance to the next x-side.
 * @side_dist_y: Distance to the next y-side.
 * @step_x: Step in the x direction.
 * @step_y: Step in the y direction.
 */
void calculate_side_distance(Camera *camera, double ray_dir_x,
                             double ray_dir_y, double *side_dist_x,
                             double *side_dist_y, int *step_x, int *step_y)
{
    if (ray_dir_x < 0)
    {
        *step_x = -1;
        *side_dist_x = (camera->pos_x - (int)camera->pos_x) / ray_dir_x;
    }
    else
    {
        *step_x = 1;
        *side_dist_x = ((int)camera->pos_x + 1.0 - camera->pos_x) / ray_dir_x;
    }

    if (ray_dir_y < 0)
    {
        *step_y = -1;
        *side_dist_y = (camera->pos_y - (int)camera->pos_y) / ray_dir_y;
    }
    else
    {
        *step_y = 1;
        *side_dist_y = ((int)camera->pos_y + 1.0 - camera->pos_y) / ray_dir_y;
    }
}

/**
 * render_column - Draws a vertical column of the wall, ceiling, and floor.
 * @renderer: SDL renderer.
 * @x: The column x-coordinate on the screen.
 * @draw_start: Start position of the wall.
 * @draw_end: End position of the wall.
 * @side: Whether the wall was hit on x-side or y-side.
 */
void render_column(SDL_Renderer *renderer, int x, int draw_start, int draw_end, int side)
{
    SDL_SetRenderDrawColor(renderer, side == 0 ? 255 : 128, 0, 0, 255);
    SDL_RenderDrawLine(renderer, x, draw_start, x, draw_end);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); /* Blue ceiling */
    SDL_RenderDrawLine(renderer, x, 0, x, draw_start);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); /* Green floor */
    SDL_RenderDrawLine(renderer, x, draw_end, x, SCREEN_HEIGHT);
}

/**
 * render_walls - Renders all wall columns using raycasting.
 * @renderer: SDL renderer.
 * @camera: Pointer to the camera struct.
 * @map: 2D map of the game world.
 */
void render_walls(SDL_Renderer *renderer, Camera *camera, int map[MAP_HEIGHT][MAP_WIDTH])
{
    int x, step_x, step_y, hit, side;
    double ray_dir_x, ray_dir_y, side_dist_x, side_dist_y;
    double perp_wall_dist, delta_dist_x, delta_dist_y;

    for (x = 0; x < SCREEN_WIDTH; x++)
    {
        calculate_ray_dir(camera, x, &ray_dir_x, &ray_dir_y);
        calculate_side_distance(camera, ray_dir_x, ray_dir_y,
                                &side_dist_x, &side_dist_y, &step_x, &step_y);
        perform_dda(&map_x, &map_y, step_x, step_y, &hit, &side);
        perp_wall_dist = calculate_wall_distance(ray_dir_x, ray_dir_y, side);
        draw_vertical_line(renderer, x, perp_wall_dist, side);
    }
}
