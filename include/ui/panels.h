#ifndef PANELS_H
#define PANELS_H

#include <PDCurses/curses.h>
#include <time.h>
#include "operations/dir_ops.h"
#include "operations/file_ops.h"
#include "operations/clipboard.h"
#include "operations/processes.h"

extern int scr_height, scr_width;
extern int winfo_width, winfo_height;
extern int wmain_height, wmain_width;

extern WINDOW *directory_win, *content_win, *info_win, *processes_win, *clipboard_win, *commandline_win;

void get_screen_size();
void init_windows();
void display_directory(WINDOW *win, dir_t *content, int scroll_offset);
void display_content(WINDOW *win, dir_t *content, int scroll_offset);
void display_info(item_t *item);
void display_processes(process_t *processes);
void display_clipboard(clipboard_t *clipboard);
void display_command_line(const char *command);
void cleanup_windows();

#endif // PANELS_H