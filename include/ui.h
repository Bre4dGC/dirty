#ifndef UI_H
#define UI_H

#include "ui/input.h"
#include "ui/panels.h"

void init_ui();
void cleanup_ui();

void display_main_menu();
void display_file_menu();

void display_error(char *message);
void display_success(char *message);

void display_dir_panel();
void display_file_panel();

void display_input_prompt(char *message);
void display_input_error(char *message);

#endif // UI_H