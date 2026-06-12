#include "Administrator.h"
#include "Exceptions/JiraStateException.h"

Administrator::Administrator(size_t id, const std::string& username, const std::string& password)
    : User(id, username, password, UserRole::Administrator) {
}

Administrator::Administrator(const std::string& username, const std::string& password)
    : User(username, password, UserRole::Administrator) { }

Administrator& Administrator::getInstance() {
    static Administrator instance{
        std::string(AdminConstants::DEFAULT_ADMIN_USERNAME),
        std::string(AdminConstants::DEFAULT_ADMIN_PASSWORD)};

    return instance;
}

std::unique_ptr<User> Administrator::clone() const {
    throw JiraStateException(std::string(AdminConstants::ERROR_CLONE_ADMIN));
}


void Administrator::displayInfo(std::ostream& os) const {
    User::displayInfo(os);
}