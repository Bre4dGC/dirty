#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include "file_ops.h"
#include "dir_ops.h"

#define MAX_CAPACITY 10 // Maximum number of files in the clipboard

typedef struct {
    int count;                  // Number of files
    file_t files[MAX_CAPACITY]; // List of files
} clipboard_t;

void cut_file(file_t *files); 
void copy_file(file_t *files);
void paste_file(file_t *file, dir_t *to_dir);
void free_clipboard();

#endif // CLIPBOARD_H