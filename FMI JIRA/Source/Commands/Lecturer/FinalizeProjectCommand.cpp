#include "FinalizeProjectCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Users/User.h"
#include <iostream>

FinalizeProjectCommand::FinalizeProjectCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool FinalizeProjectCommand::requiresLogin() const { return true; }

void FinalizeProjectCommand::execute(const std::vector<std::string>& args, AppData& data) {
   
    UserRole role = data.getCurrentUser()->getRole();
    if (role != UserRole::Lecturer) {
        throw JiraInvalidArgumentException("Security error: Only Lecturers can finalize projects.");
    }

    if (args.size() != 1) {
        throw JiraInvalidArgumentException("Usage: finalize-project <project_name>");
    }

    std::string projectName = args[0];

    Project* targetProject = nullptr;
    for (const auto& project : data.getProjects()) {
        if (project && project->getName() == projectName) {
            targetProject = project.get();
            break;
        }
    }

    if (!targetProject) {
        throw JiraInvalidArgumentException("Project '" + projectName + "' not found.");
    }

    if (targetProject->getStatus() == ProjectStatus::Finished) {
        throw JiraInvalidArgumentException("Project '" + projectName + "' is already finalized.");
    }

    targetProject->setStatus(ProjectStatus::Finished);

    std::cout << "[System] Project '" << projectName << "' has been finalized successfully." << std::endl;
}