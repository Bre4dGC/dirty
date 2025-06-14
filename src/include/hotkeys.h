#pragma once

#include "./commands.h"

typedef struct
{
        char *key_combination;
        command_t command;
} hotkey_t;

int hotkey_execute(const hotkey_t hotkey);