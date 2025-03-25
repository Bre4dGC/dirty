#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include "operations/file_ops.h"
#include "operations/dir_ops.h"

#define MAX_CLIPBOARD_SIZE 10 // Maximum number of files in the clipboard

// Clipboard structure
typedef struct {
    int count;                        // Number of files
    file_t files[MAX_CLIPBOARD_SIZE]; // List of files
} clipboard_t;

void cut_file(file_t *files);                   // Cut the file
void copy_file(file_t *files);                  // Copy the file
void paste_file(int buff_index, dir_t *to_dir); // Paste the file
void free_clipboard();                          // Free the clipboard

#endif // CLIPBOARD_H