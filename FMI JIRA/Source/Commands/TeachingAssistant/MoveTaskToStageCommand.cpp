#include "MoveTaskToStageCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Users/User.h"
#include <iostream>

MoveTaskToStageCommand::MoveTaskToStageCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool MoveTaskToStageCommand::requiresLogin() const { return true; }

void MoveTaskToStageCommand::execute(const std::vector<std::string>& args, AppData& data) {
    UserRole role = data.getCurrentUser()->getRole();
    if (role != UserRole::TeachingAssistant && role != UserRole::Lecturer && role != UserRole::Administrator) {
        throw JiraInvalidArgumentException("This command is only available for Teaching Assistants and Lecturers.");
    }
    if (args.size() != 2) {
        throw JiraInvalidArgumentException("Usage: move-task-to-stage <task_id> <stage_name>");
    }

    std::string taskIdStr = args[0];
    std::string stageName = args[1];
    User* currentUser = data.getCurrentUser();
    size_t taskId = std::stoul(taskIdStr.substr(taskIdStr.find('-') + 1));

    bool taskMoved = false;

    for (const auto& project : data.getProjects()) {
        if (project->hasMember(currentUser->getUsername())) {

           
            Stage* newStage = project->findStage(stageName);
            if (!newStage) continue; 

         
            std::shared_ptr<Task> taskToMove = nullptr;
            Stage* oldStage = nullptr;

            for (auto& stage : project->getStages()) {
                auto task = stage.findTask(taskId);
                if (task) {
                    taskToMove = task;
                    oldStage = &stage;
                    break;
                }
            }

            if (!taskToMove) {
                taskToMove = project->findTask(taskId);
            }

           
            if (taskToMove) {
                if (oldStage) {
                    oldStage->removeTask(taskId);
                }
                newStage->addTask(taskToMove);

                std::cout << "Task [" << taskIdStr << "] moved to stage [" << stageName << "]." << std::endl;
                taskMoved = true;
                return;
            }
        }
    }

    if (!taskMoved) {
        throw JiraInvalidArgumentException("Task not found or target stage does not exist.");
    }
}