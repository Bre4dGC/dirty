#include <curses.h>
#include "dir_ops.h"
#include "file_ops.h"

int scr_height, scr_width;
int winfo_width, winfo_height;
int wmain_height, wmain_width;

WINDOW *directory_win, *content_win, *info_win, *processes_win, *clipboard_win, *commandline_win;

void get_screen_size();
void init_windows();
void display_directory();
void display_info();
void display_processes();
void display_clipboard();
void cleanup_windows();