#pragma once

#include <stdbool.h>
#include <stdint.h>

#define CLIPBOARD_LIMIT 5

typedef struct {
    char *path;
    char *name;
    bool is_cut;
} cb_item_t;

typedef struct {
    cb_item_t items[CLIPBOARD_LIMIT];
    uint8_t count;
    uint16_t offset;
    uint16_t selected;
} clipboard_t;

int cb_copy(const char *path);
int cb_cut(const char *path);
int cb_paste(const char *path, const uint8_t index);