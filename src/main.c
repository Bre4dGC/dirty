#include <curses.h>
#include "operations.h"
#include "ui.h"

int main()
{
    init_ui();
    
    cleanup_ui();
    return 0;    
}