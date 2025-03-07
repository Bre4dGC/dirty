#include <PDcurses/curses.h>

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    
    printw("dotFile is loaded. Press any key...");
    refresh();
    
    getch();
    endwin();
    return 0;
}