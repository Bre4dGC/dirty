#include "operations/commands.h"
#include "operations/file_ops.h"
#include "operations/dir_ops.h"
#include "operations/clipboard.h"
#include <string.h>
#include <stdio.h>

/* Execute a command */
bool execute_command(const char *command) {
    if (command == NULL) {
        return false;
    }
    
    // Parse the command
    char cmd[256];
    char arg1[256];
    char arg2[256];
    
    int parsed = sscanf(command, "%255s %255s %255s", cmd, arg1, arg2);
    
    if (parsed < 1) {
        return false;
    }
    
    /* Execute the command */
    if (strcmp(cmd, "cd") == 0 && parsed >= 2) {
        // Change directory
        change_dir(arg1);
        return true;
    } 
    else if (strcmp(cmd, "mkdir") == 0 && parsed >= 2) {
        // Create directory
        create_dir(".", arg1);
        return true;
    } 
    else if (strcmp(cmd, "touch") == 0 && parsed >= 2) {
        // Create file
        create_file(".", arg1);
        return true;
    } 
    else if (strcmp(cmd, "rm") == 0 && parsed >= 2) {
        // Delete file or directory
        // This is a simplified implementation
        file_t file = {0};
        file.name = arg1;
        file.path = ".";
        delete_file(&file);
        return true;
    } 
    else if (strcmp(cmd, "cp") == 0 && parsed >= 3) {
        // Copy file
        // This is a simplified implementation
        file_t file = {0};
        file.name = arg1;
        file.path = ".";
        copy_file(&file);
        return true;
    } 
    else if (strcmp(cmd, "mv") == 0 && parsed >= 3) {
        // Move file
        // This is a simplified implementation
        file_t file = {0};
        file.name = arg1;
        file.path = ".";
        file.is_cut = true;
        copy_file(&file);
        return true;
    }
    return false;
}

