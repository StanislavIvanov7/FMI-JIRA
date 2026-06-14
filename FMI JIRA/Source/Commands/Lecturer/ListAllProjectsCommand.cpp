#include "ListAllProjectsCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Users/User.h"
#include <iostream>

ListAllProjectsCommand::ListAllProjectsCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool ListAllProjectsCommand::requiresLogin() const {
    return true;
}

void ListAllProjectsCommand::execute(const std::vector<std::string>& args, AppData& data) {
  
    UserRole role = data.getCurrentUser()->getRole();
    if (role != UserRole::Lecturer) {
        throw JiraInvalidArgumentException("Security error: This command is only available for Lecturers");
    }


    if (!args.empty()) {
        throw JiraInvalidArgumentException("Usage: list-all-projects (does not accept any arguments)");
    }

    const auto& projects = data.getProjects();


    if (projects.empty()) {
        std::cout << "[System] No projects found in the system." << std::endl;
        return;
    }


    std::cout << "=== All Projects ===" << std::endl;
    for (const auto& projectPtr : projects) {
        if (projectPtr) {
     
            std::cout << *projectPtr << std::endl;
            std::cout << "-----------------------------------" << std::endl;
        }
    }
}