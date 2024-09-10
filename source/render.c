#include "raycasting.h"

/**
 * render_walls - Draws the walls using raycasting.
 * @renderer: The SDL renderer.
 * @camera: The player/camera's position and direction.
 * @map: The game map represented as a 2D array.
 */
void render_walls(SDL_Renderer *renderer, Camera *camera, int map[MAP_HEIGHT][MAP_WIDTH])
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        // Calculate the ray position and direction
        double camera_x = 2 * x / (double)SCREEN_WIDTH - 1; // x-coordinate in camera space
        double ray_dir_x = camera->dir_x + camera->plane_x * camera_x;
        double ray_dir_y = camera->dir_y + camera->plane_y * camera_x;

        // Determine which square of the map the ray is in
        int map_x = (int)camera->pos_x;
        int map_y = (int)camera->pos_y;

        // Calculate the distance to the next x and y sides
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);

        double side_dist_x, side_dist_y;

        // Determine step direction and initial side distance
        int step_x, step_y;
        int hit = 0; // Has the ray hit a wall?
        int side; // Was the wall hit on the x or y side?

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (camera->pos_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - camera->pos_x) * delta_dist_x;
        }

        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (camera->pos_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - camera->pos_y) * delta_dist_y;
        }

        // Perform DDA algorithm to find where the ray hits the wall
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }

            // Check if ray has hit a wall
            if (map[map_y][map_x] > 0) hit = 1;
        }

        // Calculate distance to the wall
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (map_x - camera->pos_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - camera->pos_y + (1 - step_y) / 2) / ray_dir_y;

        // Calculate height of line to draw on the screen
        int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

        // Calculate the lowest and highest pixel to fill in the wall stripe
        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;

        // Choose color for the wall based on the side of the wall
        SDL_SetRenderDrawColor(renderer, side == 0 ? 255 : 128, 0, 0, 255); // Red for x-side, darker for y-side

        // Draw the vertical line representing the wall
        SDL_RenderDrawLine(renderer, x, draw_start, x, draw_end);

        // Draw the ceiling and floor
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for ceiling
        SDL_RenderDrawLine(renderer, x, 0, x, draw_start);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for floor
        SDL_RenderDrawLine(renderer, x, draw_end, x, SCREEN_HEIGHT);
    }
}
