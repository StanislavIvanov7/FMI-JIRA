#include "Project.h"
#include "Models/Task/Task.h"
#include "Models/Users/User.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include <algorithm>
#include <format>

Project::Project(const std::string& name, const std::string& description)
    : name(name), description(description), status(ProjectStatus::Active) {
    if (this->name.empty()) {
        throw JiraInvalidArgumentException(std::string(ProjectConstants::ERROR_EMPTY_NAME));
    }
}

const std::string& Project::getName() const {
    return name;
}

const std::string& Project::getDescription() const {
    return description;
}

ProjectStatus Project::getStatus() const {
    return status;
}

const std::vector<User*>& Project::getMembers() const {
    return members;
}

const std::vector<std::shared_ptr<Task>>& Project::getTasks() const {
    return tasks;
}

const std::vector<Stage>& Project::getStages() const {
    return stages;
}

std::vector<Stage>& Project::getStages()
{
    return stages;
}

void Project::setDescription(const std::string& newDescription) {
    description = newDescription;
}

void Project::setStatus(ProjectStatus newStatus) {
    status = newStatus;
}

void Project::addMember(User* user) {
    if (!user) return;
    if (hasMember(user->getUsername())) {
        throw JiraInvalidArgumentException(std::string(ProjectConstants::ERROR_MEMBER_ALREADY_EXISTS));
    }
    members.push_back(user);
}

void Project::removeMember(const std::string& username) {
    auto it = std::remove_if(members.begin(), members.end(), [&username](const User* u) {
        return u && u->getUsername() == username;
        });

    if (it == members.end()) {
        throw JiraInvalidArgumentException(std::string(ProjectConstants::ERROR_MEMBER_NOT_FOUND));
    }
    members.erase(it, members.end());
}

bool Project::hasMember(const std::string& username) const {
    return findMember(username) != nullptr;
}

User* Project::findMember(const std::string& username) {
    auto it = std::find_if(members.begin(), members.end(), [&username](const User* u) {
        return u && u->getUsername() == username;
        });
    return (it != members.end()) ? *it : nullptr;
}

const User* Project::findMember(const std::string& username) const {
    auto it = std::find_if(members.begin(), members.end(), [&username](const User* u) {
        return u && u->getUsername() == username;
        });
    return (it != members.end()) ? *it : nullptr;
}

std::shared_ptr<Task> Project::addTask(std::shared_ptr<Task> task) {
    if (!task) return nullptr;

    if (findTask(task->getId()) != nullptr) {
        throw JiraInvalidArgumentException("Task with this ID already exists in the project.");
    }

    tasks.push_back(task); 
    return task;
}


std::shared_ptr<Task> Project::findTask(size_t taskId) const {
    auto it = std::find_if(tasks.begin(), tasks.end(), [taskId](const std::shared_ptr<Task>& t) {
        return t && t->getId() == taskId;
        });
    return (it != tasks.end()) ? *it : nullptr;
}


std::shared_ptr<Task> Project::findTaskByFormattedId(const std::string& formattedId) const {
    auto it = std::find_if(tasks.begin(), tasks.end(), [&formattedId](const std::shared_ptr<Task>& t) {
        return t && t->getFormattedId() == formattedId;
        });
    return (it != tasks.end()) ? *it : nullptr;
}

void Project::addStage(const Stage& stage) {
    if (findStage(stage.getName()) != nullptr) {
        throw JiraInvalidArgumentException(std::string(ProjectConstants::ERROR_STAGE_ALREADY_EXISTS));
    }
    stages.push_back(stage);
}

Stage* Project::findStage(const std::string& stageName) {
    auto it = std::find_if(stages.begin(), stages.end(), [&stageName](const Stage& s) {
        return s.getName() == stageName;
        });
    return (it != stages.end()) ? &(*it) : nullptr;
}

const Stage* Project::findStage(const std::string& stageName) const {
    auto it = std::find_if(stages.begin(), stages.end(), [&stageName](const Stage& s) {
        return s.getName() == stageName;
        });
    return (it != stages.end()) ? &(*it) : nullptr;
}


void Project::finalize() {
    status = ProjectStatus::Finished;
}

void Project::archive() {
    status = ProjectStatus::Finished;
}

std::ostream& operator<<(std::ostream& os, const Project& project) {
    os << std::format("Project: {} | Status: {}\nDescription: {}\nMembers: {}\nStages: {}\nTasks: {}",
        project.name,
        (project.status == ProjectStatus::Active ? "Active" : "Finished"),
        project.description,
        project.members.size(),
        project.stages.size(),
        project.tasks.size());
    return os;
}