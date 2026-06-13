#include "ChangeStatusCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include "Utils/Enums/TaskStatus.h"
#include <iostream>

ChangeStatusCommand::ChangeStatusCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool ChangeStatusCommand::requiresLogin() const {
    return true;
}

void ChangeStatusCommand::execute(const std::vector<std::string>& args, AppData& data) {
    if (args.size() != 2) {
        throw JiraInvalidArgumentException(std::string(CommandConstants::ERR_INVALID_ARGS));
    }

    std::string taskIdStr = args[0];
    std::string statusStr = args[1];

    
    std::shared_ptr<Task> foundTask = nullptr;
    for (const auto& project : data.getProjects()) {
        auto task = project->findTaskByFormattedId(taskIdStr);
        if (task) {
            foundTask = task;
            break;
        }
    }

    if (!foundTask) {
        throw JiraInvalidArgumentException(std::string(ProjectConstants::ERROR_TASK_NOT_FOUND));
    }

   
    TaskStatus newStatus = parseTaskStatus(statusStr);

    foundTask->setStatus(newStatus, data.getCurrentUser(), Date());

    std::cout << "Task " << foundTask->getFormattedId() << " changed to " << statusStr << "." << std::endl;
}