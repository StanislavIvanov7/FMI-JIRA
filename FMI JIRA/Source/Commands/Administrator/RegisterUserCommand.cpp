#include "RegisterUserCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Users/User.h"
#include "Factories/UserFactory.h"
#include <iostream>
#include <memory>

RegisterUserCommand::RegisterUserCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool RegisterUserCommand::requiresLogin() const {
    return true;
}

void RegisterUserCommand::execute(const std::vector<std::string>& args, AppData& data) {
    if (data.getCurrentUser()->getRole() != UserRole::Administrator) {
        throw JiraInvalidArgumentException("Security error: This command is only available for Administrators.");
    }

   
    if (args.size() != 3) {
        throw JiraInvalidArgumentException("Usage: register <username> <password> <role>");
    }

    std::string username = args[0];
    std::string password = args[1];
    std::string roleStr = args[2];

    if (data.findUser(username) != nullptr) {
        throw JiraInvalidArgumentException("Registration failed: User with this username already exists.");
    }

    UserRole role;
    try {
        role = parseRole(roleStr);
    }
    catch (const std::exception&) {
        throw JiraInvalidArgumentException("Registration failed: Invalid role specified. Valid roles are: Student, TeachingAssistant, Administrator.");
    }

    
    auto newUser = UserFactory::createUser(username, password, role);
    data.addUser(std::move(newUser));

    std::cout << "[System] User '" << username << "' registered successfully with role: " << roleStr << "." << std::endl;
}