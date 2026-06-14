#include "AppData.h"
#include "Models/Users/User.h"
#include "Models/Users/Administrator.h"
#include "Models/Project/Project.h"
#include <algorithm>
#include <filesystem>
#include "Factories/UserFactory.h"

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

bool AppData::removeUser(const std::string& username) {
    for (auto& project : projects) {
        if (project->hasMember(username)) {
            project->removeMember(username);
        }
    }

    auto it = std::remove_if(users.begin(), users.end(),
        [&username](const std::unique_ptr<User>& u) {
            return u && u->getUsername() == username;
        });

    if (it != users.end()) {
        users.erase(it, users.end());
        return true; 
    }

    return false;
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

void AppData::save() const{
    std::filesystem::create_directory("data");

  
    std::ofstream uOut("data/users.txt");
    if (uOut.is_open()) {
        uOut << users.size() << "\n";
        for (const auto& u : users) u->save(uOut);
    }

  
    std::ofstream pOut("data/projects.txt");
    if (pOut.is_open()) {
        pOut << projects.size() << "\n";
        for (const auto& p : projects) p->save(pOut);
    }


    std::ofstream tOut("data/tasks.txt");
    if (tOut.is_open()) {
        size_t totalTasks = 0;
        for (const auto& p : projects) {
           
            totalTasks += p->getTasks().size();
        }

        tOut << totalTasks << "\n";
        for (const auto& p : projects) {
            for (const auto& task : p->getTasks()) {
                tOut << p->getName() << "\n"; 
                task->save(tOut);
            }
        }
    }
}

void AppData::load() {
   
    std::ifstream uIn("data/users.txt");
    if (uIn.is_open()) {
        size_t count; uIn >> count; uIn.ignore();
        for (size_t i = 0; i < count; ++i) {
            this->addUser(User::loadPoly(uIn));
        }
    }

   
    std::ifstream pIn("data/projects.txt");
    if (pIn.is_open()) {
        size_t count; pIn >> count; pIn.ignore();
        for (size_t i = 0; i < count; ++i) {
            this->addProject(Project::loadSkeleton(pIn, *this));
        }
    }

   
    std::ifstream tIn("data/tasks.txt");
    if (tIn.is_open()) {
        size_t count; tIn >> count; tIn.ignore();
        for (size_t i = 0; i < count; ++i) {
            std::string projName;
            std::getline(tIn, projName);

            auto task = Task::load(tIn, *this);
            tIn.ignore();

            Project* p = findProject(projName);
            if (p) p->addTask(task);
        }
    }
}


void AppData::ensureDefaultAdmin() {

    for (const auto& user : users) {
        if (user->getRole() == UserRole::Administrator) return;
    }

    
    auto admin = std::unique_ptr<Administrator>(new Administrator("admin", "admin"));

    users.push_back(std::move(admin));

    std::clog << "[System] Admin created via friend access." << std::endl;
}