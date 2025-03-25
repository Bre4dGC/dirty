#include "operations/clipboard.h"
#include "operations/file_ops.h"

clipboard_t clipboard = {0, {NULL}}; // Initialization of the clipboard structure

void cut_file(file_t *file)
{
    copy_file(file);     // Copying a file
    file->is_cut = true; // Mark as cut
}

void copy_file(file_t *file)
{
    if (clipboard.count < MAX_CLIPBOARD_SIZE) {
        clipboard.files[clipboard.count] = *file;
    } else {
        clipboard.files[0] = *file;
    }
}

void paste_file(int buff_index, dir_t *to_dir)
{
    file_t file = clipboard.files[buff_index];
    char new_path[256];
    snprintf(new_path, sizeof(new_path), "%s/%s", to_dir->path, file.name);
    // copy_file_to_path(file.path, new_path); // Copying a file to a new directory
    if(file.is_cut) {
        delete_file(&file);
    }
}

void free_clipboard()
{
    for (int index = 0; index < clipboard.count; index++) {
        clipboard.files[index] = (file_t){0}; // Free of file_t structure
    }
    clipboard.count = 0;
}