#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

#include "ui.h"
#include "fs.h"
#include "logs.h"
#include "config.h"
#include "clipboard.h"
#include "commands.h"
#include "hotkeys.h"

void dirty_init();
void dirty_loop();
void dirty_cleanup();

int main()
{
    dirty_init();

    assert(log_report(REPORT_SUCCESS, "Test action") == REPORT_SUCCESS);

    assert(conf_load() == REPORT_SUCCESS);

    const char *test_file_path = "test_file.txt";
    const char *test_dir_path = "test_dir";
    assert(fs_create(test_file_path, "test_file", false) == REPORT_SUCCESS);
    assert(fs_create(test_dir_path, "test_dir", true) == REPORT_SUCCESS);

    const char *renamed_file_path = "renamed_file.txt";
    assert(fs_rename(test_file_path, renamed_file_path) == REPORT_SUCCESS);

    const char *moved_file_path = "test_dir/renamed_file.txt";
    assert(fs_move(renamed_file_path, moved_file_path) == REPORT_SUCCESS);

    assert(fs_chmod(moved_file_path, FS_MOD_EXECUTE) == REPORT_SUCCESS);

    assert(cb_copy(moved_file_path) == REPORT_SUCCESS);
    assert(cb_cut(test_dir_path) == REPORT_SUCCESS);
    // assert(cb_paste("pasted_file.txt", 0) == REPORT_SUCCESS);

    assert(fs_remove(moved_file_path) == REPORT_SUCCESS);
    assert(fs_remove(test_dir_path) == REPORT_SUCCESS);

    printf("All advanced tests passed!\n");

    dirty_cleanup();
    return 0;
}

void dirty_init()
{
    log_init();
    conf_init();
    hk_init();
    ui_init();
}

void dirty_loop()
{
}

void dirty_cleanup()
{
    ui_cleanup();
    hk_cleanup();
    conf_cleanup();
    log_cleanup();
}