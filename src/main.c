#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "clipboard.h"
#include "commands.h"
#include "config.h"
#include "file-system.h"
#include "hotkeys.h"
#include "logs.h"
#include <unistd.h>

int main()
{
        // Test log_message
        assert(log_message("Test log message: %d", 123) == SUCCESS);

        // Test log_status
        assert(log_status(SUCCESS, "Test action") == SUCCESS);

        // Test config_init and load_config
        assert(config_init() == SUCCESS);
        assert(load_config() == SUCCESS);

        // Test create_item
        const char *test_file_path = "test_file.txt";
        const char *test_dir_path = "test_dir";
        assert(create_item(test_file_path, "test_file", false) == SUCCESS);
        assert(create_item(test_dir_path, "test_dir", true) == SUCCESS);

        // Test rename_item
        const char *renamed_file_path = "renamed_file.txt";
        assert(rename_item(test_file_path, renamed_file_path) == SUCCESS);

        // Test move_item
        const char *moved_file_path = "test_dir/renamed_file.txt";
        assert(move_item(renamed_file_path, moved_file_path) == SUCCESS);

        // Test change_item_permission
        assert(change_item_permission(moved_file_path, "0644") == SUCCESS);

        // Test clipboard operations
        assert(copy_item(moved_file_path) == SUCCESS);
        assert(cut_item(test_dir_path) == SUCCESS);
        assert(paste_item("pasted_file.txt", 0) == SUCCESS);

        // Test remove_item
        assert(remove_item(moved_file_path) == SUCCESS);
        if (access("pasted_file.txt", F_OK) == 0)
        {
                assert(remove_item("pasted_file.txt") == SUCCESS);
        }
        else
        {
                printf("File 'pasted_file.txt' does not exist.\n");
        }
        assert(remove_item(test_dir_path) == SUCCESS);

        printf("All advanced tests passed!\n");
        return 0;
}