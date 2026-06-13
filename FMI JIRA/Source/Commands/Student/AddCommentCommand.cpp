#include "AddCommentCommand.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Models/Project/Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include "Models/Comments/Comment.h" 
#include "Utils/Date.h"             
#include <iostream>

AddCommentCommand::AddCommentCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool AddCommentCommand::requiresLogin() const {
    return true;
}

void AddCommentCommand::execute(const std::vector<std::string>& args, AppData& data) {
    if (args.size() != 1) {
        throw JiraInvalidArgumentException("Usage: add-comment <task_id>");
    }

    std::string taskIdStr = args[0];

   
    std::shared_ptr<Task> foundTask = nullptr;
    for (const auto& project : data.getProjects()) {
        auto task = project->findTaskByFormattedId(taskIdStr);
        if (task) {
            foundTask = task;
            break;
        }
    }

    if (!foundTask) {
        throw JiraInvalidArgumentException(std::string(ProjectConstants::ERROR_TASK_NOT_FOUND));
    }

    
    std::string content;
    std::cout << "Enter comment content: ";
    std::getline(std::cin >> std::ws, content);

    if (content.empty()) {
        throw JiraInvalidArgumentException(std::string(CommentConstants::ERROR_EMPTY_CONTENT));
    }

    
    Comment newComment(data.getCurrentUser(), content, Date());

    foundTask->addComment(newComment);

    std::cout << "Comment added to task " << foundTask->getFormattedId() << "." << std::endl;
}