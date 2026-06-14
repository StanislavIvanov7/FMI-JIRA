#pragma once
#include <string>
#include <vector>
#include <string_view>
#include "Utils/Date.h"
#include "Utils/Enums/StageStatus.h"
#include "Models/Task/Task.h"
#include<memory>

namespace StageConstants {
    constexpr std::string_view ERROR_EMPTY_NAME = "Stage name cannot be empty.";
    constexpr std::string_view ERROR_INVALID_DATES = "Stage end date cannot be before start date.";
    constexpr std::string_view ERROR_TASK_NOT_FOUND = "Task with the requested ID was not found in this stage.";
    constexpr std::string_view ERROR_TASK_ALREADY_EXISTS = "Task is already present in this stage.";
    constexpr std::string_view ERROR_ALREADY_STARTED = "Stage has already been started.";
    constexpr std::string_view ERROR_NOT_ACTIVE = "Stage cannot be finished because it is not active.";
}

class Stage {
private:
    std::string name;
    Date startDate;
    Date endDate;
    StageStatus status;
    std::vector<std::weak_ptr<Task>> tasks;

public:

    Stage() = default;
    explicit Stage(const std::string& name);
    Stage(const std::string& name, const Date& startDate, const Date& endDate, StageStatus status);

    const std::string& getName() const;
    const Date& getStartDate() const;
    const Date& getEndDate() const;
    StageStatus getStatus() const;
    const std::vector<std::weak_ptr<Task>>& getTasks() const;

    void start(const Date& currentStartDate);
    void finish(const Date& currentEndDate);

    void addTask(const std::shared_ptr<Task>& task);
    void removeTask(size_t taskId);
    bool containsTask(size_t taskId) const;
    std::shared_ptr<Task> findTask(size_t taskId) const;

    int getTotalTaskCount() const;
    int getCompletedTaskCount() const;

    void save(std::ostream& os) const;
    static Stage load(std::istream& is, const AppData& context);

    friend std::ostream& operator<<(std::ostream& os, const Stage& stage);
};