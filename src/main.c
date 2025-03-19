/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** A tiny software where we can modify a world in an isometric view
*/

#include "my_world.h"
#include <stdlib.h>

static void init_music(my_world_t *my_world)
{
    my_world->soundtrack = sfMusic_createFromFile("./assets/soundtrack.ogg");
    sfMusic_setLoop(my_world->soundtrack, sfTrue);
    sfMusic_play(my_world->soundtrack);
}

static void init_background(my_world_t *my_world)
{
    my_world->background_texture =
        sfTexture_createFromFile("./assets/background.png", NULL);
    my_world->background = sfSprite_create();
    sfSprite_setTexture(my_world->background,
        my_world->background_texture, sfTrue);
}

int check_num(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!(str[i] <= '9' && str[i] >= '0'))
            return 1;
    if (str[0] == '\0')
        return 1;
    return 0;
}

int verify_main_args(int ac, char **av, my_world_t *my_world)
{
    if (ac != 3 || av[1] == NULL || av[2] == NULL ||
        check_num(av[1]) || check_num(av[2]) || strcmp("-h", av[1]) == 0 ||
        strcmp("--help", av[1]) == 0 || atoi(av[1]) < 2 || atoi(av[2]) < 2) {
        printf(UNDERLINE"How to use:\n\n"RESET);
        printf("./my_world [width] [length]\n");
        printf("The minimal size of the map is 2 by 2\n\n");
        printf(BOLD"[MOUSEPAD]"RESET" ---> to move around the map\n");
        printf(BOLD"[A][E]"RESET" ---> to zoom in and out\n");
        printf(BOLD"[Q][D]"RESET" ---> to rotate in space the map\n");
        printf(BOLD"[MOUSE LEFT]"RESET
            " ---> to interact with buttons and the map\n\n");
        printf("If you are wondering what the button do, hover them\n");
        free(my_world);
        exit(84);
    }
    return 0;
}

static my_world_t *init_my_world(int horizontal, int vertical, int ac,
    char **av)
{
    my_world_t *my_world = malloc(sizeof(my_world_t));
    sfVideoMode video_mode;

    verify_main_args(ac, av, my_world);
    video_mode.width = 1920;
    video_mode.height = 1080;
    video_mode.bitsPerPixel = 32;
    my_world->window = sfRenderWindow_create(video_mode,
        "MY_WORLD", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(my_world->window, 60);
    my_world->buttons = NULL;
    my_world->action = ACTION_NONE;
    my_world->radius = 1;
    my_world->map = create_3d_map(atoi(av[1]), atoi(av[2]));
    my_world->map->map_2d = create_2d_map(my_world->map, horizontal, vertical);
    init_background(my_world);
    init_music(my_world);
    return my_world;
}

static void handle_key_inputs(sfEvent event, my_world_t *my_world)
{
    if (event.key.code == sfKeyEscape)
        sfRenderWindow_close(my_world->window);
    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyQ)
            rotate_map(my_world, 0);
        if (event.key.code == sfKeyD)
            rotate_map(my_world, 1);
        if (event.key.code == sfKeyA)
            my_world->map->zoom /= 1.1;
        if (event.key.code == sfKeyE)
            my_world->map->zoom *= 1.1;
    }
}

void handle_pad_events(sfEvent event, int *horizontal, int *vertical)
{
    if (event.type == sfEvtMouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sfMouseVerticalWheel &&
            event.mouseWheelScroll.delta != 0)
            *vertical += event.mouseWheelScroll.delta > 0 ? 10 : -10;
        if (event.mouseWheelScroll.wheel == sfMouseHorizontalWheel &&
            event.mouseWheelScroll.delta != 0)
            *horizontal += event.mouseWheelScroll.delta > 0 ? 10 : -10;
    }
}

static void handle_events(my_world_t *my_world, int *horizontal, int *vertical)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(my_world->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(my_world->window);
        if (event.type == sfEvtKeyPressed)
            handle_key_inputs(event, my_world);
        handle_pad_events(event, horizontal, vertical);
        handle_map_click(my_world, event);
        handle_ui_interaction(my_world, event);
    }
}

int main(int ac, char **av)
{
    int horizontal = 0;
    int vertical = 0;
    my_world_t *my_world = init_my_world(horizontal, vertical, ac, av);

    init_ui(my_world);
    while (sfRenderWindow_isOpen(my_world->window)) {
        sfRenderWindow_clear(my_world->window, sfBlue);
        sfRenderWindow_drawSprite(my_world->window,
            my_world->background, NULL);
        draw_2d_map(my_world);
        draw_borders(my_world);
        draw_ui(my_world);
        sfRenderWindow_display(my_world->window);
        handle_events(my_world, &horizontal, &vertical);
        free_2d_map(my_world->map);
        my_world->map->map_2d = create_2d_map(my_world->map,
            horizontal, vertical);
    }
    return free_my_world(my_world);
}
