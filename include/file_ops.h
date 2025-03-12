#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

#define FOREACH_TYPE(TYPE)\
        TYPE(File)        \
        TYPE(Folder)      \

#define GENERATE_ENUM(ENUM)     ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum {
    FOREACH_TYPE(GENERATE_ENUM)
} Type;

static const char *TYPE_STRING[] = {
    FOREACH_TYPE(GENERATE_STRING)
};

typedef struct {
    Type type;
    char *name;
    char *path;
    bool is_cut;
    bool is_selected;
    struct stat info;
} FileEntry;

typedef struct {
    FileEntry *files;
    int elem_count;
    int scroll_offset;
    int selected_index;
} Directory;

typedef struct {
    char *current_path;
    Directory left_pane;
    Directory right_pane;
    Directory *active_pane;
} AppState;

void dir_load(Directory *content, const char *path);
void dir_open(Directory *pane, char *path);
void dir_create();
void file_open();
void file_create();
void element_del();
void element_copy();
void element_move();
void element_rename();

#endif