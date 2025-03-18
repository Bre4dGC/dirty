#include <dirent.h>
#include <sys/stat.h>
#include "file_ops.h"

// Structure for storing directories
typedef struct {
    int count;          // Number of files
    int scroll_offset;  // Scroll offset
    char *name;         // Name of the directory
    char *path;         // Path to the directory
    item_u *items;      // List of files
    dir_t *previus;     // Previous directory
} dir_t;

// Union for storing directories and files
typedef union {
    dir_t *dir;   // Directory
    file_t *file; // File
} item_u;

bool is_dir(const char *path);                       // Check if the path is a directory
void change_dir(const char *path);                   // Change the current directory
void enter_dir(dir_t *dir);                          // Enter the directory
void create_dir(const char *path, const char *name); // Create a new directory
void rename_dir(dir_t *dir, const char *new_name);   // Rename the directory
void delete_dir(dir_t *dir);                         // Delete the directory
void leave_dir(dir_t *prev_dir);                     // Leave the directory
void free_dir(dir_t *dir);                           // Free the directory