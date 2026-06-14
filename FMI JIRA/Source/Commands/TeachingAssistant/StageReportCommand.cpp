#include "StageReportCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Users/User.h"
#include <iostream>

StageReportCommand::StageReportCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool StageReportCommand::requiresLogin() const { return true; }

void StageReportCommand::execute(const std::vector<std::string>& args, AppData& data) {
    UserRole role = data.getCurrentUser()->getRole();
    if (role != UserRole::TeachingAssistant && role != UserRole::Lecturer) {
        throw JiraInvalidArgumentException("This command is only available for Teaching Assistants and Lecturers.");
    }
    User* currentUser = data.getCurrentUser();
    bool foundAny = false;

    std::cout << "--- Stage Report for " << currentUser->getUsername() << " ---" << std::endl;

    for (const auto& project : data.getProjects()) {
        if (project->hasMember(currentUser->getUsername())) {
            foundAny = true;
            std::cout << "Project: " << project->getName() << std::endl;

            for (const auto& stage : project->getStages()) {
                std::cout << "  " << stage << std::endl;
            }
        }
    }

    if (!foundAny) {
        std::cout << "No projects or stages found." << std::endl;
    }
}