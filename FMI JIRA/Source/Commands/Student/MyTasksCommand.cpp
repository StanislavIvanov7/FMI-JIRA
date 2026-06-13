#include "MyTasksCommand.h"
#include "App/AppData.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include <iostream>

MyTasksCommand::MyTasksCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool MyTasksCommand::requiresLogin() const {
    return true;
}

void MyTasksCommand::execute(const std::vector<std::string>& args, AppData& data) {
    User* currentUser = data.getCurrentUser();
    bool foundAny = false;

    std::cout << "Tasks assigned to " << currentUser->getUsername() << ":" << std::endl;

    for (const auto& project : data.getProjects()) {
        for (const auto& task : project->getTasks()) {

            if (task->getAssignee() != nullptr &&
                task->getAssignee()->getUsername() == currentUser->getUsername()) {

                std::cout << " - [" << task->getFormattedId() << "] " << task->getTitle() << std::endl;
                foundAny = true;
            }
        }
    }

    if (!foundAny) {
        std::cout << "No tasks assigned to you." << std::endl;
    }
}