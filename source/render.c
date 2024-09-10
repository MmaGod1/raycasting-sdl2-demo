#include <SDL2/SDL.h>
#include "raycasting.h"

/**
 * Draw walls using raycasting.
 * @param renderer The SDL renderer.
 */
void draw_walls(SDL_Renderer *renderer)
{
    // Example: Draw a vertical line (placeholder for actual raycasting)
    SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); // Grey color for walls
    SDL_RenderDrawLine(renderer, 400, 0, 400, 600); // Vertical line in the middle
}

/**
 * Draw the map.
 * @param renderer The SDL renderer.
 */
void draw_map(SDL_Renderer *renderer)
{
    // Example map representation
    int map[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    int tile_size = 50;
    int map_width = 10;
    int map_height = 10;

    // Draw map grid
    for (int y = 0; y < map_height; ++y)
    {
        for (int x = 0; x < map_width; ++x)
        {
            if (map[y][x] == 1)
            {
                SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); // Grey color for walls
                SDL_Rect rect = { x * tile_size, y * tile_size, tile_size, tile_size };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    // Draw the player's line of sight
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for line of sight
    SDL_RenderDrawLine(renderer, player_x, player_y, player_x + 100 * cos(camera_angle), player_y + 100 * sin(camera_angle));
}

/**
 * Render the game state to the window.
 * @param renderer The SDL renderer.
 */
void render(SDL_Renderer *renderer)
{
    // Clear the screen with sky color (blue)
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue color
    SDL_RenderClear(renderer);

    // Draw ground (green) at the bottom half of the screen
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color for ground
    SDL_Rect ground_rect = { 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2 };
    SDL_RenderFillRect(renderer, &ground_rect);

    // Draw walls and map
    draw_walls(renderer);

    if (show_map)
        draw_map(renderer);
}
