#include <PDCurses/curses.h>
#include <string.h>
#include <stdlib.h>
#include "ui.h"
#include "ui/panels.h"
#include "ui/input.h"
#include "operations/dir_ops.h"

void init_ui() {
    // Initializing the PDCurses lib
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    init_windows(); // Initializing windows
}

void load_initial_content(const char *path) {
    // Loading the initial directory
    current_dir = read_dir(path);
    if (current_dir) {
        current_dir->scroll_offset = 0;
        display_directory(directory_win, current_dir, 0);
        
        // If there are elements and the first element is a directory
        if (current_dir->count > 0 && is_directory(&current_dir->items[0])) {
            content_dir = current_dir->items[0].data.dir;
            display_content(content_win, content_dir, 0);
        }
        
        // Display information about the selected item
        if (current_dir->count > 0) {
            display_info(&current_dir->items[0]);
        }
    }
    
    // Select the active panel (directory by default)
    wattron(directory_win, A_BOLD);
    box(directory_win, 0, 0);
    wattroff(directory_win, A_BOLD);
    wrefresh(directory_win);
    
    display_command_line(""); // Display an empty command line
}

int get_user_input() {
    return wgetch(stdscr);
}

void run_ui_loop() {
    int running = 1;
    int key;
    char cmd_buffer[256] = {0};
    int cmd_pos = 0;
    
    while (running) {
        key = get_user_input();
        
        // Output processing
        if (key == 'q' || key == 'Q') {
            running = 0;
            continue;
        }
        
        // Command entry mode
        if (active_panel == PANEL_COMMAND) {
            // ESC - exit command mode
            if (key == 27) { 
                active_panel = PANEL_DIRECTORY;
                display_command_line("");
            } 
            // Enter - command execution
            else if (key == '\n') { 
                cmd_buffer[cmd_pos] = '\0';
                process_command(cmd_buffer);
                
                // Return to navigation mode
                active_panel = PANEL_DIRECTORY;
                cmd_pos = 0;
                memset(cmd_buffer, 0, sizeof(cmd_buffer));
                display_command_line("");
            } 
            // Backspace
            else if (key == KEY_BACKSPACE || key == 127) {
                if (cmd_pos > 0) cmd_buffer[--cmd_pos] = '\0';
                display_command_line(cmd_buffer);
            } 
            // Printable chars
            else if (cmd_pos < sizeof(cmd_buffer) - 1 && key >= 32 && key <= 126) { 
                cmd_buffer[cmd_pos++] = (char)key;
                cmd_buffer[cmd_pos] = '\0';
                display_command_line(cmd_buffer);
            }
        } else {
            navigate(key); // Navigation mode
        }
    }
}

void cleanup_ui() {
    cleanup_windows(); // Window cleaning

    // Clearing directory data
    if (current_dir) {
        free_dir(current_dir);
        current_dir = NULL;
    }
    
    // content_dir refers to a subdirectory of current_dir,
    // so there is no need to free it separately
    content_dir = NULL;

    endwin(); // Finishing work with PDCurses
}