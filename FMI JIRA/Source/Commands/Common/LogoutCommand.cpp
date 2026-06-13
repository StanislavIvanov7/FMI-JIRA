#include "LogoutCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include <iostream>

LogoutCommand::LogoutCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

void LogoutCommand::execute(const std::vector<std::string>& args, AppData& data) {
    if (!data.isUserLoggedIn()) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_NOT_LOGGED_IN));
    }

    data.logout();

    std::cout << CommandConstants::MSG_SUCCESS_LOGOUT << std::endl;
}
bool LogoutCommand::requiresLogin() const {
    return true;
}