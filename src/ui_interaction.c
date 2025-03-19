/*
** EPITECH PROJECT, 2025
** ui_interaction
** File description:
** Functions to handle the ui interactions in my_world
*/

#include "my_world.h"

static void reset_ui_state(my_world_t *my_world)
{
    button_t *button = my_world->buttons;

    while (button != NULL) {
        sfRectangleShape_setTextureRect(button->rectangle,
            (sfIntRect) {0, 0, 64, 64});
        button = button->next;
    }
}

static int update_misc_button(my_world_t *my_world, button_t *button)
{
    if (button->action != ACTION_RADIUS_MINUS &&
        button->action != ACTION_RADIUS_PLUS &&
        button->action != ACTION_SAVE && button->action != ACTION_LOAD)
        return 0;
    if (button->action == ACTION_RADIUS_MINUS)
        my_world->radius = (my_world->radius > 0) ? my_world->radius - 1 : 0;
    if (button->action == ACTION_RADIUS_PLUS)
        my_world->radius += 1;
    if (button->action == ACTION_SAVE)
        save_map(my_world);
    if (button->action == ACTION_LOAD)
        load_map(my_world);
    return 1;
}

static char *get_help_message(button_t *button)
{
    for (int i = 0; help_msgs[i].action != 0; i++) {
        if (help_msgs[i].action == button->action)
            return help_msgs[i].message;
    }
    return NULL;
}

static void update_helpbox(my_world_t *my_world, int state, button_t *button)
{
    sfFloatRect bounds;
    char *help_message;

    if (button == NULL || (state != 1 && state != 2)) {
        my_world->helpbox->active = 0;
        return;
    }
    help_message = get_help_message(button);
    if (help_message == NULL)
        return;
    sfText_setString(my_world->helpbox->text, help_message);
    bounds = sfText_getLocalBounds(my_world->helpbox->text);
    sfRectangleShape_setSize(my_world->helpbox->rectangle,
        (sfVector2f) {bounds.width + 20, bounds.height + 20});
    my_world->helpbox->active = 1;
}

static void update_button_state(my_world_t *my_world,
    sfVector2f mouse_position, int state)
{
    button_t *button = my_world->buttons;
    sfFloatRect bounds;

    if (state == 0)
        return;
    while (button != NULL) {
        bounds = sfRectangleShape_getGlobalBounds(button->rectangle);
        if (sfFloatRect_contains(&bounds,
            mouse_position.x, mouse_position.y) == sfTrue) {
            sfRectangleShape_setTextureRect(button->rectangle,
                (sfIntRect) {state * 64, 0, 64, 64});
            break;
        }
        button = button->next;
    }
    update_helpbox(my_world, state, button);
    if (button != NULL && state == 2 &&
        !update_misc_button(my_world, button))
        my_world->action = button->action;
}

void handle_ui_interaction(my_world_t *my_world, sfEvent event)
{
    sfVector2f mouse_position;
    int state = 0;

    reset_ui_state(my_world);
    if (event.type == sfEvtMouseMoved) {
        mouse_position = sfRenderWindow_mapPixelToCoords(my_world->window,
            (sfVector2i) { event.mouseMove.x, event.mouseMove.y },
            sfRenderWindow_getView(my_world->window));
        state = 1;
    }
    if (event.type == sfEvtMouseButtonPressed ||
        event.type == sfEvtMouseButtonReleased) {
        mouse_position = sfRenderWindow_mapPixelToCoords(my_world->window,
            (sfVector2i) { event.mouseButton.x, event.mouseButton.y },
            sfRenderWindow_getView(my_world->window));
        state = 2;
        if (event.type == sfEvtMouseButtonReleased)
            state = 1;
    }
    update_button_state(my_world, mouse_position, state);
}
