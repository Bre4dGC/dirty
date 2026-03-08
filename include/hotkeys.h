#pragma once

#include <stdint.h>

#include "commands.h"

#define MAX_HOTKEYS 32

typedef struct {
    char *comb;
    command_t cmd;
} hotkey_t;

typedef struct {
    hotkey_t keys[MAX_HOTKEYS];
    uint8_t count;
} hk_table_t;

int hk_init();
int hk_execute(const hotkey_t hk);
int hk_register(const hotkey_t hk);
int hk_cleanup();
