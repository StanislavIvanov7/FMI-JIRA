#pragma once
#include<string>
#include <string_view>
#include "Exceptions/JiraInvalidArgumentException.h"

enum class TaskType {
    Bug,
    Feature,
    Task,
    Improvement
};

namespace TaskTypeConstants {
    constexpr std::string_view BUG = "Bug";
    constexpr std::string_view FEATURE = "Feature";
    constexpr std::string_view TASK = "Task";
    constexpr std::string_view IMPROVEMENT = "Improvement";
    constexpr std::string_view UNKNOWN = "Unknown";

    constexpr std::string_view ERROR_INVALID_TYPE = "Unknown Task Type requested: ";
}

inline std::string to_string(TaskType type) {
    switch (type) {
    case TaskType::Bug:         return std::string(TaskTypeConstants::BUG);
    case TaskType::Feature:     return std::string(TaskTypeConstants::FEATURE);
    case TaskType::Task:        return std::string(TaskTypeConstants::TASK);
    case TaskType::Improvement: return std::string(TaskTypeConstants::IMPROVEMENT);
    }
    return std::string(TaskTypeConstants::UNKNOWN);
}

inline TaskType parse_task_type(const std::string& str) {
    if (str == TaskTypeConstants::BUG)         return TaskType::Bug;
    if (str == TaskTypeConstants::FEATURE)     return TaskType::Feature;
    if (str == TaskTypeConstants::TASK)        return TaskType::Task;
    if (str == TaskTypeConstants::IMPROVEMENT) return TaskType::Improvement;

    throw JiraInvalidArgumentException(std::string(TaskTypeConstants::ERROR_INVALID_TYPE) + str);
}