#include "raycasting.h"

/**
 * handle_events - Handles SDL events.
 * @event: Pointer to the SDL_Event structure.
 *
 * Return: 0 to exit the program, 1 to continue running.
 */
int handle_events(SDL_Event *event)
{
    if (event->type == SDL_QUIT)
        return (0);
    return (1);
}
