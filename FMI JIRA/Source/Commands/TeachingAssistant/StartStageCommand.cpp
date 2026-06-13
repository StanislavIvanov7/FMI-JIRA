#include "StartStageCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Users/User.h"
#include "Utils/Date.h"
#include <iostream>

StartStageCommand::StartStageCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool StartStageCommand::requiresLogin() const { return true; }

void StartStageCommand::execute(const std::vector<std::string>& args, AppData& data) {
   
    if (data.getCurrentUser()->getRole() != UserRole::TeachingAssistant) {
        throw JiraInvalidArgumentException("This command is only available for Teaching Assistants.");
    }

    if (args.size() != 1) {
        throw JiraInvalidArgumentException("Usage: start-stage <stage_name>");
    }

    std::string stageName = args[0];
    User* currentUser = data.getCurrentUser();
    bool stageFound = false;

    for (const auto& project : data.getProjects()) {
       
        if (project->hasMember(currentUser->getUsername())) {

            
            for (auto& stage : project->getStages()) {
                if (stage.getName() == stageName) {
                    
                    stage.start(Date());

                    std::cout << "Stage [" << stageName << "] has been started." << std::endl;
                    stageFound = true;
                    return;
                }
            }
        }
    }

    if (!stageFound) {
        std::cout << "Stage '" << stageName << "' not found or access denied." << std::endl;
    }
}