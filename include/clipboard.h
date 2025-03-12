#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <stdlib.h>
#include "file_ops.h"

#define CLIPBOARD_BUFF 6

typedef struct {
    int elem_count;
    FileEntry files[CLIPBOARD_BUFF];
} Clipboard;

void clipboard_free(Clipboard *clipboard);

#endif