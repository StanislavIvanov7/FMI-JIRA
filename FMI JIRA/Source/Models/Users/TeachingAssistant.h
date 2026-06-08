#pragma once
#include "User.h"

class TeachingAssistant : public User {
public:
    TeachingAssistant(const std::string& username, const std::string& password);

    std::unique_ptr<User> clone() const override;
    void displayInfo(std::ostream& os) const override;
};