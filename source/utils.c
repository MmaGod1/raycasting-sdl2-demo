#include <stdio.h>
#include <stdlib.h>
#include "raycasting.h"


/* Initialize to 0 (map off by default) */
int showMap = 0;

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



#define MAX_LINE_LENGTH 100  // Arbitrary large value for line buffer

void loadMap(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening map file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int y = 0;

    printf("Reading map file: %s\n", filename);

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        // Strip newline characters (if any)
        line[strcspn(line, "\n")] = '\0';

        if (y >= MAP_HEIGHT) {
            fprintf(stderr, "Error: Map file has more rows than expected (MAP_HEIGHT = %d)\n", MAP_HEIGHT);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        // Check if the line length matches MAP_WIDTH
        int lineLength = strlen(line);
        if (lineLength != MAP_WIDTH) {
            fprintf(stderr, "Error: Line %d in map has %d characters, expected %d\n", y, lineLength, MAP_WIDTH);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        // Parse each character in the line
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (line[x] == '#') {
                map[y][x] = 1;  // Wall
            } else if (line[x] == '.') {
                map[y][x] = 0;  // Empty space
            } else {
                fprintf(stderr, "Error: Invalid character '%c' at (%d, %d) in map file\n", line[x], y, x);
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }

        y++;
    }

    fclose(file);

    // Ensure the map has exactly the expected number of rows
    if (y < MAP_HEIGHT) {
        fprintf(stderr, "Error: Map file has fewer rows than expected (MAP_HEIGHT = %d)\n", MAP_HEIGHT);
        exit(EXIT_FAILURE);
    }

    printf("Map loaded successfully.\n");
}
