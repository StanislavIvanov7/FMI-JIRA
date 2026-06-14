#include "Student.h"
#include "Exceptions/JiraInvalidArgumentException.h"

Student::Student(size_t id, const std::string& username, 
    const std::string& password,
    int completedTasks, int inProgressTasks, double performanceScore)
    : User(id, username, password, UserRole::Student),
    completedTasks(completedTasks),
    inProgressTasks(inProgressTasks),
    performanceScore(performanceScore) {
}

Student::Student(const std::string& username, const std::string& password)
    : User(username, password, UserRole::Student)
{
  
}

std::unique_ptr<User> Student::clone() const {
    return std::make_unique<Student>(*this);
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

void Student::save(std::ostream& os) const {
    User::save(os); 
    os  << completedTasks << "\n"
        << inProgressTasks << "\n"
        << performanceScore << "\n";
}

void Student::loadSubclass(std::istream& is) {

   
    int completed, inProgress;
    double score;

    is >> completed >> inProgress >> score;
    is.ignore(); 

    this->completedTasks = completed;
    this->inProgressTasks = inProgress;
    this->performanceScore = score;
}
void Student::displayInfo(std::ostream& os) const {

    User::displayInfo(os);

    os 
        << " | Completed tasks: " << completedTasks
        << " | In progress: " << inProgressTasks
        << " | Performance score: " << performanceScore;
}

