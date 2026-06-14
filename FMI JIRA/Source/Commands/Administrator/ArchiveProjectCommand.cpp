#include "ArchiveProjectCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Users/User.h"
#include <iostream>

ArchiveProjectCommand::ArchiveProjectCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool ArchiveProjectCommand::requiresLogin() const { return true; }

void ArchiveProjectCommand::execute(const std::vector<std::string>& args, AppData& data) {
    if (data.getCurrentUser()->getRole() != UserRole::Administrator) {
        throw JiraInvalidArgumentException("This command is only available for Administrators.");
    }

    if (args.size() != 1) {
        throw JiraInvalidArgumentException("Usage: archive-project <name>");
    }

    std::string projectName = args[0];

    for (const auto& project : data.getProjects()) {
        if (project->getName() == projectName) {

            if (project->getStatus() == ProjectStatus::Finished) {
                throw JiraInvalidArgumentException("Project is already finished/archived.");
            }

            project->archive();

            std::cout << "Project [" << projectName << "] archived successfully." << std::endl;
            return;
        }
    }

    throw JiraInvalidArgumentException("Project with that name does not exist.");
}