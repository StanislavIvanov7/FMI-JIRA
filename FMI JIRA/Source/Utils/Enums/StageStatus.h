#pragma once
#include<string>
#include <string_view>
#include "Exceptions/JiraInvalidArgumentException.h"
enum class StageStatus {
    Planned,
    Active,
    Finished
};

namespace StageStatusConstants {
    constexpr std::string_view PLANNED = "Planned";
    constexpr std::string_view ACTIVE = "Active";
    constexpr std::string_view FINISHED = "Finished";
    constexpr std::string_view UNKNOWN = "Unknown";

    constexpr std::string_view ERROR_INVALID_STATUS = "Unknown Stage Status requested: ";
}

inline std::string toString(StageStatus status) {
    switch (status) {
    case StageStatus::Planned:  return std::string(StageStatusConstants::PLANNED);
    case StageStatus::Active:   return std::string(StageStatusConstants::ACTIVE);
    case StageStatus::Finished: return std::string(StageStatusConstants::FINISHED);
    }
    return std::string(StageStatusConstants::UNKNOWN);
}

inline StageStatus parseStageStatus(const std::string& str) {
    if (str == StageStatusConstants::PLANNED) return StageStatus::Planned;
    if (str == StageStatusConstants::ACTIVE)  return StageStatus::Active;
    if (str == StageStatusConstants::FINISHED) return StageStatus::Finished;

    throw JiraInvalidArgumentException(std::string(StageStatusConstants::ERROR_INVALID_STATUS) + str);
}