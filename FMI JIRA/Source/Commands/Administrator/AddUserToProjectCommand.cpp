#include "AddUserToProjectCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Users/User.h"
#include <iostream>

AddUserToProjectCommand::AddUserToProjectCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool AddUserToProjectCommand::requiresLogin() const { return true; }

void AddUserToProjectCommand::execute(const std::vector<std::string>& args, AppData& data) {
    if (data.getCurrentUser()->getRole() != UserRole::Administrator) {
        throw JiraInvalidArgumentException("This command is only available for Administrators.");
    }

    if (args.size() != 2) {
        throw JiraInvalidArgumentException("Usage: add-user-to-project <user> <project>");
    }

    std::string username = args[0];
    std::string projectName = args[1];

    User* userToAdd = data.findUser(username);
    if (!userToAdd) {
        throw JiraInvalidArgumentException("User not found.");
    }

    Project* targetProject = nullptr;
    for (const auto& project : data.getProjects()) {
        if (project->getName() == projectName) {
            targetProject = project.get();
            break;
        }
    }

    if (!targetProject) {
        throw JiraInvalidArgumentException("Project not found.");
    }

    targetProject->addMember(userToAdd);

    std::cout << "User [" << username << "] added to project [" << projectName << "] successfully." << std::endl;
}