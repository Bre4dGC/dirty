#ifndef UI_H
#define UI_H

#include "ui/input.h"
#include "ui/panels.h"
#include "operations/dir_ops.h"

void init_ui();
void cleanup_ui();
void run_ui_loop();
int get_user_input();
void load_initial_content(const char *path);

#endif // UI_H