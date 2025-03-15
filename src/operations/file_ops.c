#include "file_ops.h"
#include "dir_ops.h"

void enter_dir(char *path)
{
    // TODO: Implement this function
    // This function should change the current directory to the one specified by the path.
}

void create_dir(char *path, char *name)
{
    // TODO: Implement this function
    // This function should create a new directory with the specified name in the specified path.
}

void rename_dir(dir_t *dir, char *new_name)
{
    // TODO: Implement this function
    // This function should rename the specified directory to the new name.
}

void delete_dir(dir_t *dir)
{
    // TODO: Implement this function
    // This function should delete the specified directory.
}

void leave_dir(dir_t *prev_dir)
{
    // TODO: Implement this function
    // This function should leave the current directory and go back to the previous one.
}