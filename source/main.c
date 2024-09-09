#include <SDL2/SDL.h>
#include "raycasting.h"

/**
 * main - Entry point for the raycasting program.
 *
 * Return: 0 on success, or error code.
 */
int main(void)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    double playerX = 3.5, playerY = 3.5, playerAngle = 1.57;
    int running = 1;
    const double moveSpeed = 0.1; // Speed of movement

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Raycasting Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRelativeMouseMode(SDL_TRUE); // Enable relative mouse mode

    /* Main loop */
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w: // Move forward
                        playerX += cos(playerAngle) * moveSpeed;
                        playerY += sin(playerAngle) * moveSpeed;
                        break;
                    case SDLK_s: // Move backward
                        playerX -= cos(playerAngle) * moveSpeed;
                        playerY -= sin(playerAngle) * moveSpeed;
                        break;
                    case SDLK_a: // Strafe left
                        playerX -= cos(playerAngle + M_PI_2) * moveSpeed;
                        playerY -= sin(playerAngle + M_PI_2) * moveSpeed;
                        break;
                    case SDLK_d: // Strafe right
                        playerX += cos(playerAngle - M_PI_2) * moveSpeed;
                        playerY += sin(playerAngle - M_PI_2) * moveSpeed;
                        break;
                }
            }
            if (event.type == SDL_MOUSEMOTION) {
                handleMouseMotion(&playerAngle); // Update angle based on mouse movement
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render(renderer, playerX, playerY, playerAngle);

        SDL_RenderPresent(renderer);
    }

    SDL_SetRelativeMouseMode(SDL_FALSE); // Disable relative mouse mode when exiting

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
