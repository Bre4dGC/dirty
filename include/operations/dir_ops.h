#ifndef DIR_OPS_H
#define DIR_OPS_H

#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "operations/file_ops.h"

// Предварительные объявления структур
typedef struct dir_t dir_t;
typedef struct item_t item_t;

// Element type definition
typedef enum {
    ITEM_TYPE_FILE,
    ITEM_TYPE_DIR
} item_type_t;

// Structure for storing a file system element
typedef struct item_t {
    item_type_t type;
    union {
        dir_t *dir;
        file_t *file;
    } data;
} item_t;

// Structure for storing directories
typedef struct dir_t {
    int count;          // Number of files
    int scroll_offset;  // Scroll offset
    char *name;         // Name of the directory
    char *path;         // Path to the directory
    item_t *items;      // List of files and directories
    struct dir_t *previus; // Previous directory
} dir_t;

// Function for checking the element type
static inline bool is_directory(const item_t *item) {
    return item->type == ITEM_TYPE_DIR;
}

bool is_dir(const char *path);                       // Check if the path is a directory
void change_dir(const char *path);                   // Change the current directory
void enter_dir(dir_t *dir);                          // Enter the directory
void create_dir(const char *path, const char *name); // Create a new directory
void rename_dir(dir_t *dir, const char *new_name);   // Rename the directory
void delete_dir(dir_t *dir);                         // Delete the directory
dir_t *leave_dir(dir_t *dir);                     // Leave the directory
void free_dir(dir_t *dir);                           // Free the directory
void create_item(dir_t *content, item_t *item, const char *name, const char *path, item_type_t type);

#endif // DIR_OPS_H