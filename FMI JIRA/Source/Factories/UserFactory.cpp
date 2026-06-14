#include "UserFactory.h"
#include "Models/Users/Student.h"
#include "Models/Users/TeachingAssistant.h"
#include "Models/Users/Lecturer.h"
#include "Models/Users/Administrator.h"
#include "Exceptions/JiraInvalidArgumentException.h"

std::unique_ptr<User> UserFactory::createUser(
    const std::string& username,
    const std::string& password,
    UserRole role,
    const std::string& facultyNumber)
{
    switch (role) {
    case UserRole::Student:
        return std::make_unique<Student>(username, password);
    case UserRole::TeachingAssistant:
        return std::make_unique<TeachingAssistant>(username, password);
    case UserRole::Lecturer:
        return std::make_unique<Lecturer>(username, password);
    default:
        throw JiraInvalidArgumentException(std::string(UserFactoryConstants::ERROR_INVALID_CREATE_ROLE));
    }
}

std::unique_ptr<User> UserFactory::loadUser(
    size_t id,
    const std::string& username,
    const std::string& password,
    UserRole role,
    const std::string& facultyNumber, 
    int completedTasks,
    int inProgressTasks,
    double performanceScore)
{
    switch (role) {
    case UserRole::Student:
        return std::make_unique<Student>(id, username, password,
            completedTasks, inProgressTasks, performanceScore);
    case UserRole::TeachingAssistant:
        return std::make_unique<TeachingAssistant>(id, username, password);
    case UserRole::Lecturer:
        return std::make_unique<Lecturer>(id, username, password);
    default:
        throw JiraInvalidArgumentException(std::string(UserFactoryConstants::ERROR_INVALID_LOAD_ROLE));
    }
}