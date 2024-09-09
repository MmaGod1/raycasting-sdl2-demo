#include <stdio.h>
#include <stdlib.h>
#include "raycasting.h"

int handle_events(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        return 0; // Exit the loop
    }
    return 1; // Continue running
}

void handleMouseMotion(SDL_Event *event, double *playerAngle) {
    if (event->type == SDL_MOUSEMOTION) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Mouse sensitivity
        const double mouseSensitivity = 0.001;

        *playerAngle += (mouseX - SCREEN_WIDTH / 2) * mouseSensitivity;
        if (*playerAngle < 0) *playerAngle += 2 * M_PI;
        if (*playerAngle >= 2 * M_PI) *playerAngle -= 2 * M_PI;

        // Center the mouse for continuous rotation
        SDL_WarpMouseInWindow(NULL, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
}

/* Function to handle keyboard input and update player position, including map toggle */
void handleKeyboardInput(SDL_Event *event, double *playerX, double *playerY, double *playerAngle) {
    const double moveSpeed = 0.1; // Speed at which the player moves
    const double turnSpeed = 0.05; // Speed at which the player turns
    double newX, newY;

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_w: // Move forward
                newX = *playerX + cos(*playerAngle) * moveSpeed;
                newY = *playerY + sin(*playerAngle) * moveSpeed;
                if (map[(int)newY][(int)newX] == 0) { // Check for wall collision
                    *playerX = newX;
                    *playerY = newY;
                }
                break;
            case SDLK_s: // Move backward
                newX = *playerX - cos(*playerAngle) * moveSpeed;
                newY = *playerY - sin(*playerAngle) * moveSpeed;
                if (map[(int)newY][(int)newX] == 0) { // Check for wall collision
                    *playerX = newX;
                    *playerY = newY;
                }
                break;
            case SDLK_a: // Turn left
                *playerAngle -= turnSpeed;
                if (*playerAngle < 0) *playerAngle += 2 * M_PI;
                break;
            case SDLK_d: // Turn right
                *playerAngle += turnSpeed;
                if (*playerAngle >= 2 * M_PI) *playerAngle -= 2 * M_PI;
                break;
            case SDLK_m: // Toggle map display
                showMap = !showMap;
                break;
        }
    }
}

void loadMap(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening map file");
        exit(EXIT_FAILURE);
    }

    int x = 0, y = 0;
    int ch;  // Use int to handle EOF properly

    printf("Reading map file: %s\n", filename);

    while ((ch = fgetc(file)) != EOF && y < MAP_HEIGHT) {
        printf("Reading character: %c at (y = %d, x = %d)\n", ch, y, x);

        if (ch == '\n') {
            // End of line, move to the next row
            y++;
            x = 0;
        } else {
            if (x < MAP_WIDTH) {
                if (ch == '#') {
                    map[y][x] = 1;  // Wall
                } else if (ch == '.') {
                    map[y][x] = 0;  // Empty space
                } else {
                    fclose(file);
                    fprintf(stderr, "Error: Invalid character '%c' in map file at (%d, %d)\n", ch, y, x);
                    exit(EXIT_FAILURE);
                }
                x++;
            } else {
                fprintf(stderr, "Error: Line %d exceeds expected width of %d characters\n", y, MAP_WIDTH);
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);

    printf("Finished reading the map. Read up to y = %d, x = %d\n", y, x);

    if (y < MAP_HEIGHT || x < MAP_WIDTH) {
        fprintf(stderr, "Unexpected end of map file. Expected dimensions %dx%d, but read %dx%d\n", MAP_WIDTH, MAP_HEIGHT, x, y);
        exit(EXIT_FAILURE);
    }
}
