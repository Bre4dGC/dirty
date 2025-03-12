#include "ui.h"
#include "file_ops.h"
#include "config.h"

int main() {
    
    return 0;
}

void init(AppState *state)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    strcpy(state->current_path, ".");
    dir_load(&state->left_pane, state->current_path);
    state->active_pane = &state->left_pane;
}

void cleanup()
{
    endwin();
}