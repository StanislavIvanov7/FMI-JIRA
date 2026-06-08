#pragma once
#include<string>
#include <string_view>
#include "Exceptions/JiraInvalidArgumentException.h"
enum class TaskStatus {
    ToDo,
    InProgress,
    InReview,
    Done
};

namespace TaskStatusConstants {
    constexpr std::string_view TODO = "ToDo";
    constexpr std::string_view IN_PROGRESS = "InProgress";
    constexpr std::string_view IN_REVIEW = "InReview";
    constexpr std::string_view DONE = "Done";
    constexpr std::string_view UNKNOWN = "Unknown";

    constexpr std::string_view ERROR_INVALID_STATUS = "Unknown Task Status requested: ";
}

inline std::string to_string(TaskStatus status) {
    switch (status) {
    case TaskStatus::ToDo:       return std::string(TaskStatusConstants::TODO);
    case TaskStatus::InProgress: return std::string(TaskStatusConstants::IN_PROGRESS);
    case TaskStatus::InReview:   return std::string(TaskStatusConstants::IN_REVIEW);
    case TaskStatus::Done:       return std::string(TaskStatusConstants::DONE);
    }
    return std::string(TaskStatusConstants::UNKNOWN);
}

inline TaskStatus parse_task_status(const std::string& str) {
    if (str == TaskStatusConstants::TODO)        return TaskStatus::ToDo;
    if (str == TaskStatusConstants::IN_PROGRESS) return TaskStatus::InProgress;
    if (str == TaskStatusConstants::IN_REVIEW)   return TaskStatus::InReview;
    if (str == TaskStatusConstants::DONE)        return TaskStatus::Done;

    throw JiraInvalidArgumentException(std::string(TaskStatusConstants::ERROR_INVALID_STATUS) + str);
}