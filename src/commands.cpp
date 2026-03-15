#include "commands.hpp"

namespace dirty
{
    namespace cmd
    {
        command::command(const std::string name, const std::string description, const std::string options)
        {
            this->name = name;
            this->description = description;
            this->options = options;
        }

        command::~command()
        {

        }

        log::type command::execute()
        {
            // TODO: implement
        }
    }
}