/*
** EPITECH PROJECT, 2024
** my_world.h
** File description:
** Header file for the prototypes of all of the functions in my_world
*/

#ifndef MY_WORLD
    #define MY_WORLD
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <math.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #define ANGLE_X 150
    #define ANGLE_Y 35
    #define TILE_SIZE 64

    #define ACTION_NONE 1
    #define ACTION_LEVEL 2
    #define ACTION_RAISE 3
    #define ACTION_LOWER 4

    #define ACTION_RADIUS_MINUS 10
    #define ACTION_RADIUS_PLUS 11

    #define ACTION_SAVE 20
    #define ACTION_LOAD 21

    #define UNDERLINE "\e[4;33m"
    #define BOLD "\e[1;33m"
    #define RESET "\e[0m"

typedef struct tile_s {
    sfVector2f *point1;
    sfVector2f *point2;
    sfVector2f *point3;
    sfVector2f *point4;
    int z1;
    int z2;
    int z3;
    int z4;
} tile_t;

typedef struct world_textures_s {
    sfTexture *grass_texture;
    sfTexture *stone_texture;
    sfTexture *water_texture;
    sfTexture *sand_texture;
    sfRenderStates state;
} world_textures_t;

typedef struct border_vertexes_s {
    sfVertex v1;
    sfVertex v2;
    sfVertex v3;
    sfVertex v4;
} border_vertexes_t;

typedef struct button_s {
    int x;
    int y;
    sfTexture *texture;
    sfRectangleShape *rectangle;
    int action;
    struct button_s *next;
} button_t;

typedef struct map_s {
    int width;
    int length;
    float zoom;
    sfVector2f **map_2d;
    int **map_3d;
} map_t;

typedef struct helpbox_s {
    sfText *text;
    sfRectangleShape* rectangle;
    int active;
} helpbox_t;

typedef struct my_world_s {
    sfRenderWindow *window;
    button_t *buttons;
    sfFont *font;
    sfText *radius_info_text;
    sfText *radius_text;
    helpbox_t *helpbox;
    map_t *map;
    int action;
    int radius;
    sfTexture *background_texture;
    sfSprite *background;
    sfMusic *soundtrack;
} my_world_t;

typedef struct help_msg_s {
    int action;
    char *message;
} help_msg_t;

extern const help_msg_t help_msgs[];

/* MAP */
map_t *create_3d_map(int width, int lenght);
sfVector2f **create_2d_map(map_t *map, int horizontal, int vertical);

/* ROTATE_MAP */
void rotate_map(my_world_t *my_world, int clockwise);

/* DRAW_MAP */
void draw_2d_map(my_world_t *my_world);

/* UI */
void init_ui(my_world_t *my_world);
void center_radius_text(sfText *radius_text, int x, int y);

/* DRAW_UI */
void draw_ui(my_world_t *my_world);

/* UI_INTERACTION */
void handle_ui_interaction(my_world_t *my_world, sfEvent event);

/* DRAW_BORDERS */
void draw_borders(my_world_t *my_world);

/* MAP_INTERACTION */
void handle_map_click(my_world_t *my_world, sfEvent event);

/* SAVE */
void save_map(my_world_t *my_world);
void load_map(my_world_t *my_world);

/* FREE */
void free_3d_map(map_t *map);
void free_2d_map(map_t *map);
int free_my_world(my_world_t *my_world);
#endif
