#include "CloseCommand.h"
#include "App/AppData.h"
#include <iostream>

CloseCommand::CloseCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

void CloseCommand::execute(const std::vector<std::string>& args, AppData& data) {
    std::cout << CommandConstants::MSG_EXITING << std::endl;

    data.stop();
}

bool CloseCommand::requiresLogin() const {
    return false;
}