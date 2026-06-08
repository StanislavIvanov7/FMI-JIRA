#pragma once
#include <string>
#include <string_view>
#include <memory>
#include <iostream>
#include "Utils/Enums/UserRole.h"
namespace UserConstants {
    constexpr std::string_view ERROR_EMPTY_USERNAME = "Username cannot be empty.";
    constexpr std::string_view ERROR_EMPTY_PASSWORD = "Password cannot be empty.";
    constexpr std::string_view ERROR_INCORRECT_PASSWORD = "The provided password does not match.";
    constexpr std::string_view ERROR_SAME_PASSWORD = "New password cannot be the same as the old password.";

    constexpr size_t INITIAL_ID_VALUE = 1;
}
class User
{

    private:
        static size_t idCounter; 

        size_t id;
        std::string username;
        std::string password;
        UserRole role;

    public:
        
        User(const std::string& username, const std::string& password, UserRole role);
    
        size_t getId() const;
        const std::string& getUsername() const;
        UserRole getRole() const;
        std::string getRoleString() const;

        bool checkPassword(const std::string& password) const;
        void changePassword(const std::string& oldPassword, const std::string& newPassword);

        virtual std::unique_ptr<User> clone() const = 0;
        virtual void displayInfo(std::ostream& os) const;
        virtual ~User() noexcept = default;
       
        friend std::ostream& operator<<(std::ostream& os, const User& user);
};

