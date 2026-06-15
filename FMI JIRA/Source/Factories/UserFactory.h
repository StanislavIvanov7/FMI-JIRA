#pragma once
#include <memory>
#include <string>
#include "Utils/Enums/UserRole.h" 
#include "Models/Users/User.h"
#include <string_view>

namespace UserFactoryConstants {
    constexpr std::string_view ERROR_INVALID_CREATE_ROLE = "Invalid or unknown role passed to UserFactory::createUser.";
    constexpr std::string_view ERROR_INVALID_LOAD_ROLE = "Invalid or unknown role passed to UserFactory::loadUser.";
}

class UserFactory {
public:

    UserFactory() = delete;

    static std::unique_ptr<User> createUser(
        const std::string& username,
        const std::string& password,
        UserRole role
    );

    static std::unique_ptr<User> loadUser(
        size_t id,
        const std::string& username,
        const std::string& password,
        UserRole role,
        int completedTasks = 0,        
        int inProgressTasks = 0,        
        double performanceScore = 0.0
    );
};