#include "ListProjectsCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Users/User.h"
#include "Models/Project/Project.h"
#include <iostream>

ListProjectsCommand::ListProjectsCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool ListProjectsCommand::requiresLogin() const {
    return true;
}

void ListProjectsCommand::execute(const std::vector<std::string>& args, AppData& data) {
    if (!data.isUserLoggedIn()) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_NOT_LOGGED_IN));
    }

    if (data.getCurrentUser()->getRole() != UserRole::Student) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_ACCESS_DENIED));
    }
    const auto& projects = data.getProjects();

    if (projects.empty()) {
        std::cout << CommandConstants::MSG_NO_PROJECTS << std::endl;
        return;
    }

    std::cout << CommandConstants::MSG_AVAILABLE_PROJECTS << std::endl;
    for (const auto& project : projects) {
        if (project) {
            std::cout << *project << std::endl;
        }
    }
}