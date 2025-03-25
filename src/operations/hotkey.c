#include "operations/hotkey.h"
#include "utils/hotkeys_parser.h"

// Register a new hotkey
bool register_hotkey(const char *keys, void (*action)(void*, ...)) {
    if (keys == NULL || action == NULL) {
        return false;
    }
    
    // Reallocate the hotkeys array
    hotkey_t *new_hotkeys = realloc(hotkeys, sizeof(hotkey_t) * (hotkey_count + 1));
    if (new_hotkeys == NULL) {
        return false;
    }
    
    hotkeys = new_hotkeys;
    
    // Initialize the new hotkey
    hotkeys[hotkey_count].keys = strdup(keys);
    hotkeys[hotkey_count].action = action;
    hotkey_count++;
    
    return true;
}

// Find a hotkey by its key combination
hotkey_t *find_hotkey(const char *keys) {
    if (keys == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < hotkey_count; i++) {
        if (strcmp(hotkeys[i].keys, keys) == 0) {
            return &hotkeys[i];
        }
    }
    
    return NULL;
}

// Execute a hotkey action
bool execute_hotkey(const char *keys, void *arg, ...) {
    hotkey_t *hotkey = find_hotkey(keys);
    if (hotkey == NULL) {
        return false;
    }
    
    va_list args;
    va_start(args, arg);
    hotkey->action(arg, args);
    va_end(args);
    
    return true;
}

// Free all registered hotkeys
void free_hotkeys() {
    for (int i = 0; i < hotkey_count; i++) {
        free(hotkeys[i].keys);
    }
    
    free(hotkeys);
    hotkeys = NULL;
    hotkey_count = 0;
}

