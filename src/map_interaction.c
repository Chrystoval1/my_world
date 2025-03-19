/*
** EPITECH PROJECT, 2025
** map_interaction
** File description:
** Functions to handle the map interactions in my_world
*/

#include "my_world.h"

static void modify_tile_height(my_world_t *my_world,
    int distance, int x, int y)
{
    int tile_height;

    if (distance > my_world->radius)
        return;
    if (x < 0 || x >= my_world->map->length ||
        y < 0 || y >= my_world->map->width)
        return;
    tile_height = my_world->map->map_3d[x][y];
    if (my_world->action == ACTION_LEVEL)
        tile_height = 0;
    if (my_world->action == ACTION_RAISE)
        tile_height += 30;
    if (my_world->action == ACTION_LOWER)
        tile_height -= 30;
    my_world->map->map_3d[x][y] = tile_height;
}

static void modify_surrounding_tiles(my_world_t *my_world, sfVector2i tile_pos)
{
    int x = 0;
    int y = 0;
    float distance = 0.0;

    for (int dx = -my_world->radius; dx <= my_world->radius; dx++) {
        for (int dy = -my_world->radius; dy <= my_world->radius; dy++) {
            distance = sqrtf(dx * dx + dy * dy);
            x = tile_pos.x + dx;
            y = tile_pos.y + dy;
            modify_tile_height(my_world, distance, x, y);
        }
    }
}

static sfVector2i check_tile_distance(map_t *map, sfVector2f click_pos, int i)
{
    sfVector2i tile_pos;
    float dx = 0;
    float dy = 0;
    float distance = 0;

    tile_pos.x = -1;
    tile_pos.y = -1;
    for (int j = map->width - 1; j >= 0; j--) {
        dx = click_pos.x - map->map_2d[i][j].x;
        dy = click_pos.y - map->map_2d[i][j].y;
        distance = sqrtf(dx * dx + dy * dy);
        if (distance < TILE_SIZE * map->zoom) {
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

    for (int i = map->length - 1; i >= 0; i--) {
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
        modify_surrounding_tiles(my_world, tile_pos);
}
