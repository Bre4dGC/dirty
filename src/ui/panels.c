#include "ui/panels.h"

/* Define the variables declared as extern in the header */
int scr_height, scr_width;
int winfo_width, winfo_height;
int wmain_height, wmain_width;
WINDOW *directory_win, *content_win, *info_win, *processes_win, *clipboard_win, *commandline_win;

void get_screen_size()
{
    getmaxyx(stdscr, scr_height, scr_width);
}

void init_windows()
{
    get_screen_size();
    
    winfo_width = scr_width / 4;
    winfo_height = scr_height / 3;
    
    wmain_height = scr_height - 2;
    wmain_width = (scr_width - winfo_width) / 2;

    // Создаем окна с правильными размерами
    directory_win   = newwin(wmain_height, wmain_width, 0, 0);
    content_win     = newwin(wmain_height, wmain_width, 0, wmain_width);
    commandline_win = newwin(2, scr_width - winfo_width, wmain_height, 0);
    info_win        = newwin(winfo_height, winfo_width, 0, scr_width - winfo_width);
    processes_win   = newwin(winfo_height, winfo_width, winfo_height, scr_width - winfo_width);
    clipboard_win   = newwin(winfo_height, winfo_width, winfo_height * 2, scr_width - winfo_width);
    
    // Инициализируем цвета, если поддерживаются
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);    // Для заголовков
        init_pair(2, COLOR_BLACK, COLOR_WHITE);   // Для выделенных элементов
        init_pair(3, COLOR_WHITE, COLOR_BLACK);   // Для обычного текста
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);  // Для директорий
        init_pair(5, COLOR_GREEN, COLOR_BLACK);   // Для файлов
    }
}

void display_directory(WINDOW *win, dir_t *content, int scroll_offset) {
    wclear(win);
    box(win, 0, 0);

    int max_y, max_x;
    getmaxyx(win, max_y, max_x);
    (void)max_x; // Suppress unused variable warning
    
    // Отображаем заголовок окна с путем текущей директории
    mvwprintw(win, 0, 2, "| %s |", content->path);

    for (int i = 0; i < content->count && i < max_y - 2; i++) {
        int index = i + scroll_offset;
        if (index >= content->count) break;
        
        // Добавляем префикс для обозначения типа элемента
        char prefix = is_directory(&content->items[index]) ? '/' : '.';
        
        // Выделяем текущий элемент
        if (i == content->scroll_offset) {
            wattron(win, A_REVERSE);
            mvwprintw(win, i + 1, 1, "[%c] %s", prefix, 
                is_directory(&content->items[index]) ? 
                content->items[index].data.dir->name : 
                content->items[index].data.file->name);
            wattroff(win, A_REVERSE);
        } else {
            mvwprintw(win, i + 1, 1, "[%c] %s", prefix, 
                is_directory(&content->items[index]) ? 
                content->items[index].data.dir->name : 
                content->items[index].data.file->name);
        }
    }

    wrefresh(win);
}

void display_info(item_t *item)
{
    wclear(info_win);
    box(info_win, 0, 0);
    mvwprintw(info_win, 0, winfo_width / 2 - 4, "| Info |");
    
    if (item) {
        int row = 1;
        
        if (item->type == ITEM_TYPE_FILE) {
            mvwprintw(info_win, row++, 1, "type%*s",     winfo_width - 5, "file");
            mvwprintw(info_win, row++, 1, "name%*s",     winfo_width - 5, item->data.file->name);
            mvwprintw(info_win, row++, 1, "size%*ld kb", winfo_width - 5, item->data.file->stat.st_size / 1024);
            mvwprintw(info_win, row++, 1, "created%*s",  winfo_width - 5, ctime(&item->data.file->stat.st_ctime));
            mvwprintw(info_win, row++, 1, "modified%*s", winfo_width - 5, ctime(&item->data.file->stat.st_mtime));
        } else if (item->type == ITEM_TYPE_DIR) {
            mvwprintw(info_win, row++, 1, "type%*s",     winfo_width - 5, "folder");
            mvwprintw(info_win, row++, 1, "name%*s",     winfo_width - 5, item->data.dir->name);
            // Можно добавить больше информации о директории
        }
    }
    
    wrefresh(info_win);
}

void display_processes(process_t *processes)
{
    (void)processes; // Suppress unused parameter warning
    
    wclear(processes_win);
    box(processes_win, 0, 0);
    mvwprintw(processes_win, 0, winfo_width / 2, "| processes |");
    wrefresh(processes_win);
}

void display_clipboard(clipboard_t *clipboard)
{
    wclear(clipboard_win);
    box(clipboard_win, 0, 0);
    mvwprintw(clipboard_win, 0, winfo_width / 2 - 6, "| Clipboard |");

    if (clipboard && clipboard->count > 0) {
        for (int i = 0; i < clipboard->count && i < winfo_height - 2; i++) {
            char prefix = clipboard->files[i].is_cut ? '-' : '+'; // - для вырезанных, + для скопированных
            mvwprintw(clipboard_win, i + 1, 1, "[%c] %s", prefix, clipboard->files[i].name);
        }
    } else {
        mvwprintw(clipboard_win, 1, 1, "Empty clipboard");
    }

    wrefresh(clipboard_win);
}

void display_content(WINDOW *win, dir_t *content, int scroll_offset) {
    wclear(win);
    box(win, 0, 0);

    int max_y, max_x;
    getmaxyx(win, max_y, max_x);
    
    // Отображаем заголовок окна
    mvwprintw(win, 0, 2, "| %s |", content ? content->path : "Empty");

    if (content) {
        for (int i = 0; i < content->count && i < max_y - 2; i++) {
            int index = i + scroll_offset;
            if (index >= content->count) break;
            
            // Добавляем префикс для обозначения типа элемента
            char prefix = is_directory(&content->items[index]) ? '/' : '.';
            
            // Выделяем текущий элемент
            if (i == content->scroll_offset) {
                wattron(win, A_REVERSE);
                mvwprintw(win, i + 1, 1, "[%c] %s", prefix, 
                    is_directory(&content->items[index]) ? 
                    content->items[index].data.dir->name : 
                    content->items[index].data.file->name);
                wattroff(win, A_REVERSE);
            } else {
                mvwprintw(win, i + 1, 1, "[%c] %s", prefix, 
                    is_directory(&content->items[index]) ? 
                    content->items[index].data.dir->name : 
                    content->items[index].data.file->name);
            }
        }
    }

    wrefresh(win);
}

void display_command_line(const char *command) {
    wclear(commandline_win);
    box(commandline_win, 0, 0);
    
    if (command && strlen(command) > 0) {
        mvwprintw(commandline_win, 0, 1, ":");
        mvwprintw(commandline_win, 0, 2, "%s", command);
    } else {
        mvwprintw(commandline_win, 0, 1, "Press : to enter command mode");
    }
    
    wrefresh(commandline_win);
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