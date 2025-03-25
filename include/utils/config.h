#ifndef CONFIG_H
#define CONFIG_H

#include "utils/themes.h"
#include "operations/hotkey.h"

#define MAX_THEMES_COUNT 10

typedef struct {
    char *font;        // Font name
    char *curr_theme;  // Name of the current theme
    char *home_path;   // Path to the home directory
    theme_t *themes;   // Array of themes
    int themes_count;  // Number of themes
    hotkey_t *hotkeys; // Array of hotkeys
    int hotkeys_count; // Number of hotkeys
} config_t;

config_t *load_config(const char *filename);
bool save_config(const config_t *config, const char *config_file);
void free_config(config_t *config);

#endif // CONFIG_H 