#include "ReviewTaskCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include "Utils/Date.h"
#include <iostream>

ReviewTaskCommand::ReviewTaskCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool ReviewTaskCommand::requiresLogin() const {
    return true;
}

void ReviewTaskCommand::execute(const std::vector<std::string>& args, AppData& data) {
    
    UserRole role = data.getCurrentUser()->getRole();
    if (role != UserRole::TeachingAssistant && role != UserRole::Lecturer) {
        throw JiraInvalidArgumentException("This command is only available for Teaching Assistants and Lecturers.");
    }

    if (args.size() != 1) {
        throw JiraInvalidArgumentException("Usage: review-task <task_id>");
    }

    const std::string& taskId = args[0];
    User* currentUser = data.getCurrentUser();
    bool taskFound = false;

   
    for (const auto& project : data.getProjects()) {
        if (project->hasMember(currentUser->getUsername())) {

            for (const auto& task : project->getTasks()) {
                if (task->getFormattedId() == taskId) {

                    
                    task->setStatus(TaskStatus::InReview, currentUser, Date());

                    std::cout << "Task [" << taskId << "] status set to 'Review'." << std::endl;
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