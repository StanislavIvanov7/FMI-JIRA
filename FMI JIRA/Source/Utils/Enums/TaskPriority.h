#pragma once
#include<string>
#include <string_view>
#include "Exceptions/JiraInvalidArgumentException.h"
enum class TaskPriority {
    Low,
    Medium,
    High,
    Critical
};

namespace TaskPriorityConstants {
    constexpr std::string_view LOW = "Low";
    constexpr std::string_view MEDIUM = "Medium";
    constexpr std::string_view HIGH = "High";
    constexpr std::string_view CRITICAL = "Critical";
    constexpr std::string_view UNKNOWN = "Unknown";

    constexpr std::string_view ERROR_INVALID_PRIORITY = "Unknown Task Priority requested: ";
}

inline std::string to_string(TaskPriority priority) {
    switch (priority) {
    case TaskPriority::Low:      return std::string(TaskPriorityConstants::LOW);
    case TaskPriority::Medium:   return std::string(TaskPriorityConstants::MEDIUM);
    case TaskPriority::High:     return std::string(TaskPriorityConstants::HIGH);
    case TaskPriority::Critical: return std::string(TaskPriorityConstants::CRITICAL);
    }
    return std::string(TaskPriorityConstants::UNKNOWN);
}

inline TaskPriority parse_task_priority(const std::string& str) {
    if (str == TaskPriorityConstants::LOW)      return TaskPriority::Low;
    if (str == TaskPriorityConstants::MEDIUM)   return TaskPriority::Medium;
    if (str == TaskPriorityConstants::HIGH)     return TaskPriority::High;
    if (str == TaskPriorityConstants::CRITICAL) return TaskPriority::Critical;

    throw JiraInvalidArgumentException(std::string(TaskPriorityConstants::ERROR_INVALID_PRIORITY) + str);
}