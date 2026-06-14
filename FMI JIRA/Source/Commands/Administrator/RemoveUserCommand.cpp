#include "RemoveUserCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Users/User.h"
#include <iostream>

RemoveUserCommand::RemoveUserCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool RemoveUserCommand::requiresLogin() const { return true; }

void RemoveUserCommand::execute(const std::vector<std::string>& args, AppData& data) {

    if (data.getCurrentUser()->getRole() != UserRole::Administrator) {
        throw JiraInvalidArgumentException("This command is only available for Administrators.");
    }

    if (args.size() != 1) {
        throw JiraInvalidArgumentException("Usage: remove-user <user>");
    }

    std::string usernameToRemove = args[0];
    User* currentUser = data.getCurrentUser();

    if (currentUser->getUsername() == usernameToRemove) {
        throw JiraInvalidArgumentException("Security violation: You cannot remove your own administrator account.");
    }

    bool success = data.removeUser(usernameToRemove);

    if (!success) {
        throw JiraInvalidArgumentException("User not found in the system.");
    }

    std::cout << "User [" << usernameToRemove << "] has been successfully removed from the system." << std::endl;
}