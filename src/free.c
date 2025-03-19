/*
** EPITECH PROJECT, 2025
** free
** File description:
** Functions to free the memory of my_world
*/

#include "my_world.h"

static void free_buttons(button_t *buttons)
{
    button_t *elem = buttons;
    button_t *next_tmp;

    while (elem != NULL) {
        next_tmp = elem->next;
        sfTexture_destroy(elem->texture);
        sfRectangleShape_destroy(elem->rectangle);
        free(elem);
        elem = next_tmp;
    }
}

void free_3d_map(map_t *map)
{
    for (int i = 0; i < map->length; i++)
        free(map->map_3d[i]);
    free(map->map_3d);
}

void free_2d_map(map_t *map)
{
    for (int i = 0; i < map->length; i++)
        free(map->map_2d[i]);
    free(map->map_2d);
}

static void free_ui(my_world_t *my_world)
{
    sfFont_destroy(my_world->font);
    sfText_destroy(my_world->radius_info_text);
    sfText_destroy(my_world->radius_text);
    sfText_destroy(my_world->helpbox->text);
    sfRectangleShape_destroy(my_world->helpbox->rectangle);
    free(my_world->helpbox);
}

int free_my_world(my_world_t *my_world)
{
    sfRenderWindow_destroy(my_world->window);
    free_buttons(my_world->buttons);
    free_3d_map(my_world->map);
    free_2d_map(my_world->map);
    free(my_world->map);
    sfTexture_destroy(my_world->background_texture);
    sfSprite_destroy(my_world->background);
    free_ui(my_world);
    sfMusic_destroy(my_world->soundtrack);
    free(my_world);
    return 0;
}
