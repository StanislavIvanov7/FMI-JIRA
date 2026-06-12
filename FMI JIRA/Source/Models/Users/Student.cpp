#include "Student.h"
#include "Exceptions/JiraInvalidArgumentException.h"

Student::Student(size_t id, const std::string& username, const std::string& password, const std::string& facultyNumber)
    : User(id, username, password, UserRole::Student),
    facultyNumber(validateFacultyNumber(facultyNumber)) {
}

Student::Student(const std::string& username, const std::string& password, const std::string& facultyNumber)
    : User(username, password, UserRole::Student),
    facultyNumber(validateFacultyNumber(facultyNumber))
{
  
}

std::unique_ptr<User> Student::clone() const {
    return std::make_unique<Student>(*this);
}

const std::string& Student::getFacultyNumber() const {
    return facultyNumber;
}

int Student::getCompletedTasks() const {
    return completedTasks; 
}

int Student::getInProgressTasks() const { 
    return inProgressTasks; 
}

double Student::getPerformanceScore() const { 
    return performanceScore; 
}

void Student::incrementCompletedTasks() {

    completedTasks++;
}

void Student::incrementInProgressTasks() {
    inProgressTasks++;
}

void Student::decrementInProgressTasks() {
    if (inProgressTasks > StudentConstants::INITIAL_COUNTER_VALUE) {
        inProgressTasks--;
    }
}

void Student::addPerformancePoints(double points) {
    performanceScore += points;
}

void Student::displayInfo(std::ostream& os) const {

    User::displayInfo(os);

    os << " | FN: " << facultyNumber
        << " | Completed tasks: " << completedTasks
        << " | In progress: " << inProgressTasks
        << " | Performance score: " << performanceScore;
}

const std::string& Student::validateFacultyNumber(const std::string& fn) {
    if (fn.empty()) {
        throw JiraInvalidArgumentException(std::string(StudentConstants::ERROR_EMPTY_FACULTY_NUMBER));
    }
    return fn;
}