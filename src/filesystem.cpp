#include "filesystem.hpp"

namespace dirty
{
    namespace fs
    {
        directory::directory(const std::string path)
        {
            this->path = path;
        }
        
        directory::~directory()
        {
            
        }

        log::type directory::open(void)
        {
            // TODO: implement
        }

        log::type directory::create(const std::string name, const bool is_dir)
        {
            // TODO: implement
        }

        log::type directory::rename(const std::string old_name, const std::string new_name)
        {
            // TODO: implement
        }

        log::type directory::move(const std::string dest)
        {
            // TODO: implement
        }

        log::type directory::copy(const std::string dest)
        {
            // TODO: implement
        }

        log::type directory::chmod(const fs::perm perm)
        {
            // TODO: implement
        }

        log::type directory::remove(void)
        {
            // TODO: implement
        }
    }
}