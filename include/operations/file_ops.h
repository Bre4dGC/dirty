#include <sys/stat.h>
#include <stdbool.h>

typedef struct {
    char *name;
    char *mode;
    bool is_cut;
    struct stat stat;
} file_t;

void create_file(char *path, char *name);
void rename_file(file_t *file, char *new_name);
void delete_file(file_t *file);