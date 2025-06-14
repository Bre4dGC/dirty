#include <stddef.h> // For NULL
#include <string.h>

#include "include/clipboard.h"
#include "include/logs.h"

clipboard_t clipboard = {0};

// For "paste_item" function
extern int move_item(const char *item_path, const char *dest_path);
extern int remove_item(const char *item_path);
//

static int clipboard_add_item(const char *path, const bool is_cut)
{
        if (!path || *path == '\0')
        {
                return log_status(INVALID_ARGUMENT_ERROR, "Clipboard item path");
        }

        if (clipboard.count >= CLIPBOARD_LIMIT)
        {
                return log_status(LIMIT_REACHED_ERROR, "Clipboard adding item");
        }

        clipboard_item_t clip = {.path = (char *)path, .is_cut = is_cut};

        for (uint_fast8_t i = 0; i < clipboard.count; ++i)
        {
                if (clipboard.items[i].path && strcmp(clipboard.items[i].path, clip.path) == SUCCESS)
                {
                        return log_status(ALREADY_EXISTS_ERROR, "Clipboard item");
                }
        }

        clipboard.items[clipboard.count++] = clip;
        return log_status(SUCCESS, "Clipboard item added");
}

int copy_item(const char *path)
{
        return clipboard_add_item(path, false);
}

int cut_item(const char *path)
{
        return clipboard_add_item(path, true);
}

int paste_item(const char *path, const uint8_t index)
{
        if (index >= clipboard.count)
        {
                return log_status(HANDLE_ERROR, "Clipboard index out of bounds");
        }

        const clipboard_item_t *clip = &clipboard.items[index];

        if (clip->is_cut)
        {
                if (move_item(clip->path, path) != SUCCESS && remove_item(clip->path) != SUCCESS)
                {
                        return log_status(EXECUTE_ERROR, "Clipboard item paste");
                }

                // Clear the clipboard item after moving
                clipboard.items[index] = clipboard.items[--clipboard.count];
                clipboard.items[clipboard.count].path = NULL;
                clipboard.items[clipboard.count].is_cut = false;
        }
        else
        {
                move_item(clip->path, path);
        }

        return log_status(SUCCESS, "Clipboard item pasted");
}