#ifndef CONFIG_H
#define CONFIG_H

#include <PDcurses/curses.h>

typedef struct {
    char *name;
    int background;
    int foreground;
    int highlight;
} Theme;

struct {
    Theme current_theme;       // Текущая тема
    Theme available_themes[10]; // Список доступных тем
    int theme_count;           // Количество доступных тем
    char *home_path;
} Config;


void load_config();
void save_config();
void apply_theme();

#endif