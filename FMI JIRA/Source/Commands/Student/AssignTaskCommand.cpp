#include "AssignTaskCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include <iostream>

AssignTaskCommand::AssignTaskCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool AssignTaskCommand::requiresLogin() const {
    return true;
}

void AssignTaskCommand::execute(const std::vector<std::string>& args, AppData& data) {
   
    if (args.size() != 1) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_INVALID_ARGS));
    }

    std::string taskIdStr = args[0];
    User* currentUser = data.getCurrentUser();
    std::shared_ptr<Task> foundTask = nullptr;
    Project* foundProject = nullptr;

   
    for (const auto& project : data.getProjects()) {
        auto task = project->findTaskByFormattedId(taskIdStr);
        if (task) {
            foundTask = task;
            foundProject = project.get();
            break;
        }
    }

    if (!foundTask) {
        throw JiraInvalidArgumentException(std::string(ProjectConstants::ERROR_TASK_NOT_FOUND));
    }

  
    if (!foundProject->hasMember(currentUser->getUsername())) {
        throw JiraInvalidArgumentException(std::string(ProjectConstants::ERROR_ACCESS_DENIED));
    }

    foundTask->setAssignee(currentUser, currentUser, Date());

    std::cout << "Task " << foundTask->getFormattedId() << " assigned to you." << std::endl;
}