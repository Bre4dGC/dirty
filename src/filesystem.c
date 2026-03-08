#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "filesystem.h"
#include "logs.h"

int fs_open(const char *path, const bool is_dir)
{
    if (is_dir)
    {
        // TODO: Implement open directory logic
    }
    else
    {
        // TODO: Implement open file logic
    }

    return log_report(REPORT_SUCCESS, "Item open");
}

int fs_create(const char *path, const char *name, const bool is_dir)
{
    if (is_dir)
    {
        if (mkdir(path, 0755) == -1)
        {
            return log_report(REPORT_EXECUTE_ERROR, "Create directory");
        }
    }
    else
    {
        FILE *file = fopen(path, "a");
        if (!file)
        {
            return log_report(REPORT_EXECUTE_ERROR, "Create file");
        }
        fclose(file);
    }

    return log_report(REPORT_SUCCESS, "Item created");
}

int fs_rename(const char *old, const char *new)
{
    if (rename(old, new) == -1)
    {
        return log_report(REPORT_EXECUTE_ERROR, "Rename item");
    }
    return log_report(REPORT_SUCCESS, "Item renamed");
}

int fs_move(const char *path, const char *dest)
{
    if (!path || !dest || *path == '\0' || *dest == '\0')
    {
        return log_report(REPORT_INVALID_ARGUMENT_ERROR, "Invalid path(s) for move");
    }

    log_report(REPORT_SUCCESS, "Move file");

    if (rename(path, dest) == -1)
    {
        perror("rename");
        return log_report(REPORT_EXECUTE_ERROR, "Move operation failed");
    }

    return log_report(REPORT_SUCCESS, "Item moved");
}

int fs_chmod(const char *path, const fs_mod_t mode)
{
    if (chmod(path, (unsigned int)mode))
    {
        return log_report(REPORT_EXECUTE_ERROR, "Change item permission");
    }
    return log_report(REPORT_SUCCESS, "Item permission changed");
}

int fs_remove(const char *path)
{
    if (remove(path) == -1)
    {
        return log_report(REPORT_EXECUTE_ERROR, "Remove item");
    }
    return log_report(REPORT_SUCCESS, "Item removed");
}
