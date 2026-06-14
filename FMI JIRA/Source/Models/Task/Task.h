#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <string_view>
#include <optional>

#include "Utils/Enums/TaskType.h"
#include "Utils/Date.h"
#include "Utils/Enums/TaskPriority.h"
#include "Utils/Enums/TaskStatus.h"
#include "Models/Comments/Comment.h"
#include "Models/Task/HistoryEntry.h"

class User;
class AppData;

namespace TaskConstants {
    constexpr std::string_view ERROR_EMPTY_TITLE = "Task title cannot be empty.";
    constexpr std::string_view ERROR_EMPTY_DESCRIPTION = "Task description cannot be empty.";
    constexpr std::string_view ERROR_INVALID_POINTS = "Task points cannot be negative.";
    constexpr std::string_view ERROR_INVALID_GRADE = "Task grade must be between 2.0 and 6.0.";

    constexpr int INITIAL_POINTS = 0;
    constexpr bool INITIAL_APPROVED_STATUS = false;

    constexpr std::string_view FIELD_TITLE = "Title";
    constexpr std::string_view FIELD_DESCRIPTION = "Description";
    constexpr std::string_view FIELD_PRIORITY = "Priority";
    constexpr std::string_view FIELD_STATUS = "Status";
    constexpr std::string_view FIELD_ASSIGNEE = "Assignee";
    constexpr std::string_view FIELD_DEADLINE = "Deadline";
    constexpr std::string_view FIELD_POINTS = "Points";
    constexpr std::string_view FIELD_GRADE = "Grade";
    constexpr std::string_view FIELD_APPROVED = "Approved";
    constexpr std::string_view FIELD_TAG_ADDED = "Tag Added";

    constexpr std::string_view VALUE_UNASSIGNED = "Unassigned";
    constexpr std::string_view VALUE_TRUE = "True";
    constexpr std::string_view VALUE_FALSE = "False";
    constexpr std::string_view VALUE_NONE = "";
}

class Task {
private:
    static size_t idGen;

    size_t id;
    std::string title;
    std::string description;
    TaskType type;
    TaskPriority priority;
    TaskStatus status;
    const User* assignee = nullptr;
    Date deadline;
    int points = TaskConstants::INITIAL_POINTS;
    std::optional<double> grade = std::nullopt;
    bool approved = TaskConstants::INITIAL_APPROVED_STATUS;

    std::vector<Comment> comments;
    std::vector<std::string> tags;
    std::vector<HistoryEntry> changeHistory;

public:
    Task(const std::string& title, const std::string& description, TaskType type, TaskPriority priority, const Date& deadline);
    
    Task(size_t id, const std::string& title, const std::string& description,
        TaskType type, TaskPriority priority, TaskStatus status,
        const User* assignee, const Date& deadline, int points,
        std::optional<double> grade, bool approved, std::vector<Comment> comments,
        std::vector<std::string> tags, std::vector<HistoryEntry> changeHistory);

    size_t getId() const;
    std::string getFormattedId() const;
    const std::string& getTitle() const;
    const std::string& getDescription() const;
    TaskType getType() const;
    TaskPriority getPriority() const;
    TaskStatus getStatus() const;
    const User* getAssignee() const;
    const Date& getDeadline() const;
    int getPoints() const;
    std::optional<double> getGrade() const;
    bool isApproved() const;

    const std::vector<Comment>& getComments() const;
    const std::vector<std::string>& getTags() const;
    const std::vector<HistoryEntry>& getChangeHistory() const;

    void setTitle(const std::string& newTitle, const User* changedBy, const Date& timestamp);
    void setDescription(const std::string& newDescription, const User* changedBy, const Date& timestamp);
    void setPriority(TaskPriority priority, const User* changedBy, const Date& timestamp);
    void setStatus(TaskStatus status, const User* changedBy, const Date& timestamp);
    void setAssignee(const User* user, const User* changedBy, const Date& timestamp);
    void setDeadline(const Date& deadline, const User* changedBy, const Date& timestamp);
    void setPoints(int points, const User* changedBy, const Date& timestamp);
    void setGrade(double grade, const User* changedBy, const Date& timestamp);
    void setApproved(bool approved, const User* changedBy, const Date& timestamp);

    void addComment(const Comment& comment);
    void addTag(const std::string& tag, const User* changedBy, const Date& timestamp);


    void save(std::ostream& os) const;
    static std::shared_ptr<Task> load(std::istream& is, const AppData& context);

    friend std::ostream& operator<<(std::ostream& os, const Task& task);
};