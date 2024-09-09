#include <SDL2/SDL.h>
#include "raycasting.h"

#define TURN_SPEED 0.005

void handleMouseMotion(double *playerAngle) {
    int mouseX, mouseY;
    SDL_GetRelativeMouseState(&mouseX, &mouseY);

    *playerAngle -= mouseX * TURN_SPEED; // Adjust the angle based on mouse movement

    // Optionally constrain the angle to avoid wrapping around
    if (*playerAngle < 0) *playerAngle += 2 * M_PI;
    if (*playerAngle >= 2 * M_PI) *playerAngle -= 2 * M_PI;
}
