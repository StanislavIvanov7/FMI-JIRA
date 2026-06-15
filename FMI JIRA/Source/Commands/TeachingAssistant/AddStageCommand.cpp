#include "AddStageCommand.h"
#include "App/AppData.h"
#include "Models/Project/Project.h"
#include "Exceptions/JiraInvalidArgumentException.h"

AddStageCommand::AddStageCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
} 
void AddStageCommand::execute(const std::vector<std::string>& args, AppData& data) {
    if (args.size() < 2) {
        throw JiraInvalidArgumentException("Usage: add-stage <project_name> <stage_name>");
    }

    const std::string& projectName = args[0];
    const std::string& stageName = args[1];

    Project* proj = data.findProject(projectName);
    if (!proj) {
        throw JiraInvalidArgumentException(std::string(ProjectConstants::ERROR_PROJECT_NOT_FOUND));
    }

  
    if (proj->findStage(stageName) != nullptr) {
        throw JiraInvalidArgumentException(std::string(ProjectConstants::ERROR_STAGE_ALREADY_EXISTS));
    }

    
    proj->addStage(Stage(stageName));
    std::cout << "Stage '" << stageName << "' added to project '" << projectName << "' successfully." << std::endl;
}