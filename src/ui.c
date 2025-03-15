#include <curses.h>
#include "ui.h"

void init_ui()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

void cleanup_ui()
{
    endwin();
}