#pragma once

#include <stdint.h>

#include "filesystem.h"
#include "clipboard.h"
#include "commands.h"

typedef enum {
    CONTENT_TYPE_DIRECTORY,
    CONTENT_TYPE_FILE,
    CONTENT_TYPE_IMAGE,
} ui_content_type;

int ui_init(void);
int ui_run(void);
int ui_update(void);
int ui_draw(void);
int ui_handle_input(void);
int ui_cleanup(void);
