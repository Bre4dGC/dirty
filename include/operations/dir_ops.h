#include <sys/stat.h>
#include "file_ops.h"

typedef struct {
    int count;          // Number of files
    int scroll_offset;  // Scroll offset
    char *path;         // Path to the directory
    file_t *content;    // List of files
    dir_t *previus_dir; // Previous directory
} dir_t;

void enter_dir(char *path);
void create_dir(char *path, char *name);
void rename_dir(dir_t *dir, char *new_name);
void delete_dir(dir_t *dir);
void leave_dir(dir_t *prev_dir);