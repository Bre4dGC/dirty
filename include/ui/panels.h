#include <curses.h>

int scr_height, scr_width;
int winfo_width, winfo_height;
int wmain_height, wmain_width;

WINDOW *directory_win, *content_win, *info_win, *processes_win, *clipboard_win, *commandline_win;

void get_screen_size();
void init_windows();
void render_directory();
void render_info();
void render_processes();
void render_clipboard();