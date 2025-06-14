#include "include/ui.h"
#include "include/logs.h"

int ui_init()
{
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE);
        start_color();

        getmaxyx(stdscr, scr_height, scr_width);

        int winfo_width = scr_width / 5;
        int winfo_height = scr_height / 2;

        int wmain_height = scr_height - 3;
        int wmain_width = (scr_width - winfo_width) / 2;

        // Creating windows
        catalog_window.window = newwin(wmain_height + 1, wmain_width + 1, 0, 0);
        content_window.window = newwin(wmain_height + 1, wmain_width + 1, 0, wmain_width);
        info_window.window = newwin(winfo_height, winfo_width, 0, scr_width - winfo_width);
        clipboard_window.window = newwin(winfo_height, winfo_width, winfo_height, scr_width - winfo_width);
        commandline_window.window = newwin(3, scr_width - winfo_width, wmain_height, 0);

        // Adding borders to the windows
        box(commandline_window.window, 0, 0);
        box(catalog_window.window, 0, 0);
        box(content_window.window, 0, 0);
        box(info_window.window, 0, 0);
        box(clipboard_window.window, 0, 0);

        // Refreshing windows to display borders
        wrefresh(catalog_window.window);
        wrefresh(content_window.window);
        wrefresh(info_window.window);
        wrefresh(clipboard_window.window);
        wrefresh(commandline_window.window);

        while (true)
        {
                /* code */
        }
}

void ui_cleanup()
{
        endwin();
}

int ui_handle_input(const char *input)
{
        // TODO: Implement logic to handle user input (e.g., navigation, clipboard actions)
        return log_status(SUCCESS, "Input handled");
}