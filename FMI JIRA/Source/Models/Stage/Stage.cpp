#include "Stage.h"
#include "Models/Task/Task.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include <algorithm>
#include <format>

Stage::Stage(const std::string& name)
    : name(name), status(StageStatus::Planned), startDate(Date()), endDate(Date()) {
    if (this->name.empty()) {
        throw JiraInvalidArgumentException(std::string(StageConstants::ERROR_EMPTY_NAME));
    }
}

Stage::Stage(const std::string& name, const Date& startDate, const Date& endDate, StageStatus status)
    : name(name), startDate(startDate), endDate(endDate), status(status) {
    if (this->name.empty()) {
        throw JiraInvalidArgumentException(std::string(StageConstants::ERROR_EMPTY_NAME));
    }
    if (this->endDate < this->startDate) {
        throw JiraInvalidArgumentException(std::string(StageConstants::ERROR_INVALID_DATES));
    }
}

const std::string& Stage::getName() const { return name; }
const Date& Stage::getStartDate() const { return startDate; }
const Date& Stage::getEndDate() const { return endDate; }
StageStatus Stage::getStatus() const { return status; }
const std::vector<Task*>& Stage::getTasks() const { return tasks; }

void Stage::start(const Date& currentStartDate) {
    if (status != StageStatus::Planned) {
        throw JiraInvalidArgumentException(std::string(StageConstants::ERROR_ALREADY_STARTED));
    }
    startDate = currentStartDate;
    status = StageStatus::Active;
}

void Stage::finish(const Date& currentEndDate) {
    if (status != StageStatus::Active) {
        throw JiraInvalidArgumentException(std::string(StageConstants::ERROR_NOT_ACTIVE));
    }
    if (currentEndDate < startDate) {
        throw JiraInvalidArgumentException(std::string(StageConstants::ERROR_INVALID_DATES));
    }
    endDate = currentEndDate;
    status = StageStatus::Finished;
}

void Stage::addTask(Task* task) {
    if (!task) return;
    if (containsTask(task->getId())) {
        throw JiraInvalidArgumentException(std::string(StageConstants::ERROR_TASK_ALREADY_EXISTS));
    }
    tasks.push_back(task);
}

void Stage::removeTask(size_t taskId) {
    auto it = std::remove_if(tasks.begin(), tasks.end(), [taskId](const Task* t) {
        return t->getId() == taskId;
        });

    if (it == tasks.end()) {
        throw JiraInvalidArgumentException(std::string(StageConstants::ERROR_TASK_NOT_FOUND));
    }
    tasks.erase(it, tasks.end());
}

bool Stage::containsTask(size_t taskId) const {
    return std::any_of(tasks.begin(), tasks.end(), [taskId](const Task* t) {
        return t->getId() == taskId;
        });
}

Task* Stage::findTask(size_t taskId) const {
    auto it = std::find_if(tasks.begin(), tasks.end(), [taskId](const Task* t) {
        return t->getId() == taskId;
        });
    return (it != tasks.end()) ? *it : nullptr;
}

int Stage::getTotalTaskCount() const {
    return static_cast<int>(tasks.size());
}

int Stage::getCompletedTaskCount() const {
    return static_cast<int>(std::count_if(tasks.begin(), tasks.end(), [](const Task* t) {
        return t->getStatus() == TaskStatus::Done;
        }));
}

std::ostream& operator<<(std::ostream& os, const Stage& stage) {
    os << std::format("Stage: {} [{}] | Tasks: {}/{}",
        stage.name,
        toString(stage.status),
        stage.getCompletedTaskCount(),
        stage.getTotalTaskCount());
    return os;
}