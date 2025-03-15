#include <curses.h>
#include "input.h"
#include "dir_ops.h"

cursor_t cursor = {0, NULL, NULL};

void navigate(int action)
{
    switch (action)
    {
        case KEY_UP:
            move_up();
            break;
        case KEY_DOWN:
            move_down();
            break;
        case KEY_LEFT:
            move_left();
            break;
        case KEY_RIGHT:
            move_right();
             break;
        case KEY_ENTER:
            // enter_dir();
            break;
        case KEY_BACKSPACE:
            // leave_dir();
            break;
    }
}

void move_up()
{
    if(cursor.y_pos > 0) {
        cursor.y_pos--;
    }
    // return list_dir[catalog_cursor.y_pos];
}

void move_down()
{
    if(cursor.y_pos > 0) {
        cursor.y_pos++;
    }
}

void move_left()
{
    // Move the cursor left
}

void move_right()
{
    // Move the cursor right
}