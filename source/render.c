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
 * calculate_ray_dir - Calculates the direction of the ray for a given x coordinate.
 * @camera: Pointer to the camera struct.
 * @x: The x coordinate on the screen.
 * @ray_dir_x: Pointer to store ray direction in x-axis.
 * @ray_dir_y: Pointer to store ray direction in y-axis.
 */
void calculate_ray_dir(Camera *camera, int x, double *ray_dir_x, double *ray_dir_y)
{
    double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
    *ray_dir_x = camera->dir_x + camera->plane_x * camera_x;
    *ray_dir_y = camera->dir_y + camera->plane_y * camera_x;
}

/**
 * perform_dda - Performs the DDA algorithm to find the wall hit point.
 * @map_x: Pointer to the current map x-coordinate.
 * @map_y: Pointer to the current map y-coordinate.
 * @step_x: Step in the x direction.
 * @step_y: Step in the y direction.
 * @hit: Pointer to store whether a wall was hit.
 * @side: Pointer to store whether the wall was hit on the x-side or y-side.
 */
void perform_dda(int *map_x, int *map_y, int step_x, int step_y, int *hit, int *side)
{
    int side_dist_x = 0;
    int side_dist_y = 0;
    *hit = 0;

    while (!(*hit))
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            *map_x += step_x;
            *side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            *map_y += step_y;
            *side = 1;
        }

        if (world_map[*map_x][*map_y] > 0)
            *hit = 1;
    }
}

/**
 * calculate_wall_distance - Calculates the distance to the wall.
 * @ray_dir_x: Ray direction in x-axis.
 * @ray_dir_y: Ray direction in y-axis.
 * @side: Whether the wall was hit on x-side or y-side.
 * 
 * Return: The perpendicular distance to the wall.
 */
double calculate_wall_distance(double ray_dir_x, double ray_dir_y, int side)
{
    return side == 0 ? fabs((map_x - camera->pos_x + (1 - step_x) / 2) / ray_dir_x) :
                        fabs((map_y - camera->pos_y + (1 - step_y) / 2) / ray_dir_y);
}

/**
 * draw_vertical_line - Draws a vertical line representing a wall column.
 * @renderer: SDL renderer.
 * @x: The x coordinate of the column.
 * @perp_wall_dist: The perpendicular distance to the wall.
 * @side: Whether the wall was hit on x-side or y-side.
 */
void draw_vertical_line(SDL_Renderer *renderer, int x, double perp_wall_dist, int side)
{
    int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
    int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
    int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;

    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= SCREEN_HEIGHT)
        draw_end = SCREEN_HEIGHT - 1;

    render_column(renderer, x, draw_start, draw_end, side);
}
