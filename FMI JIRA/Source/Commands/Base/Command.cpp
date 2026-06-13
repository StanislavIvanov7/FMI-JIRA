#include "Command.h"
#include "Exceptions/JiraInvalidArgumentException.h"

Command::Command(const std::string& name, const std::string& description)
    : name(name), description(description)
{
    if (name.empty()) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_COMMAND_NAME_EMPTY));
    }

    if (description.empty()) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_COMMAND_DESC_EMPTY));
    }
}


const std::string& Command::getName() const {
    return name;
}

const std::string& Command::getDescription() const {
    return description;
}


bool Command::requiresLogin() const {
    return true;
}
