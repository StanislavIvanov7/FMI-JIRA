#include "Task.h"
#include "Models/Users/User.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include <format>
#include <algorithm>

size_t Task::idGen = 100;


Task::Task(const std::string& title, const std::string& description, TaskType type, TaskPriority priority, const Date& deadline)
    : id(++idGen),
    title(title),
    description(description),
    type(type),
    priority(priority),
    status(TaskStatus::ToDo),
    assignee(nullptr),
    deadline(deadline),
    points(TaskConstants::INITIAL_POINTS),
    grade(std::nullopt),
    approved(TaskConstants::INITIAL_APPROVED_STATUS)
{
    if (this->title.empty()) throw JiraInvalidArgumentException(std::string(TaskConstants::ERROR_EMPTY_TITLE));
    if (this->description.empty()) throw JiraInvalidArgumentException(std::string(TaskConstants::ERROR_EMPTY_DESCRIPTION));
}


Task::Task(size_t id, const std::string& title, const std::string& description,
    TaskType type, TaskPriority priority, TaskStatus status,
    const User* assignee, const Date& deadline, int points,
    std::optional<double> grade, bool approved, std::vector<Comment> comments,
    std::vector<std::string> tags, std::vector<HistoryEntry> changeHistory)
    : id(id),
    title(title),
    description(description),
    type(type),
    priority(priority),
    status(status),
    assignee(assignee),
    deadline(deadline),
    points(points),
    grade(grade),
    approved(approved),
    comments(comments),
    tags(tags),
    changeHistory(changeHistory) {

    if (id >= idGen) {
        idGen = id + 1;
    }
}


size_t Task::getId() const { return id; }
std::string Task::getFormattedId() const { return std::format("FMI-{}", id); }
const std::string& Task::getTitle() const { return title; }
const std::string& Task::getDescription() const { return description; }
TaskType Task::getType() const { return type; }
TaskPriority Task::getPriority() const { return priority; }
TaskStatus Task::getStatus() const { return status; }
const User* Task::getAssignee() const { return assignee; }
const Date& Task::getDeadline() const { return deadline; }
int Task::getPoints() const { return points; }
std::optional<double> Task::getGrade() const { return grade; }
bool Task::isApproved() const { return approved; }

const std::vector<Comment>& Task::getComments() const { return comments; }
const std::vector<std::string>& Task::getTags() const { return tags; }
const std::vector<HistoryEntry>& Task::getChangeHistory() const { return changeHistory; }

void Task::setTitle(const std::string& newTitle, const User* changedBy, const Date& timestamp) {
    if (newTitle.empty()) throw JiraInvalidArgumentException(std::string(TaskConstants::ERROR_EMPTY_TITLE));
    changeHistory.emplace_back(changedBy, std::string(TaskConstants::FIELD_TITLE), title, newTitle, timestamp);
    title = newTitle;
}

void Task::setDescription(const std::string& newDescription, const User* changedBy, const Date& timestamp) {
    if (newDescription.empty()) throw JiraInvalidArgumentException(std::string(TaskConstants::ERROR_EMPTY_DESCRIPTION));
    changeHistory.emplace_back(changedBy, std::string(TaskConstants::FIELD_DESCRIPTION), description, newDescription, timestamp);
    description = newDescription;
}

void Task::setPriority(TaskPriority newPriority, const User* changedBy, const Date& timestamp) {
    changeHistory.emplace_back(changedBy, std::string(TaskConstants::FIELD_PRIORITY), toString(priority), toString(newPriority), timestamp);
    priority = newPriority;
}

void Task::setStatus(TaskStatus newStatus, const User* changedBy, const Date& timestamp) {
    changeHistory.emplace_back(changedBy, std::string(TaskConstants::FIELD_STATUS), toString(status), toString(newStatus), timestamp);
    status = newStatus;
}

void Task::setAssignee(const User* user, const User* changedBy, const Date& timestamp) {
    std::string oldAssignee = assignee ? assignee->getUsername() : std::string(TaskConstants::VALUE_UNASSIGNED);
    std::string newAssignee = user ? user->getUsername() : std::string(TaskConstants::VALUE_UNASSIGNED);
    changeHistory.emplace_back(changedBy, std::string(TaskConstants::FIELD_ASSIGNEE), oldAssignee, newAssignee, timestamp);
    assignee = user;
}

void Task::setDeadline(const Date& newDeadline, const User* changedBy, const Date& timestamp) {
    changeHistory.emplace_back(changedBy, std::string(TaskConstants::FIELD_DEADLINE), deadline.toString(), newDeadline.toString(), timestamp);
    deadline = newDeadline;
}

void Task::setPoints(int newPoints, const User* changedBy, const Date& timestamp) {
    if (newPoints < 0) throw JiraInvalidArgumentException(std::string(TaskConstants::ERROR_INVALID_POINTS));
    changeHistory.emplace_back(changedBy, std::string(TaskConstants::FIELD_POINTS), std::to_string(points), std::to_string(newPoints), timestamp);
    points = newPoints;
}

void Task::setGrade(double newGrade, const User* changedBy, const Date& timestamp) {
    if (newGrade < 2.0 || newGrade > 6.0) throw JiraInvalidArgumentException(std::string(TaskConstants::ERROR_INVALID_GRADE));

    std::string oldGradeStr = grade.has_value() ? std::format("{:.2f}", grade.value()) : "None";
    changeHistory.emplace_back(changedBy, std::string(TaskConstants::FIELD_GRADE), oldGradeStr, std::format("{:.2f}", newGrade), timestamp);
    grade = newGrade;
}

void Task::setApproved(bool newApproved, const User* changedBy, const Date& timestamp) {
    std::string oldApprovedStr = this->approved ? std::string(TaskConstants::VALUE_TRUE) : std::string(TaskConstants::VALUE_FALSE);
    std::string newApprovedStr = newApproved ? std::string(TaskConstants::VALUE_TRUE) : std::string(TaskConstants::VALUE_FALSE);
    changeHistory.emplace_back(changedBy, std::string(TaskConstants::FIELD_APPROVED), oldApprovedStr, newApprovedStr, timestamp);
    this->approved = newApproved;
}

void Task::addComment(const Comment& comment) { comments.push_back(comment); }

void Task::addTag(const std::string& tag, const User* changedBy, const Date& timestamp) {
    if (std::find(tags.begin(), tags.end(), tag) == tags.end()) {
        changeHistory.emplace_back(changedBy, std::string(TaskConstants::FIELD_TAG_ADDED), std::string(TaskConstants::VALUE_NONE), tag, timestamp);
        tags.push_back(tag);
    }
}

std::ostream& operator<<(std::ostream& os, const Task& task) {
    std::string gradeStr = task.grade.has_value() ? std::format("{:.2f}", task.grade.value()) : "Not Graded";

    os << std::format("- {} | {} | {} | Priority: {} | Grade: {}",
        task.getFormattedId(),
        task.title,
        toString(task.status),
        toString(task.priority),
        gradeStr);
    return os;
}