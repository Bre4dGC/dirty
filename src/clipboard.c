#include <stddef.h>
#include <string.h>

#include "clipboard.h"
#include "fs.h"
#include "logs.h"

clipboard_t clipboard = {0};

int add_clip(const char *path, const bool is_cut)
{
    if (!path || *path == '\0')
    {
        return log_report(REPORT_INVALID_ARGUMENT_ERROR, "Clipboard item path");
    }

    if (clipboard.count >= CLIPBOARD_LIMIT)
    {
        return log_report(REPORT_LIMIT_REACHED_ERROR, "Clipboard adding item");
    }

    cb_item_t clip = {.path = (char *)path, .is_cut = is_cut};

    for (uint8_t i = 0; i < clipboard.count; ++i)
    {
        if (clipboard.items[i].path && strcmp(clipboard.items[i].path, clip.path) == REPORT_SUCCESS)
        {
            return log_report(REPORT_ALREADY_EXISTS_ERROR, "Clipboard item");
        }
    }
    clipboard.items[clipboard.count++] = clip;
    return log_report(REPORT_SUCCESS, "Clipboard item added");
}

int cb_copy(const char *path)
{
    return add_clip(path, false);
}

int cb_cut(const char *path)
{
    return add_clip(path, true);
}

int cb_paste(const char *path, const uint8_t index)
{
    if (index >= clipboard.count)
    {
        return log_report(REPORT_HANDLE_ERROR, "Clipboard index out of bounds");
    }

    const cb_item_t *clip = &clipboard.items[index];

    if (!clip->path || *clip->path == '\0')
    {
        return log_report(REPORT_INVALID_ARGUMENT_ERROR, "Clipboard item path is invalid");
    }

    log_report(REPORT_SUCCESS, "Paste clipboard item");

    if (clip->is_cut)
    {
        if (fs_move(clip->path, path) != REPORT_SUCCESS)
        {
            return log_report(REPORT_EXECUTE_ERROR, "Clipboard item paste failed during move");
        }

        // Remove the item from the clipboard
        clipboard.items[index] = clipboard.items[--clipboard.count];
        clipboard.items[clipboard.count].path = NULL;
        clipboard.items[clipboard.count].is_cut = false;
    }
    else
    {
        // Handle copy logic if needed
        return log_report(REPORT_UNKNOWN_ERROR, "Clipboard paste for copied items not implemented");
    }

    return log_report(REPORT_SUCCESS, "Clipboard item pasted successfully");
}