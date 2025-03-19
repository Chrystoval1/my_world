/*
** EPITECH PROJECT, 2025
** myworld_bs
** File description:
** myworld_bs
*/

#include "my_world.h"

static sfVertexArray *create_tile(tile_t *tiles)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1 = {.position = *tiles->point1, .color = sfWhite,
        .texCoords = {0, 0}};
    sfVertex vertex2 = {.position = *tiles->point2, .color = sfWhite,
        .texCoords = {224, 0}};
    sfVertex vertex3 = {.position = *tiles->point3, .color = sfWhite,
        .texCoords = {224, 224}};
    sfVertex vertex4 = {.position = *tiles->point4, .color = sfWhite,
        .texCoords = {0, 224}};

    sfVertexArray_setPrimitiveType(vertex_array, sfQuads);
    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_append(vertex_array, vertex3);
    sfVertexArray_append(vertex_array, vertex4);
    return vertex_array;
}

static sfVertexArray *create_line(sfVector2f *point1, sfVector2f *point2)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1 = {.position = *point1, .color = sfBlack};
    sfVertex vertex2 = {.position = *point2, .color = sfBlack};

    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_setPrimitiveType(vertex_array, sfLinesStrip);
    return vertex_array;
}

static void assign_position_values(tile_t *tiles, my_world_t *my_world,
    int i, int j)
{
    tiles->point1 = &my_world->map->map_2d[i][j];
    tiles->point2 = &my_world->map->map_2d[i][j + 1];
    tiles->point3 = &my_world->map->map_2d[i + 1][j + 1];
    tiles->point4 = &my_world->map->map_2d[i + 1][j];
    tiles->z1 = my_world->map->map_3d[i][j];
    tiles->z2 = my_world->map->map_3d[i][j + 1];
    tiles->z3 = my_world->map->map_3d[i + 1][j + 1];
    tiles->z4 = my_world->map->map_3d[i + 1][j];
}

void determine_texture_to_apply(world_textures_t *world_textures,
    tile_t *tiles)
{
    float z_average = (tiles->z1 + tiles->z2 + tiles->z3 + tiles->z4) / 4.0;

    if (z_average >= 120.0)
        world_textures->state.texture = NULL;
    if (z_average >= 60.0 && z_average < 120.0)
        world_textures->state.texture = world_textures->stone_texture;
    if (z_average >= 0.0 && z_average < 60.0)
        world_textures->state.texture = world_textures->grass_texture;
    if (z_average >= -60.0 && z_average < 0.0)
        world_textures->state.texture = world_textures->sand_texture;
    if (z_average < -60.0)
        world_textures->state.texture = world_textures->water_texture;
}

static void display_vertex_arrays(tile_t *tiles, my_world_t *my_world,
    sfVector2i loop_int, world_textures_t *world_textures)
{
    sfVertexArray *vertex_array;
    sfVertexArray *lines;

    if (loop_int.x < my_world->map->length - 1 &&
        loop_int.y < my_world->map->width - 1) {
        vertex_array = create_tile(tiles);
        determine_texture_to_apply(world_textures, tiles);
        sfRenderWindow_drawVertexArray(my_world->window, vertex_array,
            &world_textures->state);
        lines = create_line(&my_world->map->map_2d[loop_int.x][loop_int.y],
            &my_world->map->map_2d[loop_int.x + 1][loop_int.y]);
        sfRenderWindow_drawVertexArray(my_world->window, lines, NULL);
        sfVertexArray_destroy(lines);
        lines = create_line(&my_world->map->map_2d[loop_int.x][loop_int.y],
            &my_world->map->map_2d[loop_int.x][loop_int.y + 1]);
        sfRenderWindow_drawVertexArray(my_world->window, lines, NULL);
        sfVertexArray_destroy(vertex_array);
        sfVertexArray_destroy(lines);
    }
}

void init_world_textures(world_textures_t *world_textures)
{
    world_textures->state = sfRenderStates_default();
    world_textures->grass_texture =
        sfTexture_createFromFile("assets/grass.png", NULL);
    world_textures->stone_texture =
        sfTexture_createFromFile("assets/stone.png", NULL);
    world_textures->water_texture =
        sfTexture_createFromFile("assets/water.png", NULL);
    world_textures->sand_texture =
        sfTexture_createFromFile("assets/sand.png", NULL);
}

void draw_2d_map(my_world_t *my_world)
{
    tile_t *tiles = malloc(sizeof(tile_t));
    world_textures_t *world_textures = malloc(sizeof(world_textures_t));
    sfVector2i loop_int;

    init_world_textures(world_textures);
    for (int i = 0; i < my_world->map->length - 1; i++) {
        for (int j = 0; j < my_world->map->width - 1; j++) {
            loop_int = (sfVector2i){i, j};
            assign_position_values(tiles, my_world, i, j);
            display_vertex_arrays(tiles, my_world, loop_int, world_textures);
        }
    }
    sfTexture_destroy(world_textures->sand_texture);
    sfTexture_destroy(world_textures->stone_texture);
    sfTexture_destroy(world_textures->grass_texture);
    sfTexture_destroy(world_textures->water_texture);
    free(world_textures);
    free(tiles);
}
