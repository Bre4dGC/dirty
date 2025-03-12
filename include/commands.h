#ifndef COMMANDS_H
#define COMMANDS_H

void handle_command(AppState *state, const char *command);
void change_dir(AppState *state, const char *path);
void change_theme();
void open_config();
void home_return();

#endif