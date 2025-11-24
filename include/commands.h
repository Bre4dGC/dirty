#pragma once

typedef struct {
    char *name;
    char *description;
    char *options;
    int (*execute)(int argc, char **argv);
} command_t;

int cmd_execute(const command_t cmd);