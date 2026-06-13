#include "TaskFactory.h"
#include "Models/Task/Task.h"
#include "Exceptions/JiraInvalidArgumentException.h"

std::shared_ptr<Task> TaskFactory::createTask(
    const std::string& title,
    const std::string& description,
    TaskType type,
    TaskPriority priority,
    const Date& deadline)
{
    return std::make_shared<Task>(title, description, type, priority, deadline);
}

std::shared_ptr<Task> TaskFactory::loadTask(
    size_t id,
    const std::string& title,
    const std::string& description,
    TaskType type,
    TaskPriority priority,
    TaskStatus status,
    const User* assignee,
    const Date& deadline,
    int points,
    std::optional<double> grade,
    bool approved,
    const std::vector<Comment>& comments,
    const std::vector<std::string>& tags,
    const std::vector<HistoryEntry>& changeHistory)
{
   
    return std::make_shared<Task>(
        id,
        title,
        description,
        type,
        priority,
        status,
        assignee,
        deadline,
        points,
        grade,
        approved,
        comments,
        tags,
        changeHistory
    );
}