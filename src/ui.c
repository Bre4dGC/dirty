#include "ui.h"

int info_width;
int main_width;

void render_ui()
{
    initscr();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    keypad(stdscr, TRUE);

    setlocale(LC_ALL, "");
    SetConsoleOutputCP(CP_UTF8);
    system("chcp 850");

    info_width = COLS / 5;
    main_width = COLS - info_width;

    WINDOW *catalog_panel, *content_panel, *command_line, *info_panel,*clipboard_panel;

    catalog_panel   = newwin(LINES - 1, main_width / 2, 0, 0);
    content_panel   = newwin(LINES - 1, main_width / 2, 0, main_width / 2);
    command_line    = newwin(2, main_width, LINES - 2, 0);
    info_panel      = newwin(LINES / 2, info_width, 0, main_width);
    clipboard_panel = newwin(LINES / 2, info_width, LINES / 2, main_width);

    draw_border(catalog_panel);
    draw_border(content_panel);
    draw_border(command_line);
    draw_border(info_panel);
    draw_border(clipboard_panel);
}

void draw_border(WINDOW *win)
{
    wbkgd(win, COLOR_PAIR(1));
    box(win, 0, 0);
    wrefresh(win);
}

void render_dir(Directory dir, int x)
{
    for (int y = 0; y < dir.elem_count; y++) {
        mvprintw(y, x, "[ %s ] %s", (dir.files[y].type == Folder ? "/" : ".", dir.files[y].name));
        if (y == dir.selected_index) {
            mvchgat(y, x, COLS / 2, A_REVERSE, 0, NULL);
        }
    }
}

void render_info(WINDOW *info_panel, FileEntry file)
{
    char time_buff[20];
    char type[] = file.type == Folder ? TYPE_STRING[Folder] : TYPE_STRING[File];
    char is_cut[] = file.is_cut == true ? "true" : "false";

    mvwprintw(info_panel, 0, 0, "type: %*.*s", info_width - strlen(type), info_width / 2, type);
    mvwprintw(info_panel, 1, 0, "name: %*.*s", info_width - strlen(file.name), info_width / 2, file.name);
    mvwprintw(info_panel, 2, 0, "size: %*.*ld bytes", info_width - strlen(file.info.st_size), info_width / 2, file.info.st_size);
    mvwprintw(info_panel, 3, 0, "is Cut: %*.*s", info_width - strlen(is_cut), info_width / 2, is_cut);
    mvwprintw(info_panel, 4, 0, "created: %ld", info_width - 20, info_width / 2, file.info.st_birthtim);
    mvwprintw(info_panel, 5, 0, "modified: %ld", info_width - 20, info_width / 2, file.info.st_mtim);
    
    wrefresh(info_panel);
}

void render_clipboard(WINDOW *clipboard_panel, Clipboard *clipboard)
{
    for (int y = 0; y < clipboard->elem_count; y++) {
        mvwprintw(clipboard_panel, y, 0, "[%s] %s", 
                  clipboard->files[y].type == Folder ? "/" : ".", 
                  clipboard->files[y].name);
    }
    wrefresh(clipboard_panel);
}

void handle_input(AppState *state, int ch) 
{
    switch (ch) {
        case KEY_UP:
            move_selection(&state->left_pane, -1);
            break;
        case KEY_DOWN:
            move_selection(&state->left_pane, 1);
            break;
        case KEY_LEFT:
            state->active_pane = 0;
            break;
        case KEY_RIGHT:
            state->active_pane = 1;
            break;
        case '\n': // Enter
            if (state->active_pane == false) {
                dir_open(&state->left_pane, state->current_path);
            } else {
                dir_open(&state->right_pane, state->current_path);
            }
            break;
    }
}

void move_selection(Directory *pane, int direction) 
{
    pane->selected_index += direction;
    if (pane->selected_index < 0) {
        pane->selected_index = 0;
    } else if (pane->selected_index >= pane->elem_count) {
        pane->selected_index = pane->elem_count - 1;
    }
}

void switch_pane(AppState *state, int pane)
{
    if (pane == 0) {
        state->active_pane = 0; // Левая панель
    } else if (pane == 1) {
        state->active_pane = 1; // Правая панель
    }

    // Обновление интерфейса
    render_ui();
    render_dir(state->left_pane, 0);
    render_dir(state->right_pane, main_width / 2);
}