#pragma once

#include <ncurses.h>
#include <stdint.h>

#include "./item.h"
#include "./clipboard.h"

typedef struct
{
        WINDOW *window;
        uint16_t height;
        uint16_t width;
} ui_window_t;

static int scr_width, scr_height;
static ui_window_t catalog_window, content_window, info_window, clipboard_window, commandline_window;

int ui_init();
void ui_cleanup();
int ui_handle_input(const char *input);
// int ui_display_error(const char *error_message);
// int ui_display_items(const item_t *items, uint8_t count);
// int ui_display_info(const item_t *item);
// int ui_display_clipboard(const clipboard_t *clipboard);