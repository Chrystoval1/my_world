/*
** EPITECH PROJECT, 2025
** help_messages
** File description:
** File to store all help_messages of my_world
*/

#include "my_world.h"

const help_msg_t help_msgs[] = {
    {ACTION_NONE, "Reset your current tool"},
    {ACTION_LEVEL, "Reset the level of the terrain you select"},
    {ACTION_RAISE, "Raise the level of the terrain you select"},
    {ACTION_LOWER, "Lower the level of the terrain you select"},
    {ACTION_RADIUS_MINUS, "Decrease your radius of action"},
    {ACTION_RADIUS_PLUS, "Increase your radius of action"},
    {ACTION_SAVE, "Save the current map in a map.legend file"},
    {ACTION_LOAD, "Load the map in the map.legend file"},
    {0, NULL}
};
