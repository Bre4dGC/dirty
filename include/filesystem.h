#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>

typedef enum {
    FS_MOD_NONE    = 0,
    FS_MOD_READ    = 1,
    FS_MOD_WRITE   = 2,
    FS_MOD_EXECUTE = 4,
    FS_MOD_ALL     = 7
} fs_mod_t;

typedef struct {
    char *name;
    bool is_dir;
    struct stat info;
} fs_item_t;

typedef struct {
    fs_item_t *items;
    char *path;
    uint8_t count;
    uint16_t offset;
    uint16_t selected;
} fs_dir_t;

int fs_open(const char *path, const bool is_dir);
int fs_create(const char *path, const char *name, const bool is_dir);
int fs_rename(const char *old, const char *new);
int fs_move(const char *path, const char *dest);
int fs_chmod(const char *path, const fs_mod_t perm);
int fs_remove(const char *path);
