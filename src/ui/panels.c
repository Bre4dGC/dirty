#include "panels.h"
#include "file_ops.h"

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

void render_directory()
{
    wclear(directory_win);
    box(directory_win, 0, 0);
    mvwprintw(info_win, 0, wmain_width / 2, "| %s |", "random path");
    wrefresh(info_win);
}

void render_info()
{
    wclear(info_win);
    box(info_win, 0, 0);
    mvwprintw(info_win, 0, winfo_width / 2, "| info |");
    wrefresh(info_win);
}

void render_processes()
{
    wclear(processes_win);
    box(processes_win, 0, 0);
    mvwprintw(processes_win, 0, winfo_width / 2, "| processes |");
    wrefresh(processes_win);
}

void render_clipboard()
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