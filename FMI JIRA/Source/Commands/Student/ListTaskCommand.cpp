#include "ListTaskCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include <iostream>

ListTasksCommand::ListTasksCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool ListTasksCommand::requiresLogin() const {
    return true;
}

void ListTasksCommand::execute(const std::vector<std::string>& args, AppData& data) {
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

    const auto& tasks = project->getTasks();
    if (tasks.empty()) {
        std::cout << ProjectConstants::MSG_NO_TASKS << project->getName() << std::endl;
        return;
    }

    std::cout << ProjectConstants::MSG_PROJECT_TASKS << project->getName() << ":" << std::endl;
    for (const auto& task : tasks) {
        if (task) {
            std::cout << *task << std::endl;
        }
    }
}