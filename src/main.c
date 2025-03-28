#include <stdio.h>
#include "operations.h"
#include "ui.h"
#include "config.h"

int main()
{
    // Configuration loading
    config_t *config = load_config("config.json");
    if (!config) {
        fprintf(stderr, "Failed to load configuration\n");
        return 1;
    }
    
    // UI initialization
    init_ui();
    
    // Main program cycle
    int ch;
    while ((ch = getch()) != 'q') {
        navigate(ch);
    }
    
    // Resource cleansing
    cleanup_ui();
    free_config(config);
    
    return 0;    
}