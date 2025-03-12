#include "clipboard.h"

void clipboard_free(Clipboard *clipboard)
{
    free(clipboard->files);
}