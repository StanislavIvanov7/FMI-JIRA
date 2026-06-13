#include "SearchTasksCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include <iostream>
#include <algorithm>

SearchTasksCommand::SearchTasksCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool SearchTasksCommand::requiresLogin() const { return true; }

void SearchTasksCommand::execute(const std::vector<std::string>& args, AppData& data) {
    if (args.size() != 1) {
        throw JiraInvalidArgumentException("Usage: search-tasks <keyword>");
    }

    std::string keyword = args[0];
    bool foundAny = false;

    std::cout << "Searching for tasks containing: '" << keyword << "'" << std::endl;

    for (const auto& project : data.getProjects()) {
        for (const auto& task : project->getTasks()) {
            if (task->getTitle().find(keyword) != std::string::npos) {
                std::cout << " - [" << task->getFormattedId() << "] " << task->getTitle() << std::endl;
                foundAny = true;
            }
        }
    }

    if (!foundAny) {
        std::cout << "No tasks found matching the keyword." << std::endl;
    }
}