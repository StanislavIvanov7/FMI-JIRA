#include "CreateProjectCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Users/User.h"
#include <iostream>
#include <memory>

CreateProjectCommand::CreateProjectCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool CreateProjectCommand::requiresLogin() const { return true; }

void CreateProjectCommand::execute(const std::vector<std::string>& args, AppData& data) {

    if (data.getCurrentUser()->getRole() != UserRole::Administrator) {
        throw JiraInvalidArgumentException("This command is only available for Administrators.");
    }

    if (args.size() != 1) {
        throw JiraInvalidArgumentException("Usage: create-project <name>");
    }

    std::string projectName = args[0];

    for (const auto& project : data.getProjects()) {
        if (project->getName() == projectName) {
            throw JiraInvalidArgumentException("Project with this name already exists.");
        }
    }

    auto newProject = std::make_shared<Project>(projectName);
    data.addProject(newProject);

    std::cout << "Project [" << projectName << "] created successfully." << std::endl;
}