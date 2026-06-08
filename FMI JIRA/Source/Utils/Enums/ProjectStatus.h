#pragma once
#include<string>
#include <string_view>
#include "Exceptions/JiraInvalidArgumentException.h"
enum class ProjectStatus {
    Active,
    Finished
};

namespace ProjectStatusConstants {
    constexpr std::string_view ACTIVE = "Active";
    constexpr std::string_view FINISHED = "Finished";

    constexpr std::string_view ERROR_INVALID_STATUS = "Unknown Project Status requested: ";
}

inline std::string toString(ProjectStatus status) {
    return (status == ProjectStatus::Active) ?
        std::string(ProjectStatusConstants::ACTIVE) : std::string(ProjectStatusConstants::FINISHED);
}

inline ProjectStatus parseProjectStatus(const std::string& str) {
    if (str == ProjectStatusConstants::ACTIVE)   return ProjectStatus::Active;
    if (str == ProjectStatusConstants::FINISHED) return ProjectStatus::Finished;

    throw JiraInvalidArgumentException(std::string(ProjectStatusConstants::ERROR_INVALID_STATUS) + str);
}