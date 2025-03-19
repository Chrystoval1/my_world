/*
** EPITECH PROJECT, 2025
** mouse
** File description:
** Functions to handle the mouse interractions in my_world
*/

#include "my_world.h"

static void check_surrounding(map_t *map, int radius,
    sfVector2i tile_pos, int dx)
{
    int height_change = 30;
    int x = 0;
    int y = 0;
    int new_height = 0;

    for (int dy = -radius; dy <= radius; dy++) {
        x = tile_pos.x + dx;
        y = tile_pos.y + dy;
        if (x >= 0 && x < map->length && y >= 0 && y < map->width) {
            new_height = map->map_3d[x][y] + height_change;
            map->map_3d[x][y] = (new_height > 0) ? new_height : 0;
        }
    }
}

static void modify_surrounding_tiles(map_t *map, sfVector2i tile_pos)
{
    int radius = 1;

    for (int dx = -radius; dx <= radius; dx++)
        check_surrounding(map, radius, tile_pos, dx);
}

static sfVector2i check_tile_distance(map_t *map, sfVector2f click_pos, int i)
{
    sfVector2i tile_pos;
    float dx = 0;
    float dy = 0;
    float distance = 0;

    tile_pos.x = -1;
    tile_pos.y = -1;
    for (int j = 0; j < map->width; j++) {
        dx = click_pos.x - map->map_2d[i][j].x;
        dy = click_pos.y - map->map_2d[i][j].y;
        distance = sqrtf(dx * dx + dy * dy);
        if (distance < TILE_SIZE) {
            tile_pos.x = i;
            tile_pos.y = j;
            break;
        }
    }
    return tile_pos;
}

static sfVector2i get_clicked_tile(map_t *map, sfVector2f click_pos)
{
    sfVector2i tile_pos;

    for (int i = 0; i < map->length; i++) {
        tile_pos = check_tile_distance(map, click_pos, i);
        if (tile_pos.x != -1)
            break;
    }
    return tile_pos;
}

void handle_map_click(my_world_t *my_world, sfEvent event)
{
    sfVector2f map_coords;
    sfVector2i tile_pos;

    if (event.type != sfEvtMouseButtonPressed)
        return;
    map_coords = sfRenderWindow_mapPixelToCoords(my_world->window,
        (sfVector2i) { event.mouseButton.x, event.mouseButton.y },
        sfRenderWindow_getView(my_world->window));
    tile_pos = get_clicked_tile(my_world->map, map_coords);
    if (tile_pos.x != -1 && tile_pos.y != -1)
        modify_surrounding_tiles(my_world->map, tile_pos);
}
