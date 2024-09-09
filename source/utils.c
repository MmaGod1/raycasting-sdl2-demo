#include "raycasting.h"

int handle_events(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        return 0; // Exit the loop
    }
    return 1; // Continue running
}

/* Function to handle keyboard input and update player position */
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
        }
    }
}



/* Handle mouse motion for rotating the camera */
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
