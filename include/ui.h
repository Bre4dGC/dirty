#ifndef UI_H
#define UI_H

#include <PDcurses/curses.h>
#include <locale.h>
#include "file_ops.h"
#include "clipboard.h"
#include <windows.h>

void render_ui();
void draw_border(WINDOW *win);
void render_dir(Directory dir, int x);
void render_info(WINDOW *info_panel, FileEntry file);
void render_clipboard(WINDOW *clipboard_panel, Clipboard *clipboard);
void handle_input(AppState *state, int ch);
void switch_pane(AppState *state, int pane);
void move_selection(Directory *pane, int direction);

#endif