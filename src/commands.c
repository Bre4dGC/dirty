#include "commands.h"
#include "file_ops.h"

void handle_command(AppState *state, const char *command)
{
    if (strncmp(command, "cd ", 3) == 0) {
        change_dir(state, command + 3);
    } else if (strcmp(command, "home") == 0) {
        strcpy(state->current_path, getenv("HOME"));
        dir_load(&state->left_pane, state->current_path);
    }
}

void change_dir(AppState *state, const char *path) 
{
    strcpy(state->current_path, path);
    dir_load(&state->left_pane, state->current_path);
}

void change_theme()
{

}

void open_config()
{

}

void home_return()
{
    
}