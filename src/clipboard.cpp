#include <vector>

#include "clipboard.hpp"
#include "filesystem.hpp"

namespace dirty
{
    namespace cb
    {
        clipboard::clipboard()
        {
            selected = 0;
        }

        log::type clipboard::add(const cb::item item, const bool is_cut)
        {
            // TODO: implement
        }
        
        log::type clipboard::paste(fs::directory dir, const int index)
        {
            // TODO: implement
        }
        
        log::type clipboard::clear(void)
        {
            // TODO: implement
        }
    }
}