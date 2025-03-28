#include "operations/dir_ops.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>  // for PATH_MAX

/* Function for checking if path is directory */
bool is_dir(const char *path) 
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        perror("ERROR: Unable to get file status");
        return false;
    }
    return S_ISDIR(path_stat.st_mode);
}

/* Function for changing directory */
void change_dir(const char *path) 
{
    if (chdir(path) != 0) {
        perror("ERROR: failed to changing directory");
    }
}

void create_item(dir_t *content, item_t *item, const char *name, const char *path, item_type_t type)
{
    (void)item; // Suppress warning about unused parameter
    
    content->items = (item_t *)realloc(content->items, sizeof(item_t) * (content->count + 1));
    if (!content->items) {
        perror("ERROR: Failed to allocate memory for items");
        return;
    }
    
    content->items[content->count].type = type;
    
    if (type == ITEM_TYPE_DIR) {
        content->items[content->count].data.dir = (dir_t *)calloc(1, sizeof(dir_t));
        if (!content->items[content->count].data.dir) {
            perror("ERROR: Failed to allocate memory for directory");
            return;
        }
        content->items[content->count].data.dir->name = strdup(name);
        content->items[content->count].data.dir->path = strdup(path);
    } 
    else {
        content->items[content->count].data.file = (file_t *)calloc(1, sizeof(file_t));
        if (!content->items[content->count].data.file) {
            perror("ERROR: Failed to allocate memory for file");
            return;
        }
        content->items[content->count].data.file->name = strdup(name);
        content->items[content->count].data.file->path = strdup(path);
    }
    
    content->count++;
}

/* Function for getting directory content */
dir_t *get_directory_content(const char *path) 
{
    DIR *dir = opendir(path); // Open directory

    /* Check if directory is opened */
    if (!dir) {
        perror("ERROR: Unable to open directory");
        return NULL;
    }

    dir_t *content = (dir_t *)calloc(1, sizeof(dir_t)); // Directory content
    if (!content) {
        perror("ERROR: Failed to allocate memory for directory content");
        closedir(dir);
        return NULL;
    }
    
    content->name = strdup(path); // Можно извлечь имя директории из пути
    content->path = strdup(path);
    content->count = 0;
    content->scroll_offset = 0;
    content->items = NULL;
    content->previus = NULL;

    struct dirent *entry;

    /* Read directory entries */
    while ((entry = readdir(dir)) != NULL) 
    {
        /* Увеличиваем размер буфера для безопасности*/
        char full_path[PATH_MAX];
        
        /* Проверяем, что пути не слишком длинные*/
        if (strlen(path) + strlen(entry->d_name) + 2 > PATH_MAX) {
            fprintf(stderr, "ERROR: Path too long: %s/%s\n", path, entry->d_name);
            continue;
        }
        
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        /* Check if entry is directory */
        if(is_dir(full_path)) {
            create_item(content, NULL, entry->d_name, path, ITEM_TYPE_DIR);
        }
        else {
            create_item(content, NULL, entry->d_name, path, ITEM_TYPE_FILE);
        }
    }
    closedir(dir); // Close directory
    return content;
}

/*  Function for entering directory */
void enter_dir(dir_t *enter)
{
    if (!enter) return;
    
    /* Check if previus directory is not NULL */
    if(enter->previus != NULL) {
        free(enter->previus);
    }

    // Get the contents of the directory
    dir_t *content = get_directory_content(enter->path);
    if (!content) {
        perror("ERROR: Failed to get directory content");
        return;
    }
    
    // Update the current directory
    content->previus = enter;
    
    // TODO: update the UI with new content
    // display_directory(directory_win, content, 0);
}

/* Function for creating directory */
void create_dir(const char *path, const char *name) 
{
    /* Create full path */
    char full_path[PATH_MAX];
    
    // Checking that the paths are not too long
    if (strlen(path) + strlen(name) + 2 > PATH_MAX) {
        fprintf(stderr, "ERROR: Path too long: %s/%s\n", path, name);
        return;
    }
    
    snprintf(full_path, sizeof(full_path), "%s/%s", path, name); 

    /* Check if directory is created */
    if (mkdir(full_path) != 0) {
        perror("ERROR: failed to creating directory");
    }
}

// Function for renaming directory
void rename_dir(dir_t *dir, const char *new_name) 
{
    char old_path[256];
    char new_path[256];

    snprintf(old_path, sizeof(old_path), "%s/%s", dir->path, dir->name);
    snprintf(new_path, sizeof(new_path), "%s/%s", dir->path, new_name);

    /* Check if directory is renamed */
    if (rename(old_path, new_path) != 0) {
        perror("ERROR: failed to renaming directory");
        return;
    }
    dir->name = strdup(new_name); // Update directory name
}

/* Function for deleting directory */
void delete_dir(dir_t *dir) 
{
    char full_path[256];

    snprintf(full_path, sizeof(full_path), "%s/%s", dir->path, dir->name);

    /* Check if directory is deleted */
    if (rmdir(full_path) != 0) {
        perror("ERROR: failed to deleting directory");
    }
}

/* Function for freeing directory */
void free_dir(dir_t *dir)
{
    if (!dir) return;
    
    free(dir->path);
    free(dir->name);
    
    /* Free directory items */
    for (int i = 0; i < dir->count; ++i) {
        if (is_directory(&dir->items[i])) {
            free(dir->items[i].data.dir);
        } else {
            free(dir->items[i].data.file);
        }
    }
    free(dir->items);

    free(dir);
}

dir_t *leave_dir(dir_t *dir)
{
    if (!dir || !dir->previus) return NULL;
    
    dir_t *prev_dir = dir->previus;
    free_dir(dir);
    return prev_dir;
}