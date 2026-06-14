#include "Stage.h"
#include "Models/Task/Task.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "App/AppData.h"
#include "Models/Project/Project.h"
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

const std::vector<std::weak_ptr<Task>>& Stage::getTasks() const { return tasks; }

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

void Stage::addTask(const std::shared_ptr<Task>& task) {
    if (!task) return;

    if (containsTask(task->getId())) {
        throw JiraInvalidArgumentException(std::string(StageConstants::ERROR_TASK_ALREADY_EXISTS));
    }
    tasks.push_back(task); 
}

void Stage::removeTask(size_t taskId) {
    auto it = std::remove_if(tasks.begin(), tasks.end(), [taskId](const std::weak_ptr<Task>& wp) {
        auto sp = wp.lock(); 
        return sp && sp->getId() == taskId;
        });

    if (it == tasks.end()) {
        throw JiraInvalidArgumentException(std::string(StageConstants::ERROR_TASK_NOT_FOUND));
    }
    tasks.erase(it, tasks.end());
}

bool Stage::containsTask(size_t taskId) const {
    return std::any_of(tasks.begin(), tasks.end(), [taskId](const std::weak_ptr<Task>& wp) {
        auto sp = wp.lock();
        return sp && sp->getId() == taskId;
        });
}

std::shared_ptr<Task> Stage::findTask(size_t taskId) const {
    auto it = std::find_if(tasks.begin(), tasks.end(), [taskId](const std::weak_ptr<Task>& wp) {
        auto sp = wp.lock();
        return sp && sp->getId() == taskId;
        });

    return (it != tasks.end()) ? it->lock() : nullptr;
}

int Stage::getTotalTaskCount() const {
    return static_cast<int>(tasks.size());
}


int Stage::getCompletedTaskCount() const {
    return static_cast<int>(std::count_if(tasks.begin(), tasks.end(), [](const std::weak_ptr<Task>& wp) {
        auto sp = wp.lock();
        return sp && sp->getStatus() == TaskStatus::Done;
        }));
}
void Stage::save(std::ostream& os) const {
    os << name << "\n"
        << static_cast<int>(status) << "\n";

    os << startDate.getDay() << " " << startDate.getMonth() << " " << startDate.getYear() << "\n";
    os << endDate.getDay() << " " << endDate.getMonth() << " " << endDate.getYear() << "\n";

   
    size_t validTaskCount = 0;
    for (const auto& wp : tasks) {
        if (!wp.expired()) {
            validTaskCount++;
        }
    }

    os << validTaskCount << "\n";
    for (const auto& wp : tasks) {
        if (auto sp = wp.lock()) {
            os << sp->getId() << "\n";
        }
    }
}

Stage Stage::load(std::istream& is, const AppData& context) {
    std::string name;
    if (!std::getline(is, name)) return Stage();

    int statusInt;
    is >> statusInt;
    is.ignore();

    int sDay, sMonth, sYear;
    is >> sDay >> sMonth >> sYear;
    is.ignore();
    Date startDate(sDay, sMonth, sYear);

    int eDay, eMonth, eYear;
    is >> eDay >> eMonth >> eYear;
    is.ignore();
    Date endDate(eDay, eMonth, eYear);

    StageStatus status = static_cast<StageStatus>(statusInt);

   
    Stage stage(name, startDate, endDate, status);

    size_t taskCount;
    is >> taskCount;
    is.ignore();

    for (size_t i = 0; i < taskCount; ++i) {
        size_t taskId;
        is >> taskId;
        is.ignore();

        bool found = false;
      
        for (const auto& project : context.getProjects()) {
            auto task = project->findTask(taskId);
            if (task) {
                stage.tasks.push_back(task);
                found = true;
                break;
            }
        }

        
    }

    return stage;
}
std::ostream& operator<<(std::ostream& os, const Stage& stage) {
    os << std::format("Stage: {} [{}] | Tasks: {}/{}",
        stage.name,
        toString(stage.status),
        stage.getCompletedTaskCount(),
        stage.getTotalTaskCount());
    return os;
}