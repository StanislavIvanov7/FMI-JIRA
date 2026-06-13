#include "UpcomingTasksCommand.h"
#include "App/AppData.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Utils/Date.h"
#include <iostream>
#include <vector>
#include <algorithm>

UpcomingTasksCommand::UpcomingTasksCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool UpcomingTasksCommand::requiresLogin() const { return true; }

void UpcomingTasksCommand::execute(const std::vector<std::string>& args, AppData& data) {
    Date today;
    std::vector<std::shared_ptr<Task>> upcoming;

    for (const auto& project : data.getProjects()) {
        for (const auto& task : project->getTasks()) {
            if (task->getDeadline() >= today) {
                upcoming.push_back(task);
            }
        }
    }

    std::sort(upcoming.begin(), upcoming.end(), [](const auto& a, const auto& b) {
        return a->getDeadline() < b->getDeadline();
        });

  
    if (upcoming.empty()) {
        std::cout << "No upcoming tasks found." << std::endl;
        return;
    }

    std::cout << "Upcoming tasks:" << std::endl;
  
    for (const auto& task : upcoming) {
        std::cout << " - [" << task->getFormattedId() << "] "
            << task->getTitle() << " (Deadline: " << task->getDeadline().toString() << ")" << std::endl;
    }
}