#include "ApproveTaskCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include "Utils/Date.h"
#include <iostream>

ApproveTaskCommand::ApproveTaskCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool ApproveTaskCommand::requiresLogin() const { return true; }

void ApproveTaskCommand::execute(const std::vector<std::string>& args, AppData& data) {
    
    UserRole role = data.getCurrentUser()->getRole();
    if (role != UserRole::TeachingAssistant && role != UserRole::Lecturer && role != UserRole::Administrator) {
        throw JiraInvalidArgumentException("This command is only available for Teaching Assistants and Lecturers.");
    }
  

    if (args.size() != 1) {
        throw JiraInvalidArgumentException("Usage: approve-task <task_id>");
    }

    std::string taskId = args[0];
    User* currentUser = data.getCurrentUser();
    bool taskFound = false;

    for (const auto& project : data.getProjects()) {
      
        if (project->hasMember(currentUser->getUsername())) {

            for (const auto& task : project->getTasks()) {
                if (task->getFormattedId() == taskId) {
                    task->setApproved(true, currentUser, Date());

                    std::cout << "Task [" << taskId << "] has been approved." << std::endl;
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