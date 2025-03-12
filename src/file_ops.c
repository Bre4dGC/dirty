#include "file_ops.h"

void dir_load(Directory *content, const char *path)
{
    DIR *dir = opendir(path);

    if(dir == NULL) return;

    struct dirent *entry;
    struct stat statbuf;
    content->elem_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        int capacity = 10;
        content->files = (FileEntry *)malloc(capacity * sizeof(FileEntry));

        if(content->files == NULL) return;

        strcpy(content->files[content->elem_count].name, entry->d_name);

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        content->files[content->elem_count].type = S_ISDIR(statbuf.st_mode) ? Folder : Folder;
        content->elem_count++;
    }
    closedir(dir);
}

void dir_open(Directory *pane, char *path)
{
    if (pane->files[pane->selected_index].type == Folder) {
        strcat(path, "/");
        strcat(path, pane->files[pane->selected_index].name);
        dir_load(pane, path);
    }
}

void dir_create()
{

}

void file_create()
{

}

void file_open()
{

}

void element_del()
{

}

void element_copy()
{

}

void element_move()
{

}

void element_rename()
{

}