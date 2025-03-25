#ifndef INPUT_H
#define INPUT_H

#include <PDCurses/curses.h>
#include "operations/dir_ops.h"

// Текущая активная панель
typedef enum {
    PANEL_DIRECTORY,
    PANEL_CONTENT,
    PANEL_COMMAND
} panel_type_t;

extern panel_type_t active_panel;

// Текущие директории
extern dir_t *current_dir;
extern dir_t *content_dir;

void navigate(int key);
void process_command(const char *command);

#endif // INPUT_H
