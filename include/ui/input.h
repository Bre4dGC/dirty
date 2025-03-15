#ifndef INPUT_H
#define INPUT_H

#include <curses.h>

typedef struct {
    int y_pos;       // Y position of the cursor
    cursor_t *left;  // Left cursor
    cursor_t *right; // Right cursor
} cursor_t;

void navigate(int action);

#endif // INPUT_H
