#include "ViewProfileCommand.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "App/AppData.h"
#include "Models/Users/User.h"
#include <iostream>

ViewProfileCommand::ViewProfileCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

void ViewProfileCommand::execute(const std::vector<std::string>& args, AppData& data) {

    if (!data.isUserLoggedIn()) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_MUST_BE_LOGGED_IN));
    }

    User* currentUser = data.getCurrentUser();
    if (currentUser) {
        currentUser->displayInfo(std::cout);
    }
}

bool ViewProfileCommand::requiresLogin() const {
    return true;
}