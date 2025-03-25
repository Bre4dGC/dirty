#ifndef HOTKEYS_H
#define HOTKEYS_H

#include <stdbool.h>
#include <stdarg.h>

// Structure for storing information about a hotkey
typedef struct {
    char *keys;                 /* Key combination to activate the hotkey | Example: "Ctrl+Alt+A" or "Ctrl X" */
    void (*action)(void*, ...); // Pointer to the function to be performed when activated
} hotkey_t;

#endif // HOTKEYS_H