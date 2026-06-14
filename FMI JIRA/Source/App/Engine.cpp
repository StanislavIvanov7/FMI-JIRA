#include "Engine.h"
#include <iostream>
#include <sstream>

#include "Commands/Administrator/SaveCommand.h"
#include "Commands/Administrator/LoadCommand.h"
#include "Commands/Administrator/AddUserToProjectCommand.h"
#include "Commands/Administrator/ArchiveProjectCommand.h"
#include "Commands/Administrator/CreateProjectCommand.h"
#include "Commands/Administrator/RegisterUserCommand.h"
#include "Commands/Administrator/RemoveUserCommand.h"

#include "Commands/Common/CloseCommand.h"
#include "Commands/Common/HelpCommand.h"
#include "Commands/Common/LoginCommand.h"
#include "Commands/Common/LogoutCommand.h"
#include "Commands/Common/ViewProfileCommand.h"

#include "Commands/Lecturer/FinalizeProjectCommand.h"
#include "Commands/Lecturer/GradeTaskCommand.h"
#include "Commands/Lecturer/ListAllProjectsCommand.h"
#include "Commands/Lecturer/ListAllTasksCommand.h"
#include "Commands/Lecturer/StudentReportCommand.h"

#include "Commands/Student/AddCommentCommand.h"
#include "Commands/Student/AddTagCommand.h"
#include "Commands/Student/AssignTaskCommand.h"
#include "Commands/Student/ChangeStatusCommand.h"
#include "Commands/Student/CreateTaskCommand.h"
#include "Commands/Student/FilterTasksCommand.h"
#include "Commands/Student/JoinProjectCommand.h"
#include "Commands/Student/ListProjectsCommand.h"
#include "Commands/Student/ListTaskCommand.h"
#include "Commands/Student/MyTasksCommand.h"
#include "Commands/Student/SearchTasksCommand.h"
#include "Commands/Student/UpcomingTasksCommand.h"

#include "Commands/TeachingAssistant/ApproveTaskCommand.h"
#include "Commands/TeachingAssistant/FinishStageCommand.h"
#include "Commands/TeachingAssistant/MoveTaskToStageCommand.h"
#include "Commands/TeachingAssistant/ReviewTaskCommand.h"
#include "Commands/TeachingAssistant/StageReportCommand.h"
#include "Commands/TeachingAssistant/StartStageCommand.h"


Engine::Engine(AppData& data) : data(data) {
   
    commands.push_back(std::make_unique<SaveCommand>());
    commands.push_back(std::make_unique<LoadCommand>());
    commands.push_back(std::make_unique<AddUserToProjectCommand>());
    commands.push_back(std::make_unique<ArchiveProjectCommand>());
    commands.push_back(std::make_unique<CreateProjectCommand>());
    commands.push_back(std::make_unique<RegisterUserCommand>());
    commands.push_back(std::make_unique<RemoveUserCommand>());

    commands.push_back(std::make_unique<CloseCommand>());
    commands.push_back(std::make_unique<HelpCommand>());
    commands.push_back(std::make_unique<LoginCommand>());
    commands.push_back(std::make_unique<LogoutCommand>());
    commands.push_back(std::make_unique<ViewProfileCommand>());

    commands.push_back(std::make_unique<FinalizeProjectCommand>());
    commands.push_back(std::make_unique<GradeTaskCommand>());
    commands.push_back(std::make_unique<ListAllProjectsCommand>());
    commands.push_back(std::make_unique<ListAllTasksCommand>());
    commands.push_back(std::make_unique<StudentReportCommand>());

    commands.push_back(std::make_unique<AddCommentCommand>());
    commands.push_back(std::make_unique<AddTagCommand>());
    commands.push_back(std::make_unique<AssignTaskCommand>());
    commands.push_back(std::make_unique<ChangeStatusCommand>());
    commands.push_back(std::make_unique<CreateTaskCommand>());
    commands.push_back(std::make_unique<FilterTasksCommand>());
    commands.push_back(std::make_unique<JoinProjectCommand>());
    commands.push_back(std::make_unique<ListProjectsCommand>());
    commands.push_back(std::make_unique<ListTasksCommand>());
    commands.push_back(std::make_unique<MyTasksCommand>());
    commands.push_back(std::make_unique<SearchTasksCommand>());
    commands.push_back(std::make_unique<UpcomingTasksCommand>());

    commands.push_back(std::make_unique<ApproveTaskCommand>());
    commands.push_back(std::make_unique<FinishStageCommand>());
    commands.push_back(std::make_unique<MoveTaskToStageCommand>());
    commands.push_back(std::make_unique<ReviewTaskCommand>());
    commands.push_back(std::make_unique<StageReportCommand>());
    commands.push_back(std::make_unique<StartStageCommand>());
    
}

void Engine::run() {
    std::string input;
    std::cout << "FMI JIRA - Project Management System\n";
    std::cout << "Type 'help' for a list of commands.\n\n";

    while (data.isRunning()) {
        std::cout << "> ";
        std::getline(std::cin, input);

        try {
            processCommand(input);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

void Engine::processCommand(const std::string& input) {
    std::stringstream ss(input);
    std::string commandName;
    ss >> commandName; 

    std::vector<std::string> args;
    std::string arg;
    while (ss >> arg) { 
        args.push_back(arg);
    }

   
    for (const auto& cmd : commands) {
        if (cmd->getName() == commandName) {
           
            if (cmd->requiresLogin() && !data.isUserLoggedIn()) {
                throw std::runtime_error("You must be logged in to use this command.");
            }
            cmd->execute(args, data);
            return;
        }
    }
    std::cerr << "Unknown command: " << commandName << std::endl;
}