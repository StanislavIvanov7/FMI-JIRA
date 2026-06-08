#include "TeachingAssistant.h"

TeachingAssistant::TeachingAssistant(const std::string& username, const std::string& password)
    : User(username, password, UserRole::TeachingAssistant) {
} 

std::unique_ptr<User> TeachingAssistant::clone() const {
    return std::make_unique<TeachingAssistant>(*this);
}

void TeachingAssistant::displayInfo(std::ostream& os) const {
    User::displayInfo(os);
}