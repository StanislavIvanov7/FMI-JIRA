#include "GradeTaskCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include <iostream>
#include <stdexcept>

GradeTaskCommand::GradeTaskCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool GradeTaskCommand::requiresLogin() const { return true; }

void GradeTaskCommand::execute(const std::vector<std::string>& args, AppData& data) {
  
    UserRole role = data.getCurrentUser()->getRole();
    if (role != UserRole::Lecturer) {
        throw JiraInvalidArgumentException("Security error: Only Lecturers can grade tasks.");
    }

    if (args.size() != 2) {
        throw JiraInvalidArgumentException("Usage: grade-task <task_id> <grade>");
    }

    std::string taskId = args[0];
    double grade;

  
    try {
        grade = std::stod(args[1]);
    }
    catch (...) {
        throw JiraInvalidArgumentException("Invalid grade format. Please enter a number.");
    }

    if (grade < 2.0 || grade > 6.0) {
        throw JiraInvalidArgumentException("Grade must be between 2.0 and 6.0.");
    }

    
    Task* targetTask = nullptr;
    for (const auto& project : data.getProjects()) {
        for (const auto& task : project->getTasks()) {
          
            if (task->getFormattedId() == taskId || std::to_string(task->getId()) == taskId) {
                targetTask = task.get();
                break;
            }
        }
        if (targetTask) break;
    }

    if (!targetTask) {
        throw JiraInvalidArgumentException("Task with ID [" + taskId + "] not found.");
    }

    
    targetTask->setGrade(grade, data.getCurrentUser(), Date());

    std::cout << "[System] Task [" << taskId << "] graded successfully with " << grade << "." << std::endl;
}