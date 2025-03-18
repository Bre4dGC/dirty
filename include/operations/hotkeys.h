#ifndef HOTKEYS_H
#define HOTKEYS_H

#include <stdbool.h>

#define MAX_HOTKEYS 100 // Maximum number of hotkeys

// Structure for storing information about a hotkey
typedef struct {
    int key_code;     // Key code
    bool ctrl;        // Is Ctrl pressed
    bool alt;         // Is Alt pressed
    bool shift;       // Is Shift pressed
    void (*action)(); // Pointer to the function to be performed when activated
} hotkey_t;

/*
 * Registers a new hotkey
 * by associating a key combination
 * with a function 
 */
bool register_hotkey(int key_code, bool ctrl, bool alt, bool shift, void (*action)());

/* Deletes a registered hotkey */
bool unregister_hotkey(int key_code, bool ctrl, bool alt, bool shift);

/* 
 * Called on keystrokes, 
 * checks if the hotkey is registered 
 * and performs the corresponding action 
 */
void process_hotkeys(int key_code, bool ctrl, bool alt, bool shift);

#endif // HOTKEYS_H