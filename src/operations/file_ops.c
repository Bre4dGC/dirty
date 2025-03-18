#include "file_ops.h"

void create_file(const char *path, const char *name)
{
    if (path == NULL || name == NULL) {
        fprintf(stderr, "ERROR: Invalid input parameters.\n");
        return;
    }

    if(fopen(("%s/%s",path, name), "w") == NULL) {
        fprintf(stderr, "ERROR: Unable to create file.\n");
    }
}

void rename_file(file_t *file, const char *new_name) {
    if (file == NULL || new_name == NULL) {
        fprintf(stderr, "ERROR: Invalid input parameters.\n");
        return;
    }

    char old_path[256];
    char new_path[256];

    // Form the full path to the old and new file
    snprintf(old_path, sizeof(old_path), "%s/%s", file->path, file->name);
    snprintf(new_path, sizeof(new_path), "%s/%s", file->path, new_name);

    // Rename the file
    if (rename(old_path, new_path) != 0) {
        perror("ERROR: renaming the file");
        return;
    }

    // Update the file name in the structure
    free(file->name);
    file->name = strdup(new_name);
}

void delete_file(file_t *file)
{
    if (file == NULL) {
        fprintf(stderr, "ERROR: Invalid input parameters.\n");
        return;
    }

    if (remove(("%s%s", file->path, file->name)) == 1) {
        fprintf(stderr, "ERROR: Unable to delete the file.\n");
        return;
    }
    free(file);
}