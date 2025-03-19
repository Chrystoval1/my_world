/*
** EPITECH PROJECT, 2025
** map
** File description:
** Functions to create and handle the map of my_world
*/

#include "my_world.h"

map_t *create_3d_map(int width, int length)
{
    map_t *map = malloc(sizeof(map_t));

    map->width = width;
    map->length = length;
    map->zoom = 1;
    map->map_3d = malloc(sizeof(int *) * length);
    for (int i = 0; i < length; i++) {
        map->map_3d[i] = malloc(sizeof(int) * width);
        for (int j = 0; j < width; j++) {
            map->map_3d[i][j] = 0;
        }
    }
    return map;
}

static sfVector2f project_iso_point(sfVector3f point_3d,
    int center_x, int center_y, float zoom)
{
    sfVector2f point;
    float angle_x = ANGLE_X * M_PI / 180.0;
    float angle_y = ANGLE_Y * M_PI / 180.0;
    float delta_x = (point_3d.x - center_x) * zoom;
    float delta_y = (point_3d.y - center_y) * zoom;

    point.x = cos(angle_x) * delta_x - cos(angle_x) * delta_y;
    point.y = sin(angle_y) * delta_y +
        sin(angle_y) * delta_x - point_3d.z * zoom;
    return point;
}

sfVector2f **create_2d_map(map_t *map, int horizontal, int vertical)
{
    sfVector2f **map_2d = malloc(sizeof(sfVector2f *) * map->length);
    int center_x = ((map->length - 1) * TILE_SIZE) / 2;
    int center_y = ((map->width - 1) * TILE_SIZE) / 2;

    for (int i = 0; i < map->length; i++) {
        map_2d[i] = malloc(sizeof(sfVector2f) * map->width);
        for (int j = 0; j < map->width; j++) {
            map_2d[i][j] = project_iso_point(
                (sfVector3f) {i * TILE_SIZE, j * TILE_SIZE, map->map_3d[i][j]},
                center_x, center_y, map->zoom);
            map_2d[i][j].x += (1920 / 2) + horizontal;
            map_2d[i][j].y += (1080 / 2) + vertical;
        }
    }
    return map_2d;
}
