#pragma once

#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./errors.h"

typedef struct
{
        char *name;
        char *path;
        bool is_dir;
        struct stat info;
} item_t;

int create_item(const char *item_path, const char *name, const bool is_dir);
int rename_item(const char *item_path, const char *new_name);
int move_item(const char *item_path, const char *dests_path);
int change_item_permission(const char *item_path, const char *permission);
int remove_item(const char *item_path);