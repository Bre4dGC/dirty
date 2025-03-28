#include <PDCurses/curses.h>
#include "ui/input.h"
#include "ui/panels.h"
#include "operations/dir_ops.h"

panel_type_t active_panel = PANEL_DIRECTORY; // Current active panel

// Current directories
dir_t *current_dir = NULL;
dir_t *content_dir = NULL;

void navigate(int key) {
    switch (key) {
        case KEY_UP:
            if (active_panel == PANEL_DIRECTORY && current_dir) {
                if (current_dir->scroll_offset > 0)
                    current_dir->scroll_offset--;
                display_directory(directory_win, current_dir, current_dir->scroll_offset);
                
                // Updating information about the selected item
                item_t *selected_item = &current_dir->items[current_dir->scroll_offset];
                display_info(selected_item);
            } else if (active_panel == PANEL_CONTENT && content_dir) {
                if (content_dir->scroll_offset > 0)
                    content_dir->scroll_offset--;
                display_content(content_win, content_dir, content_dir->scroll_offset);
                
                // Updating information about the selected item
                item_t *selected_item = &content_dir->items[content_dir->scroll_offset];
                display_info(selected_item);
            }
            break;
            
        case KEY_DOWN:
            if (active_panel == PANEL_DIRECTORY && current_dir) {
                if (current_dir->scroll_offset < current_dir->count - 1) {
                    current_dir->scroll_offset++;
                }

                display_directory(directory_win, current_dir, current_dir->scroll_offset);
                
                // Updating information about the selected item
                item_t *selected_item = &current_dir->items[current_dir->scroll_offset];
                display_info(selected_item);
            } 
            else if (active_panel == PANEL_CONTENT && content_dir) {
                if (content_dir->scroll_offset < content_dir->count - 1)
                    content_dir->scroll_offset++;
                display_content(content_win, content_dir, content_dir->scroll_offset);
                
                // Updating information about the selected item
                item_t *selected_item = &content_dir->items[content_dir->scroll_offset];
                display_info(selected_item);
            }
            break;
            
        case KEY_LEFT:
            if (active_panel == PANEL_CONTENT) {
                active_panel = PANEL_DIRECTORY;
                // Select the active panel
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
                // Select the active panel
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
                // Get the selected element
                item_t *selected_item = &current_dir->items[current_dir->scroll_offset];
                
                if (is_directory(selected_item) && is_dir(selected_item->data.dir->path)) {
                    // If it's a directory, open it
                    enter_dir(selected_item->data.dir);
                    
                    // Update the contents of the right panel
                    if (selected_item->data.dir->count > 0) {
                        content_dir = selected_item->data.dir->items[0].data.dir;
                        display_content(content_win, content_dir, 0);
                    }
                }
            } 
            else if (active_panel == PANEL_CONTENT && content_dir) {
                // Get the selected element
                item_t *selected_item = &content_dir->items[content_dir->scroll_offset];
                
                if (is_directory(selected_item) && is_dir(selected_item->data.dir->path)) {
                    // If it is a directory, move the current directory to the left pane
                    current_dir = content_dir;
                    display_directory(directory_win, current_dir, 0);
                    
                    // Open the selected directory in the right pane
                    content_dir = selected_item->data.dir;
                    display_content(content_win, content_dir, 0);
                }
            }
            break;
            
        case ':': // Command mode
            active_panel = PANEL_COMMAND;
            // Clear the command prompt and wait for input
            display_command_line("");
            // TODO: add logic for entering a command
            break;
    }
}

void process_command(const char *command) {
    if (!command || strlen(command) == 0) {
        return;
    }
    
    // Simple command processing
    if (strcmp(command, "help") == 0) {
        // Display help
        // Here you can add the display of help in a separate window
    } else if (strncmp(command, "cd ", 3) == 0) {
        // Changing the directory
        const char *path = command + 3;
        dir_t *new_dir = read_dir(path);
        if (new_dir) {
            if (current_dir) {
                free_dir(current_dir);
            }
            current_dir = new_dir;
            current_dir->scroll_offset = 0;
            display_directory(directory_win, current_dir, 0);
            
            // Updating information about the selected item
            if (current_dir->count > 0) {
                display_info(&current_dir->items[0]);
            }
        }
    }
    // TODO: add: copy, move, delete, etc.
}