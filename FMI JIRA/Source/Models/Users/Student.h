#pragma once

#include "User.h"
#include <string>
#include <string_view>

namespace StudentConstants {
    constexpr std::string_view ERROR_EMPTY_FACULTY_NUMBER = "Faculty number cannot be empty.";

    constexpr int INITIAL_COUNTER_VALUE = 0;
    constexpr double INITIAL_SCORE_VALUE = 0.0;
}

class Student : public User {
private:
    std::string facultyNumber;
    int completedTasks = StudentConstants::INITIAL_COUNTER_VALUE;
    int inProgressTasks = StudentConstants::INITIAL_COUNTER_VALUE;
    double performanceScore = StudentConstants::INITIAL_SCORE_VALUE;

public:

    Student(const std::string& username, const std::string& password, const std::string& facultyNumber);

    const std::string& getFacultyNumber() const;
    int getCompletedTasks() const;
    int getInProgressTasks() const;
    double getPerformanceScore() const;

    void incrementCompletedTasks();
    void incrementInProgressTasks();
    void decrementInProgressTasks();
    void addPerformancePoints(double points);

    std::unique_ptr<User> clone() const override;
    void displayInfo(std::ostream& os) const override;
};