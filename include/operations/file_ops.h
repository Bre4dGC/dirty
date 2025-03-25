#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdlib.h>

// File structure
typedef struct file_t{
    char *name;       // File name
    char *mode;       // File permissions
    char *path;       // Full path
    bool is_cut;      // True if the file was cut
    struct stat stat; // File metadata
} file_t;

void create_file(const char *path, const char *name); // Create a new file
void rename_file(file_t *file, const char *new_name); // Rename a file
void delete_file(file_t *file);                       // Delete a file

#endif // FILE_OPS_Hs