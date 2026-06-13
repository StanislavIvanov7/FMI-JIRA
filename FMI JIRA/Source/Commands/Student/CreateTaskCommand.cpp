#include "CreateTaskCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include "Utils/Enums/TaskType.h"
#include "Utils/Enums/TaskPriority.h"
#include <iostream>

CreateTaskCommand::CreateTaskCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool CreateTaskCommand::requiresLogin() const {
    return true;
}

void CreateTaskCommand::execute(const std::vector<std::string>& args, AppData& data) {
    
    if (args.size() != 3) {
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

 
    TaskType type = parseTaskType(args[1]);
    TaskPriority priority = parseTaskPriority(args[2]);

    std::string title;
    std::string description;

    std::cout << "Enter task title: ";
    std::getline(std::cin >> std::ws, title);

    std::cout << "Enter task description: ";
    std::getline(std::cin, description);

  
    if (title.empty()) {
        throw JiraInvalidArgumentException(std::string(TaskConstants::ERROR_EMPTY_TITLE));
    }
    if (description.empty()) {
        throw JiraInvalidArgumentException(std::string(TaskConstants::ERROR_EMPTY_DESCRIPTION));
    }

    auto newTask = std::make_shared<Task>(title, description, type, priority, Date());
    project->addTask(newTask);

    std::cout << "Successfully created task " << newTask->getFormattedId()
        << " in project: " << project->getName() << std::endl;
}