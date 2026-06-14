#include "StudentReportCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include "Models/Users/Student.h"
#include <iostream>

StudentReportCommand::StudentReportCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool StudentReportCommand::requiresLogin() const {
    return true;
}

void StudentReportCommand::execute(const std::vector<std::string>& args, AppData& data) {

    UserRole role = data.getCurrentUser()->getRole();
    if (role != UserRole::Lecturer) {
        throw JiraInvalidArgumentException("Security error: Only Lecturers can generate reports.");
    }

    
    if (args.size() != 1) {
        throw JiraInvalidArgumentException("Usage: student-report <student_name>");
    }

    std::string studentName = args[0];

    const User* targetUser = data.findUser(studentName);
    if (!targetUser) {
        throw JiraInvalidArgumentException("User '" + studentName + "' not found.");
    }

    const Student* student = dynamic_cast<const Student*>(targetUser);
    if (!student) {
        throw JiraInvalidArgumentException("User '" + studentName + "' is not a student.");
    }

    
    std::cout << "=== Report for Student: " << studentName << " ===" << std::endl;

    
    student->displayInfo(std::cout);
    std::cout << "\n\n--- Assigned Tasks Detail ---" << std::endl;

    bool foundTasks = false;
    const auto& projects = data.getProjects();

    for (const auto& project : projects) {
        if (!project) continue;

        for (const auto& task : project->getTasks()) {
            if (task && task->getAssignee() == student) {
                foundTasks = true;

                std::cout << "Project: " << project->getName() << std::endl;
                
                std::cout << *task << std::endl;
                std::cout << "-----------------------------------" << std::endl;
            }
        }
    }

    if (!foundTasks) {
        std::cout << "[System] No tasks currently assigned to this student." << std::endl;
    }
}