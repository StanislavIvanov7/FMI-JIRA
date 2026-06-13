#include "LoginCommand.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Users/User.h"
#include "App/AppData.h"
#include <iostream>

LoginCommand::LoginCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

void LoginCommand::execute(const std::vector<std::string>& args, AppData& data) {
    if (args.size() != 2) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_INVALID_ARGS));
    }

    if (data.isUserLoggedIn()) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_ALREADY_LOGGED_IN));
    }

    User* user = data.findUser(args[0]);
    if (!user || !user->checkPassword(args[1])) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_INVALID_CREDENTIALS));
    }

    data.setCurrentUser(user);
    std::cout << CommandConstants::MSG_SUCCESS_LOGIN << std::endl;
}
bool LoginCommand::requiresLogin() const {
    return false;
}