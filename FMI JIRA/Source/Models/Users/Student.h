#pragma once

#include "User.h"
#include <string>
#include <string_view>

namespace StudentConstants {
   

    constexpr int INITIAL_COUNTER_VALUE = 0;
    constexpr double INITIAL_SCORE_VALUE = 0.0;
}

class Student : public User {
private:
 
    int completedTasks = StudentConstants::INITIAL_COUNTER_VALUE;
    int inProgressTasks = StudentConstants::INITIAL_COUNTER_VALUE;
    double performanceScore = StudentConstants::INITIAL_SCORE_VALUE;

   

public:

    Student(const std::string& username, const std::string& password);
    Student(size_t id, const std::string& username, const std::string& password,
        int completedTasks, int inProgressTasks, double performanceScore);

    int getCompletedTasks() const;
    int getInProgressTasks() const;
    double getPerformanceScore() const;

    void incrementCompletedTasks();
    void incrementInProgressTasks();
    void decrementInProgressTasks();
    void addPerformancePoints(double points);

    
    void save(std::ostream& os) const override;
    void loadSubclass(std::istream& is) override;

    std::unique_ptr<User> clone() const override;
    void displayInfo(std::ostream& os) const override;
};