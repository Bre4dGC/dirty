#include "clipboard.h"
#include "file_ops.h"

clipboard_t clipboard = {0, {NULL}};

void cut_file(file_t *files)
{
    // TODO: Implement this function
    // This function should add the specified files to the clipboard and remove them from the current directory.
}

void copy_file(file_t *files)
{
    // TODO: Implement this function
    // This function should add the specified files to the clipboard.
}

void paste_file(file_t *file, dir_t *to_dir)
{
    // TODO: Implement this function
    // This function should paste the files from the clipboard to the specified directory.
    // This function should also clear the clipboard after pasting the files.
}

void free_clipboard()
{
    for (int index = 0; index < clipboard.count; index++) {
        // clipboard.files[index] = NULL; FIXME: a value of type "void *" cannot be assigned to an entity of type "file_t"
    }
    clipboard.count = 0;
}