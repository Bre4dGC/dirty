#pragma once

#include "filesystem.h"
#include "clipboard.h"

typedef enum {
    CMD_OPEN,
    CMD_MOVE,
    CMD_RENAME,
    CMD_REMOVE,
    CMD_CREATE,
    CMD_CHMOD,
    CMD_COPY,
    CMD_CUT,
} cmd_type_t;

typedef int (*cmd_execute_t)(int argc, char **argv);

cmd_execute_t cmd_executors[] = {
    [CMD_OPEN]   = fs_open,
    [CMD_MOVE]   = fs_move,
    [CMD_RENAME] = fs_move,
    [CMD_REMOVE] = fs_remove,
    [CMD_CREATE] = fs_create,
    [CMD_CHMOD]  = fs_chmod,
    [CMD_COPY]   = cb_copy,
    [CMD_CUT]    = cb_cut,
};

typedef struct {
    char *name;
    char *description;
    char *options;
} command_t;

int cmd_execute(const command_t cmd);
