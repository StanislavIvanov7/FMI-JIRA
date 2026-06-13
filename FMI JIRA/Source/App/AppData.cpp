#include "AppData.h"
#include "Models/Users/User.h"
#include "Models/Project/Project.h"
#include <algorithm>

bool AppData::isRunning() const { 
    return running;
}

void AppData::stop() { 
    running = false; 
}

void AppData::addUser(std::unique_ptr<User> user) {
    if (user) {
        users.push_back(std::move(user));
    }
}

User* AppData::findUser(const std::string& username) const {

    auto it = std::find_if(users.begin(), users.end(), [&](const std::unique_ptr<User>& u) {
        return u->getUsername() == username;
        });
    return (it != users.end()) ? it->get() : nullptr;
}


void AppData::setCurrentUser(User* user) {
    currentUser = user;
}

User* AppData::getCurrentUser() const {
    return currentUser;
}

bool AppData::isUserLoggedIn() const {
    return currentUser != nullptr;
}

void AppData::logout() {
    currentUser = nullptr;
}

void AppData::addProject(std::shared_ptr<Project> project) {
    if (project) {
        projects.push_back(project);
    }
}

Project* AppData::findProject(const std::string& name) const {
    auto it = std::find_if(projects.begin(), projects.end(), [&](const std::shared_ptr<Project>& p) {
        return p->getName() == name;
        });
    return (it != projects.end()) ? it->get() : nullptr;
}

const std::vector<std::shared_ptr<Project>>& AppData::getProjects() const {
    return projects;
}