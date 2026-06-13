#include "AddTagCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include "Utils/Date.h"
#include <iostream>

AddTagCommand::AddTagCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool AddTagCommand::requiresLogin() const { return true; }

void AddTagCommand::execute(const std::vector<std::string>& args, AppData& data) {

    if (data.getCurrentUser()->getRole() != UserRole::Student) {
        throw JiraInvalidArgumentException("This command is only available for students.");
    }

    if (args.size() != 2) {
        throw JiraInvalidArgumentException("Usage: add-tag <task_id> <tag>");
    }

    std::string taskId = args[0];
    std::string tag = args[1];
    User* currentUser = data.getCurrentUser();
    bool taskFound = false;

  
    for (const auto& project : data.getProjects()) {
        if (project->hasMember(currentUser->getUsername())) {

            for (const auto& task : project->getTasks()) {
                if (task->getFormattedId() == taskId) {

                    task->addTag(tag, currentUser, Date());

                    std::cout << "Tag '" << tag << "' added to task [" << taskId << "]." << std::endl;
                    taskFound = true;
                    return;
                }
            }
        }
    }

    if (!taskFound) {
        std::cout << "Task with ID '" << taskId << "' not found or access denied." << std::endl;
    }
}