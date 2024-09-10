#include "raycasting.h"

/**
 * move_forward - Moves the camera forward.
 * @camera: Pointer to the camera struct.
 * @map: 2D map of the game world.
 * @move_speed: Speed of camera movement.
 */
void move_forward(Camera *camera, int map[MAP_HEIGHT][MAP_WIDTH], double move_speed)
{
    if (map[(int)(camera->pos_x + camera->dir_x * move_speed)][(int)camera->pos_y] == 0)
        camera->pos_x += camera->dir_x * move_speed;
    if (map[(int)camera->pos_x][(int)(camera->pos_y + camera->dir_y * move_speed)] == 0)
        camera->pos_y += camera->dir_y * move_speed;
}

/**
 * move_backward - Moves the camera backward.
 * @camera: Pointer to the camera struct.
 * @map: 2D map of the game world.
 * @move_speed: Speed of camera movement.
 */
void move_backward(Camera *camera, int map[MAP_HEIGHT][MAP_WIDTH], double move_speed)
{
    if (map[(int)(camera->pos_x - camera->dir_x * move_speed)][(int)camera->pos_y] == 0)
        camera->pos_x -= camera->dir_x * move_speed;
    if (map[(int)camera->pos_x][(int)(camera->pos_y - camera->dir_y * move_speed)] == 0)
        camera->pos_y -= camera->dir_y * move_speed;
}

/**
 * rotate_left - Rotates the camera to the left.
 * @camera: Pointer to the camera struct.
 * @rot_speed: Speed of camera rotation.
 */
void rotate_left(Camera *camera, double rot_speed)
{
    double old_dir_x = camera->dir_x;
    camera->dir_x = camera->dir_x * cos(-rot_speed) - camera->dir_y * sin(-rot_speed);
    camera->dir_y = old_dir_x * sin(-rot_speed) + camera->dir_y * cos(-rot_speed);

    double old_plane_x = camera->plane_x;
    camera->plane_x = camera->plane_x * cos(-rot_speed) - camera->plane_y * sin(-rot_speed);
    camera->plane_y = old_plane_x * sin(-rot_speed) + camera->plane_y * cos(-rot_speed);
}

/**
 * rotate_right - Rotates the camera to the right.
 * @camera: Pointer to the camera struct.
 * @rot_speed: Speed of camera rotation.
 */
void rotate_right(Camera *camera, double rot_speed)
{
    double old_dir_x = camera->dir_x;
    camera->dir_x = camera->dir_x * cos(rot_speed) - camera->dir_y * sin(rot_speed);
    camera->dir_y = old_dir_x * sin(rot_speed) + camera->dir_y * cos(rot_speed);

    double old_plane_x = camera->plane_x;
    camera->plane_x = camera->plane_x * cos(rot_speed) - camera->plane_y * sin(rot_speed);
    camera->plane_y = old_plane_x * sin(rot_speed) + camera->plane_y * cos(rot_speed);
}
