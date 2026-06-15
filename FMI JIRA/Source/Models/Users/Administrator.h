#pragma once
#include "User.h"

namespace AdminConstants {
    constexpr std::string_view ERROR_CLONE_ADMIN = "Cannot clone Administrator.";
    constexpr std::string_view DEFAULT_ADMIN_USERNAME = "admin";
    constexpr std::string_view DEFAULT_ADMIN_PASSWORD = "admin";
}

class Administrator : public User {
    friend class AppData;
    friend class UserFactory;
private:
    Administrator(size_t id, const std::string& username, const std::string& password);
    Administrator(const std::string& username, const std::string& password);

public:
    Administrator(const Administrator&) = delete;
    Administrator& operator=(const Administrator&) = delete;

    Administrator(Administrator&&) = delete;
    Administrator& operator=(Administrator&&) = delete;

    static Administrator& getInstance();

    std::unique_ptr<User> clone() const override;
    void displayInfo(std::ostream& os) const override;
};
