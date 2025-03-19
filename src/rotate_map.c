/*
** EPITECH PROJECT, 2025
** rotate_map
** File description:
** Functions to rotate the map of my_world
*/

#include "my_world.h"

static void fill_point(my_world_t *my_world, int **rotated,
    int i, int clockwise)
{
    for (int j = 0; j < my_world->map->width; j++) {
        if (clockwise) {
            rotated[j][my_world->map->length - i - 1] =
                my_world->map->map_3d[i][j];
            continue;
        }
        rotated[my_world->map->width - j - 1][i] = my_world->map->map_3d[i][j];
    }
}

void rotate_map(my_world_t *my_world, int clockwise)
{
    int width = my_world->map->width;
    int length = my_world->map->length;
    int **rotated = malloc(sizeof(int *) * width);

    for (int i = 0; i < width; i++)
        rotated[i] = malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++)
        fill_point(my_world, rotated, i, clockwise);
    free_3d_map(my_world->map);
    free_2d_map(my_world->map);
    my_world->map->width = length;
    my_world->map->length = width;
    my_world->map->map_3d = rotated;
    my_world->map->map_2d = create_2d_map(my_world->map, 0, 0);
}
