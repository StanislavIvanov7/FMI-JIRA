#pragma once
#include <memory>
#include <string>
#include <vector>
#include <string_view>
#include <optional>
#include "Utils/Enums/TaskType.h"
#include "Utils/Enums/TaskPriority.h"
#include "Utils/Enums/TaskStatus.h"
#include "Utils/Date.h"
#include "Models/Comments/Comment.h"
#include "Models/Task/HistoryEntry.h"

class Task;
class User;

namespace TaskFactoryConstants {
    constexpr std::string_view ERROR_INVALID_CREATE_TYPE = "Invalid or unknown task type passed to TaskFactory::createTask.";
    constexpr std::string_view ERROR_INVALID_LOAD_TYPE = "Invalid or unknown task type passed to TaskFactory::loadTask.";
}

class TaskFactory {
public:
  
    TaskFactory() = delete;

    static std::shared_ptr<Task> createTask(
        const std::string& title,
        const std::string& description,
        TaskType type,
        TaskPriority priority,
        const Date& deadline
    );

    static std::shared_ptr<Task> loadTask(
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
        const std::vector<HistoryEntry>& changeHistory
    );
};