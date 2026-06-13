#include "FilterTasksCommand.h"
#include "../../App/AppData.h"
#include "../../Exceptions/JiraInvalidArgumentException.h"
#include "../../Models/Project/Project.h"
#include "../../Models/Task/Task.h"
#include "../../Utils/Enums/TaskStatus.h"
#include "../../Utils/Enums/TaskPriority.h"
#include "../../Utils/Enums/TaskType.h"     
#include "../../Models/Users/User.h" 
#include <iostream>

FilterTasksCommand::FilterTasksCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool FilterTasksCommand::requiresLogin() const { return true; }

void FilterTasksCommand::execute(const std::vector<std::string>& args, AppData& data) {
    if (args.size() != 1) {
        throw JiraInvalidArgumentException("Usage: filter-tasks <criteria>");
    }

    std::string criteria = args[0];
    User* currentUser = data.getCurrentUser();
    bool foundAny = false;

    for (const auto& project : data.getProjects()) {
        if (project->hasMember(currentUser->getUsername())) {

            for (const auto& task : project->getTasks()) {

                
                if (toString(task->getStatus()) == criteria ||
                    toString(task->getPriority()) == criteria ||
                    toString(task->getType()) == criteria) {

                    std::cout << " - [" << task->getFormattedId() << "] " << task->getTitle() << std::endl;
                    foundAny = true;
                }
            }
        }
    }

    if (!foundAny) {
        std::cout << "No tasks found matching the criteria: " << criteria << std::endl;
    }
}