/*
** EPITECH PROJECT, 2025
** save
** File description:
** Functions to save the map of my_world into a file
*/

#include "my_world.h"

static void write_point_date(my_world_t *my_world, int i, int j, FILE *file)
{
    char *buffer = malloc(sizeof(char) * 10);

    if (j > 0)
        fwrite(",", sizeof(char), 1, file);
    sprintf(buffer, "%i", my_world->map->map_3d[i][j]);
    fwrite(buffer, sizeof(char), strlen(buffer), file);
    free(buffer);
}

void save_map(my_world_t *my_world)
{
    FILE *file = fopen("map.legend", "w+");
    char *buffer = malloc(sizeof(char) * 10);

    sprintf(buffer, "%i %i\n", my_world->map->width, my_world->map->length);
    fwrite(buffer, sizeof(char), strlen(buffer), file);
    free(buffer);
    for (int i = 0; i < my_world->map->length; i++) {
        for (int j = 0; j < my_world->map->width; j++) {
            write_point_date(my_world, i, j, file);
        }
        fwrite("\n", sizeof(char), 1, file);
    }
    fclose(file);
}

static void read_map_file(my_world_t *my_world, FILE *file)
{
    char *line = NULL;
    size_t size = 0;
    char *point;

    for (int i = 0; i < my_world->map->length; i++) {
        if (getline(&line, &size, file) == -1)
            break;
        point = strtok(line, ",");
        for (int j = 0; j < my_world->map->width && point != NULL; j++) {
            my_world->map->map_3d[i][j] = atoi(point);
            point = strtok(NULL, ",");
        }
    }
    free(line);
}

void load_map(my_world_t *my_world)
{
    FILE *file = fopen("map.legend", "r");
    int width;
    int length;
    float zoom;

    if (file == NULL)
        return;
    if (fscanf(file, "%i %i\n", &width, &length) != 2) {
        fclose(file);
        return;
    }
    zoom = my_world->map->zoom;
    free_3d_map(my_world->map);
    free_2d_map(my_world->map);
    free(my_world->map);
    my_world->map = create_3d_map(width, length);
    my_world->map->zoom = zoom;
    read_map_file(my_world, file);
    my_world->map->map_2d = create_2d_map(my_world->map, 0, 0);
    fclose(file);
}
