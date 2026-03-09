#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/color.hpp>

#include <dirent.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "ui.hpp"
#include "logs.hpp"
#include "filesystem.hpp"
#include "clipboard.hpp"
#include "commands.hpp"

/* description of ui
left main section - file browser with directory path on top
right main section - content of selected item (directory, text file, image) with item name on top
right additional section - item info, recently visited items, clipboard
bottom section - single command line
*/

namespace dirty
{
    namespace ui
    {

    }
}