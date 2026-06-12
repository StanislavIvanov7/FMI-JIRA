#include "Lecturer.h"

Lecturer::Lecturer(size_t id, const std::string& username, const std::string& password)
    : User(id, username, password, UserRole::Lecturer) {
}

Lecturer::Lecturer(const std::string& username, const std::string& password)
    : User(username, password, UserRole::Lecturer) {
} 

std::unique_ptr<User> Lecturer::clone() const {
    return std::make_unique<Lecturer>(*this);
}

void Lecturer::displayInfo(std::ostream& os) const {
    User::displayInfo(os);
}