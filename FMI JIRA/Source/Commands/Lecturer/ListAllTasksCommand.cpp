#include "ListAllTasksCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include <iostream>

ListAllTasksCommand::ListAllTasksCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool ListAllTasksCommand::requiresLogin() const {
    return true;
}

void ListAllTasksCommand::execute(const std::vector<std::string>& args, AppData& data) {
    
    UserRole role = data.getCurrentUser()->getRole();
    if (role != UserRole::Lecturer) {
        throw JiraInvalidArgumentException("Security error: This command is only available for Lecturers");
    }

  
    if (!args.empty()) {
        throw JiraInvalidArgumentException("Usage: list-all-tasks (does not accept any arguments)");
    }

    const auto& projects = data.getProjects();
    if (projects.empty()) {
        std::cout << "[System] No projects found, hence no tasks exist." << std::endl;
        return;
    }

    std::cout << "=== All Tasks in the System ===" << std::endl;
    bool anyTasksFound = false;

   
    for (const auto& projectPtr : projects) {
        if (!projectPtr) continue;

        const auto& tasks = projectPtr->getTasks();
        if (tasks.empty()) continue;

        anyTasksFound = true;
        std::cout << "\nProject: " << projectPtr->getName() << "\n";
        std::cout << "-----------------------------------" << std::endl;

       
        for (const auto& taskPtr : tasks) {
            if (taskPtr) {
               
                std::cout << *taskPtr << std::endl;
            }
        }
    }

    if (!anyTasksFound) {
        std::cout << "[System] There are projects, but no tasks have been created yet." << std::endl;
    }
}