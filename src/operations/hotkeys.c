#include "hotkeys.h"
#include <stdlib.h>
#include <string.h>

// Storage for registered hotkeys
static hotkey_t hotkeys[MAX_HOTKEYS];
static int hotkey_count = 0;

static bool is_hotkey_registered(int key_code, bool ctrl, bool alt, bool shift) {
    for (int i = 0; i < hotkey_count; i++) {
        if (hotkeys[i].key_code == key_code &&
            hotkeys[i].ctrl == ctrl &&
            hotkeys[i].alt == alt &&
            hotkeys[i].shift == shift) {
            return true;
        }
    }
    return false;
}

bool register_hotkey(int key_code, bool ctrl, bool alt, bool shift, void (*action)()) {
    if (hotkey_count >= MAX_HOTKEYS || is_hotkey_registered(key_code, ctrl, alt, shift)) {
        return false; // The maximum number has been exceeded or the hotkey already exists
    }

    hotkeys[hotkey_count++] = (hotkey_t){key_code, ctrl, alt, shift, action};
    return true;
}

bool unregister_hotkey(int key_code, bool ctrl, bool alt, bool shift) {
    for (int i = 0; i < hotkey_count; i++) {
        if (hotkeys[i].key_code == key_code &&
            hotkeys[i].ctrl == ctrl &&
            hotkeys[i].alt == alt &&
            hotkeys[i].shift == shift) {
            memmove(&hotkeys[i], &hotkeys[i + 1], (hotkey_count - i - 1) * sizeof(hotkey_t));
            hotkey_count--;
            return true;
        }
    }
    return false; // Hotkey was not found
}

void process_hotkeys(int key_code, bool ctrl, bool alt, bool shift) {
    for (int i = 0; i < hotkey_count; i++) {
        if (hotkeys[i].key_code == key_code &&
            hotkeys[i].ctrl == ctrl &&
            hotkeys[i].alt == alt &&
            hotkeys[i].shift == shift &&
            hotkeys[i].action) {
            hotkeys[i].action(); // Perform the action associated with the hotkey
            return;
        }
    }
}