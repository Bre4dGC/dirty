#include "themes.h"

#define MAX_THEMES_COUNT 10

typedef struct {
    theme_t *curr_theme;
    theme_t themes[MAX_THEMES_COUNT];
} config_t;