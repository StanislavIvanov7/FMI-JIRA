#pragma once
#include<string>
#include <string_view>
#include "Exceptions/JiraInvalidArgumentException.h"
enum class UserRole {
    Student,
    TeachingAssistant,
    Lecturer,
    Administrator
};

namespace UserRoleConstants {
    constexpr std::string_view STUDENT = "Student";
    constexpr std::string_view TEACHING_ASSISTANT = "TeachingAssistant";
    constexpr std::string_view LECTURER = "Lecturer";
    constexpr std::string_view ADMIN = "Administrator";
    constexpr std::string_view UNKNOWN = "Unknown";

    constexpr std::string_view ERROR_INVALID_ROLE = "Unknown User Role requested: ";
}

inline std::string toString(UserRole role) {
    switch (role) {
    case UserRole::Student:           return std::string(UserRoleConstants::STUDENT);
    case UserRole::TeachingAssistant: return std::string(UserRoleConstants::TEACHING_ASSISTANT);
    case UserRole::Lecturer:          return std::string(UserRoleConstants::LECTURER);
    case UserRole::Administrator:     return std::string(UserRoleConstants::ADMIN);
    }
    return std::string(UserRoleConstants::UNKNOWN);
}

inline UserRole parseRole(const std::string& str) {
    if (str == UserRoleConstants::STUDENT) return UserRole::Student;
    if (str == UserRoleConstants::TEACHING_ASSISTANT)      return UserRole::TeachingAssistant;
    if (str == UserRoleConstants::LECTURER) return UserRole::Lecturer;
    if (str == UserRoleConstants::ADMIN)    return UserRole::Administrator;

    throw JiraInvalidArgumentException(std::string(UserRoleConstants::ERROR_INVALID_ROLE) + str);
}