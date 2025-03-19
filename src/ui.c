/*
** EPITECH PROJECT, 2025
** ui
** File description:
** Functions to handle the UI of my_world
*/

#include "my_world.h"

static void create_button(my_world_t *my_world, char *texture_path,
    sfVector2f position, int action)
{
    button_t *button = malloc(sizeof(button_t));
    sfRectangleShape *rectangle = sfRectangleShape_create();
    sfTexture *texture = sfTexture_createFromFile(texture_path, NULL);

    sfRectangleShape_setTexture(rectangle, texture, sfFalse);
    sfRectangleShape_setTextureRect(rectangle,
        (sfIntRect) {0, 0, 64, 64});
    sfRectangleShape_setSize(rectangle, (sfVector2f) { 64, 64 });
    sfRectangleShape_setPosition(rectangle, position);
    button->x = position.x;
    button->y = position.y;
    button->rectangle = rectangle;
    button->texture = texture;
    button->action = action;
    button->next = my_world->buttons;
    my_world->buttons = button;
}

static sfText *create_text(sfFont *font, sfVector2f position, char *str)
{
    sfText *text = sfText_create();

    sfText_setPosition(text, position);
    sfText_setFont(text, font);
    sfText_setString(text, str);
    return text;
}

void center_radius_text(sfText *radius_text, int x, int y)
{
    sfFloatRect bounds = sfText_getLocalBounds(radius_text);

    sfText_setPosition(radius_text,
        (sfVector2f) {x - (bounds.width / 2.0), y - (bounds.height / 2.0)});
}

static void init_helpbox(my_world_t *my_world)
{
    my_world->helpbox = malloc(sizeof(helpbox_t));
    my_world->helpbox->text = create_text(my_world->font,
        (sfVector2f) {0, 0}, "");
    my_world->helpbox->rectangle = sfRectangleShape_create();
    sfRectangleShape_setFillColor(my_world->helpbox->rectangle,
        (sfColor) {255, 255, 197, 255});
    sfText_setColor(my_world->helpbox->text, sfBlack);
    my_world->helpbox->active = 0;
}

static void init_action_buttons(my_world_t *my_world)
{
    create_button(my_world, "assets/none_button.png",
        (sfVector2f) {10, 10}, ACTION_NONE);
    create_button(my_world, "assets/level_button.png",
        (sfVector2f) {84, 10}, ACTION_LEVEL);
    create_button(my_world, "assets/raise_button.png",
        (sfVector2f) {158, 10}, ACTION_RAISE);
    create_button(my_world, "assets/lower_button.png",
        (sfVector2f) {232, 10}, ACTION_LOWER);
    create_button(my_world, "assets/minus_button.png",
        (sfVector2f) {10, 124}, ACTION_RADIUS_MINUS);
    create_button(my_world, "assets/plus_button.png",
        (sfVector2f) {124, 124}, ACTION_RADIUS_PLUS);
}

void init_ui(my_world_t *my_world)
{
    init_action_buttons(my_world);
    my_world->font = sfFont_createFromFile("assets/Baskic8.otf");
    my_world->radius_info_text = create_text(my_world->font,
        (sfVector2f) {10, 84}, "Current radius:");
    my_world->radius_text = create_text(my_world->font,
        (sfVector2f) {97, 151}, "1");
    init_helpbox(my_world);
    create_button(my_world, "assets/save_button.png",
        (sfVector2f) {10, 198}, ACTION_SAVE);
    create_button(my_world, "assets/load_button.png",
        (sfVector2f) {84, 198}, ACTION_LOAD);
}
