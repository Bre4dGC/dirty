#include "panels.h"

void get_screen_size()
{
    getmaxyx(stdscr, scr_height, scr_width);
}

void init_windows()
{
    winfo_width = scr_width / 4;
    winfo_height = scr_height / 3;
    
    wmain_height = scr_height - 2;
    wmain_width = scr_width - winfo_width;

    directory_win   = newwin(wmain_height, wmain_width, 0,                0);
    content_win     = newwin(wmain_height, wmain_width, 0,                wmain_width / 2);
    commandline_win = newwin(2,            wmain_width, wmain_height,     0);
    info_win        = newwin(winfo_height, winfo_width, 0,                wmain_width);
    processes_win   = newwin(winfo_height, winfo_width, winfo_height,     wmain_width);
    clipboard_win   = newwin(winfo_height, winfo_width, winfo_height * 2, wmain_width);
}

void display_directory(WINDOW *win, dir_t *content, int scroll_offset) {
    wclear(win);
    box(win, 0, 0);

    int max_y, max_x;
    getmaxyx(win, max_y, max_x);

    for (int i = 0; i < content->count && i < max_y - 2; i++) {
        int index = i + scroll_offset;
        if (index >= content->count) break;

        mvwprintw(win, i + 1, 1, "%s", content->items[index]);
    }

    wrefresh(win);
}

void display_info()
{
    wclear(info_win);
    box(info_win, 0, 0);
    mvwprintw(info_win, 0, winfo_width / 2, "| info |");
    wrefresh(info_win);
}

void display_processes()
{
    wclear(processes_win);
    box(processes_win, 0, 0);
    mvwprintw(processes_win, 0, winfo_width / 2, "| processes |");
    wrefresh(processes_win);
}

void display_clipboard()
{
    wclear(clipboard_win);
    box(clipboard_win, 0, 0);
    mvwprintw(info_win, 0, winfo_width / 2, "| clipboard |");
    wrefresh(info_win);
}

void cleanup_windows()
{
    delwin(directory_win);
    delwin(content_win);
    delwin(info_win);
    delwin(processes_win);
    delwin(clipboard_win);
    delwin(commandline_win);
}