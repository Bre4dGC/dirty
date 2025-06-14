#pragma once

#include <stdbool.h>
#include <stdint.h>

#define CLIPBOARD_LIMIT 5

typedef struct
{
        char *path;
        bool is_cut;
} clipboard_item_t;

typedef struct
{
        uint8_t count;
        clipboard_item_t items[CLIPBOARD_LIMIT];
} clipboard_t;

extern clipboard_t clipboard;

static int clipboard_add_item(const char *path, const bool is_cut);
int copy_item(const char *path);
int cut_item(const char *path);
int paste_item(const char *path, const uint8_t index);