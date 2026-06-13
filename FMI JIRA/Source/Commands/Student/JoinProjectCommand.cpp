#include "JoinProjectCommand.h"
#include "Models/Project/Project.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "App/AppData.h"
#include "Models/Users/User.h"
#include <iostream>

JoinProjectCommand::JoinProjectCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool JoinProjectCommand::requiresLogin() const {
    return true;
}

void JoinProjectCommand::execute(const std::vector<std::string>& args, AppData& data) {
    if (args.size() != 1) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_INVALID_ARGS));
    }

    if (!data.isUserLoggedIn()) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_NOT_LOGGED_IN));
    }

    if (data.getCurrentUser()->getRole() != UserRole::Student) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_ACCESS_DENIED));
    }

    Project* project = data.findProject(args[0]);
    if (!project) {
 
        throw JiraInvalidArgumentException(std::string(ProjectConstants::ERROR_PROJECT_NOT_FOUND));
    }

    if (project->hasMember(data.getCurrentUser()->getUsername())) {
        throw JiraInvalidArgumentException(std::string(ProjectConstants::ERROR_MEMBER_ALREADY_EXISTS));
    }

    project->addMember(data.getCurrentUser());

    std::cout << "Successfully joined project: " << project->getName() << std::endl;
}