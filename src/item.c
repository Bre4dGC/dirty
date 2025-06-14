#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "include/item.h"
#include "include/logs.h"

int open_item(const char *item_path, const bool is_dir)
{
        if (is_dir)
        {
                // TODO: Implement open directory logic
        }
        else
        {
                // TODO: Implement open file logic
        }

        return log_status(SUCCESS, "Item open");
}

int create_item(const char *item_path, const char *name, const bool is_dir)
{
        if (is_dir)
        {
                if (mkdir(item_path, 0755) == -1)
                {
                        return log_status(EXECUTE_ERROR, "Create directory");
                }
        }
        else
        {
                FILE *file = fopen(item_path, "w");
                if (!file)
                {
                        return log_status(EXECUTE_ERROR, "Create file");
                }
                fclose(file);
        }

        return log_status(SUCCESS, "Item created");
}

int rename_item(const char *item_path, const char *new_name)
{
        if (rename(item_path, new_name) == -1)
        {
                return log_status(EXECUTE_ERROR, "Rename item");
        }
        return log_status(SUCCESS, "Item renamed");
}

int move_item(const char *item_path, const char *dest_path)
{
        if (rename(item_path, dest_path) == -1)
        {
                return log_status(EXECUTE_ERROR, "Move item");
        }
        return log_status(SUCCESS, "Item moved");
}

int change_item_permission(const char *item_path, const char *mode)
{
        if (chmod(item_path, strtol(mode, NULL, 8)) == -1)
        {
                return log_status(EXECUTE_ERROR, "Change item permission");
        }
        return log_status(SUCCESS, "Item permission changed");
}

int remove_item(const char *item_path)
{
        if (remove(item_path) == -1)
        {
                return log_status(EXECUTE_ERROR, "Remove item");
        }
        return log_status(SUCCESS, "Item removed");
}