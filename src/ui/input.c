#include <PDCurses/curses.h>
#include "ui/input.h"
#include "ui/panels.h"
#include "operations/dir_ops.h"

// Текущая активная панель
panel_type_t active_panel = PANEL_DIRECTORY;

// Текущие директории
dir_t *current_dir = NULL;
dir_t *content_dir = NULL;

void navigate(int key) {
    switch (key) {
        case KEY_UP:
            if (active_panel == PANEL_DIRECTORY && current_dir) {
                if (current_dir->scroll_offset > 0)
                    current_dir->scroll_offset--;
                display_directory(directory_win, current_dir, current_dir->scroll_offset);
                
                // Обновляем информацию о выбранном элементе
                item_t *selected_item = &current_dir->items[current_dir->scroll_offset];
                display_info(selected_item);
            } else if (active_panel == PANEL_CONTENT && content_dir) {
                if (content_dir->scroll_offset > 0)
                    content_dir->scroll_offset--;
                display_content(content_win, content_dir, content_dir->scroll_offset);
                
                // Обновляем информацию о выбранном элементе
                item_t *selected_item = &content_dir->items[content_dir->scroll_offset];
                display_info(selected_item);
            }
            break;
            
        case KEY_DOWN:
            if (active_panel == PANEL_DIRECTORY && current_dir) {
                if (current_dir->scroll_offset < current_dir->count - 1)
                    current_dir->scroll_offset++;
                display_directory(directory_win, current_dir, current_dir->scroll_offset);
                
                // Обновляем информацию о выбранном элементе
                item_t *selected_item = &current_dir->items[current_dir->scroll_offset];
                display_info(selected_item);
            } else if (active_panel == PANEL_CONTENT && content_dir) {
                if (content_dir->scroll_offset < content_dir->count - 1)
                    content_dir->scroll_offset++;
                display_content(content_win, content_dir, content_dir->scroll_offset);
                
                // Обновляем информацию о выбранном элементе
                item_t *selected_item = &content_dir->items[content_dir->scroll_offset];
                display_info(selected_item);
            }
            break;
            
        case KEY_LEFT:
            if (active_panel == PANEL_CONTENT) {
                active_panel = PANEL_DIRECTORY;
                // Выделяем активную панель
                wattron(directory_win, A_BOLD);
                box(directory_win, 0, 0);
                wattroff(directory_win, A_BOLD);
                wrefresh(directory_win);
                
                box(content_win, 0, 0);
                wrefresh(content_win);
            }
            break;
            
        case KEY_RIGHT:
            if (active_panel == PANEL_DIRECTORY) {
                active_panel = PANEL_CONTENT;
                // Выделяем активную панель
                wattron(content_win, A_BOLD);
                box(content_win, 0, 0);
                wattroff(content_win, A_BOLD);
                wrefresh(content_win);
                
                box(directory_win, 0, 0);
                wrefresh(directory_win);
            }
            break;
            
        case '\n': // Enter key
            if (active_panel == PANEL_DIRECTORY && current_dir) {
                // Получаем выбранный элемент
                item_t *selected_item = &current_dir->items[current_dir->scroll_offset];
                
                if (is_directory(selected_item) && is_dir(selected_item->data.dir->path)) {
                    // Если это директория, открываем ее
                    enter_dir(selected_item->data.dir);
                    
                    // Обновляем содержимое правой панели
                    if (selected_item->data.dir->count > 0) {
                        content_dir = selected_item->data.dir->items[0].data.dir;
                        display_content(content_win, content_dir, 0);
                    }
                }
            } else if (active_panel == PANEL_CONTENT && content_dir) {
                // Получаем выбранный элемент
                item_t *selected_item = &content_dir->items[content_dir->scroll_offset];
                
                if (is_directory(selected_item) && is_dir(selected_item->data.dir->path)) {
                    // Если это директория, перемещаем текущую директорию в левую панель
                    current_dir = content_dir;
                    display_directory(directory_win, current_dir, 0);
                    
                    // Открываем выбранную директорию в правой панели
                    content_dir = selected_item->data.dir;
                    display_content(content_win, content_dir, 0);
                }
            }
            break;
            
        case ':': // Command mode
            active_panel = PANEL_COMMAND;
            // Очищаем командную строку и ждем ввода
            display_command_line("");
            // Здесь нужно добавить логику для ввода команды
            break;
    }
}

void move_left()
{
    // Move the cursor left
}

void move_right()
{
    // Move the cursor right
}