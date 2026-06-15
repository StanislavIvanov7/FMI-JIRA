#include "User.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Utils/Enums/UserRole.h"
#include "Factories/UserFactory.h"
#include "Models/Users/Administrator.h"
size_t User::idCounter = UserConstants::INITIAL_ID_VALUE;

User::User(const std::string& username, const std::string& password, UserRole role)
    : id(idCounter++), role(role)
{
    if (username.empty()) {
        throw JiraInvalidArgumentException(std::string(UserConstants::ERROR_EMPTY_USERNAME));
    }
    if (password.empty()) {
        throw JiraInvalidArgumentException(std::string(UserConstants::ERROR_EMPTY_PASSWORD));
    }

    this->username = username;
    this->password = password;
}

User::User(size_t id, const std::string& username, const std::string& password, UserRole role)
    : id(id), username(username), password(password), role(role)
{
    if (username.empty()) {
        throw JiraInvalidArgumentException(std::string(UserConstants::ERROR_EMPTY_USERNAME));
    }
    if (password.empty()) {
        throw JiraInvalidArgumentException(std::string(UserConstants::ERROR_EMPTY_PASSWORD));
    }

    if (id >= idCounter) {
        idCounter = id + 1;
    }
}

size_t User::getId() const {
    return id; 
}

const std::string& User::getUsername() const {
    return username;
}

UserRole User::getRole() const {
    return role;
}


std::string User::getRoleString() const {

    return toString(role);
}

bool User::checkPassword(const std::string& password) const {
    return this->password == password;
}

void User::changePassword(const std::string& oldPassword, const std::string& newPassword) {
    if (!checkPassword(oldPassword)) {
        throw JiraInvalidArgumentException(std::string(UserConstants::ERROR_INCORRECT_PASSWORD));
    }
    if (newPassword.empty()) {
        throw JiraInvalidArgumentException(std::string(UserConstants::ERROR_EMPTY_PASSWORD));
    }
    if (oldPassword == newPassword) {
        throw JiraInvalidArgumentException(std::string(UserConstants::ERROR_SAME_PASSWORD));
    }
    this->password = newPassword;
}

void User::displayInfo(std::ostream& os) const {
    os << "ID: " << id
        << " | Username: " << username
        << " | Role: " << getRoleString();
}

void User::save(std::ostream& os) const
{
    os << static_cast<int>(role) << "\n"
        << id << "\n"
        << username << "\n"
        << password << "\n";
}

std::unique_ptr<User> User::loadPoly(std::istream& is) {
    int roleInt;
    if (!(is >> roleInt)) return nullptr;
    is.ignore();

    size_t id;
    is >> id;
    is.ignore();

    std::string username, password;
    std::getline(is, username);
    std::getline(is, password);

    UserRole role = static_cast<UserRole>(roleInt);

    std::unique_ptr<User> user = UserFactory::loadUser(id, username, password, role, 0, 0, 0.0);

    if (user) {
        user->loadSubclass(is);
    }

    return user;
}
std::ostream& operator<<(std::ostream& os, const User& user) {
    user.displayInfo(os); 
    return os;
}