/*
** EPITECH PROJECT, 2025
** draw_borders
** File description:
** Functions to display the borders of my_world
*/

#include "my_world.h"

static void initialise_border_vertex_right(border_vertexes_t *border_vertexes,
    int width, int i, my_world_t *my_world)
{
    border_vertexes->v1 = (sfVertex){.position =
        my_world->map->map_2d[i][width],
        .color = {99, 60, 11, 255}, .texCoords = {0, 0}};
    border_vertexes->v2 = (sfVertex){.position =
        my_world->map->map_2d[i + 1][width], .color = {99, 60, 11, 255},
        .texCoords = {64, 0}};
    border_vertexes->v3 = (sfVertex){.position =
        (sfVector2f){my_world->map->map_2d[i + 1][width].x, 1080},
        .color = {99, 60, 11, 255}, .texCoords = {64, 64}};
    border_vertexes->v4 = (sfVertex){.position =
        (sfVector2f){my_world->map->map_2d[i][width].x, 1080},
        .color = {99, 60, 11, 255}, .texCoords = {0, 64}};
}

static void draw_right_side_border(my_world_t *my_world, int width)
{
    sfVertexArray *array;
    border_vertexes_t *border_vertexes = malloc(sizeof(border_vertexes_t));

    for (int i = 0; i < my_world->map->length - 1; i++) {
        array = sfVertexArray_create();
        initialise_border_vertex_right(border_vertexes, width, i, my_world);
        sfVertexArray_setPrimitiveType(array, sfQuads);
        sfVertexArray_append(array, border_vertexes->v1);
        sfVertexArray_append(array, border_vertexes->v2);
        sfVertexArray_append(array, border_vertexes->v3);
        sfVertexArray_append(array, border_vertexes->v4);
        sfRenderWindow_drawVertexArray(my_world->window, array, NULL);
        sfVertexArray_destroy(array);
    }
    free(border_vertexes);
}

static void initialise_border_vertex_left(border_vertexes_t *border_vertexes,
    int length, int i, my_world_t *my_world)
{
    border_vertexes->v1 = (sfVertex){.position =
        my_world->map->map_2d[length][i],
        .color = {99, 60, 11, 255}, .texCoords = {0, 0}};
    border_vertexes->v2 = (sfVertex){.position =
        my_world->map->map_2d[length][i + 1], .color = {99, 60, 11, 255},
        .texCoords = {64, 0}};
    border_vertexes->v3 = (sfVertex){.position =
        (sfVector2f){my_world->map->map_2d[length][i + 1].x, 1080},
        .color = {99, 60, 11, 255}, .texCoords = {64, 64}};
    border_vertexes->v4 = (sfVertex){.position =
        (sfVector2f){my_world->map->map_2d[length][i].x, 1080},
        .color = {99, 60, 11, 255}, .texCoords = {0, 64}};
}

static void draw_left_side_border(my_world_t *my_world, int length)
{
    sfVertexArray *array;
    border_vertexes_t *border_vertexes = malloc(sizeof(border_vertexes_t));

    for (int i = 0; i < my_world->map->width - 1; i++) {
        array = sfVertexArray_create();
        initialise_border_vertex_left(border_vertexes, length, i, my_world);
        sfVertexArray_setPrimitiveType(array, sfQuads);
        sfVertexArray_append(array, border_vertexes->v1);
        sfVertexArray_append(array, border_vertexes->v2);
        sfVertexArray_append(array, border_vertexes->v3);
        sfVertexArray_append(array, border_vertexes->v4);
        sfRenderWindow_drawVertexArray(my_world->window, array, NULL);
        sfVertexArray_destroy(array);
    }
    free(border_vertexes);
}

void draw_borders(my_world_t *my_world)
{
    int length = my_world->map->length - 1;
    int width = my_world->map->width - 1;
    sfVertexArray *array;
    sfVertex v1;
    sfVertex v2;

    draw_left_side_border(my_world, length);
    draw_right_side_border(my_world, width);
    array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(array, sfLinesStrip);
    v1 = (sfVertex){.position =
        (sfVector2f){my_world->map->map_2d[length][width].x, 1080},
        .color = sfBlack};
    v2 = (sfVertex){.position = my_world->map->map_2d[length][width],
        .color = sfBlack};
    sfVertexArray_append(array, v1);
    sfVertexArray_append(array, v2);
    sfRenderWindow_drawVertexArray(my_world->window, array, NULL);
    sfVertexArray_destroy(array);
}
