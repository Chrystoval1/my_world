/*
** EPITECH PROJECT, 2025
** draw_ui
** File description:
** Functions to display the UI of my_world
*/

#include "my_world.h"

static void draw_buttons(my_world_t *my_world)
{
    button_t *button = my_world->buttons;

    while (button != NULL) {
        if (button->action == my_world->action)
            sfRectangleShape_setTextureRect(button->rectangle,
                (sfIntRect) {192, 0, 64, 64});
        sfRenderWindow_drawRectangleShape(my_world->window,
            button->rectangle, NULL);
        button = button->next;
    }
}

static void draw_helpbox(my_world_t *my_world)
{
    sfVector2i mouse_position;

    if (!my_world->helpbox->active)
        return;
    mouse_position = sfMouse_getPositionRenderWindow(my_world->window);
    sfRectangleShape_setPosition(my_world->helpbox->rectangle,
        (sfVector2f) {mouse_position.x + 10, mouse_position.y + 10});
    sfText_setPosition(my_world->helpbox->text,
        (sfVector2f) {mouse_position.x + 20, mouse_position.y + 20});
    sfRenderWindow_drawRectangleShape(my_world->window,
        my_world->helpbox->rectangle, NULL);
    sfRenderWindow_drawText(my_world->window, my_world->helpbox->text, NULL);
}

void draw_ui(my_world_t *my_world)
{
    char *radius_text = malloc(sizeof(char) * 10);

    draw_buttons(my_world);
    sfRenderWindow_drawText(my_world->window,
        my_world->radius_info_text, NULL);
    sprintf(radius_text, "%i", my_world->radius);
    sfText_setString(my_world->radius_text, radius_text);
    center_radius_text(my_world->radius_text, 97, 151);
    sfRenderWindow_drawText(my_world->window, my_world->radius_text, NULL);
    draw_helpbox(my_world);
    free(radius_text);
}
