#include "raycasting.h"

/**
 * handle_events - Handles SDL events.
 * @event: Pointer to the SDL_Event structure.
 *
 * Return: 0 to exit the program, 1 to continue running.
 */

#define TURN_SPEED 0.005

void handleMouseMotion(double *playerAngle) {
    int mouseX, mouseY;
    SDL_GetRelativeMouseState(&mouseX, &mouseY);

    *playerAngle -= mouseX * TURN_SPEED; // Adjust the angle based on mouse movement
}
