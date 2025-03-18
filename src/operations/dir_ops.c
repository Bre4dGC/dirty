#include "dir_ops.h"

bool is_dir(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        perror("ERROR: Unable to get file status");
        return false;
    }
    return S_ISDIR(path_stat.st_mode);
}

void change_dir(const char *path) 
{
    if (chdir(path) != 0) {
        perror("ERROR: failed to changing directory");
    }
}

dir_t *get_directory_content(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("ERROR: Unable to open directory");
        return NULL;
    }

    dir_t *content = calloc(sizeof(dir_t));

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if(is_dir(("%s/%s", path, entry->d_name))) {
            content->items = realloc(content->items, sizeof(dir_t *) * (content->count + 1));
            content->items[content->count] = calloc(sizeof(dir_t));
            content->items[content->count]->name = strdup(entry->d_name);
            content->items[content->count]->path = strdup(path);
            content->count++;
        }
        else {
            content->items = realloc(content->items, sizeof(file_t *) * (content->count + 1));
            content->items[content->count] = calloc(sizeof(file_t));
            content->items[content->count]->name = strdup(entry->d_name);
            content->items[content->count]->path = strdup(path);
            content->count++;
        }
    }
    closedir(dir);
    return content;
}

void enter_dir(dir_t *dir)
{
    if(dir->previus != NULL) {
        free(dir->previus);
    }
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("c:\\src\\")) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            printf ("%s\n", ent->d_name);
        }
        closedir (dir);
    } else {
        perror ("ERROR: failed to get directory");
    }
}

void create_dir(const char *path, const char *name) {
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, name);
    if (mkdir(full_path) != 0) {
        perror("ERROR: failed to creating directory");
    }
}

void rename_dir(dir_t *dir, const char *new_name) {
    char old_path[256];
    char new_path[256];
    snprintf(old_path, sizeof(old_path), "%s/%s", dir->path, dir->name);
    snprintf(new_path, sizeof(new_path), "%s/%s", dir->path, new_name);
    if (rename(old_path, new_path) != 0) {
        perror("ERROR: failed to renaming directory");
        return;
    }
    dir->name = strdup(new_name);
}

void delete_dir(dir_t *dir) {
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", dir->path, dir->name);
    if (rmdir(full_path) != 0) {
        perror("ERROR: failed to deleting directory");
    }
}

void free_dir(dir_t *dir)
{
    for (int i = 0; i < dir->count; ++i) {
        free(dir->items[i]);
    }
    free(dir);
}

void leave_dir(dir_t *dir)
{
    dir_t prev_dir = dir->previus;
    free_dir(dir);
    return prev_dir;
}