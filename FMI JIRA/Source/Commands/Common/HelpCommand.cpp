#include "HelpCommand.h"
#include "App/AppData.h"
#include "Models/Users/User.h"
#include <iostream>
#include <iomanip>

HelpCommand::HelpCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool HelpCommand::requiresLogin() const {
    return false;
}

void HelpCommand::execute(const std::vector<std::string>& args, AppData& data) {
    std::cout << "\n==================== JIRA SYSTEM HELP ====================" << std::endl;

    std::cout << "[Common Commands]" << std::endl;
    std::cout << "  login <username> <password>  - Logs into the system." << std::endl;
    std::cout << "  logout                       - Logs out of the current session." << std::endl;
    std::cout << "  help                         - Displays this help menu." << std::endl;
    std::cout << "  view-profile                 - Views your personal profile details." << std::endl;
    std::cout << "  close                        - Closes the application." << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

   
    User* currentUser = data.getCurrentUser();
    if (!currentUser) {
        std::cout << "Notice: Please 'login' to see role-specific commands." << std::endl;
        std::cout << "==========================================================" << std::endl;
        return;
    }

    UserRole role = currentUser->getRole();

    if (role == UserRole::Student) {
        std::cout << "[Student Commands]" << std::endl;
        std::cout << "  join-project <project_name>  - Joins an existing project." << std::endl;
        std::cout << "  list-projects                - Lists all projects you are part of." << std::endl;
        std::cout << "  list-tasks                   - Lists tasks within your projects." << std::endl;
        std::cout << "  create-task <proj> <t> <p>   - Creates a task (type, priority)." << std::endl;
        std::cout << "  assign-task <task_id>        - Assigns a specific task to yourself." << std::endl;
        std::cout << "  change-status <id> <status>  - Changes the status of a task." << std::endl;
        std::cout << "  add-comment <task_id>        - Adds a comment to a task." << std::endl;
        std::cout << "  my-tasks                     - Shows tasks assigned to you." << std::endl;
        std::cout << "  upcoming-tasks               - Shows your upcoming deadlines." << std::endl;
        std::cout << "  search-tasks <keyword>       - Searches tasks by a keyword." << std::endl;
        std::cout << "  filter-tasks <criteria>      - Filters tasks by given criteria." << std::endl;
        std::cout << "  add-tag <task_id> <tag>      - Adds a custom tag to a task." << std::endl;
    }
   
    else if (role == UserRole::TeachingAssistant) {
        std::cout << "[Teaching Assistant Commands]" << std::endl;
        std::cout << "  approve-task <task_id>       - Approves a completed task." << std::endl;
        std::cout << "  review-task <task_id>        - Moves a task to 'In Review' status." << std::endl;
        std::cout << "  start-stage <stage_name>     - Starts a specific project stage." << std::endl;
        std::cout << "  finish-stage <stage_name>    - Finishes a specific project stage." << std::endl;
        std::cout << "  stage-report                 - Generates a report for the current stage." << std::endl;
        std::cout << "  move-task-to-stage <id> <st> - Moves a task to another stage." << std::endl;
    }
  
    else if (role == UserRole::Lecturer) {
        std::cout << "[Lecturer Commands]" << std::endl;
        std::cout << "  list-all-projects            - Lists every project in the system." << std::endl;
        std::cout << "  list-all-tasks               - Lists every task across all projects." << std::endl;
        std::cout << "  grade-task <task_id> <grade> - Places a grade on a specific task." << std::endl;
        std::cout << "  student-report <name>        - Generates a performance report for a student." << std::endl;
        std::cout << "  finalize-project <name>      - Finalizes a project, locking modifications." << std::endl;
        std::cout << "  approve-task <task_id>       - Approves a completed task." << std::endl;
        std::cout << "  review-task <task_id>        - Moves a task to 'In Review' status." << std::endl;
        std::cout << "  start-stage <stage_name>     - Starts a specific project stage." << std::endl;
        std::cout << "  finish-stage <stage_name>    - Finishes a specific project stage." << std::endl;
        std::cout << "  stage-report                 - Generates a report for the current stage." << std::endl;
        std::cout << "  move-task-to-stage <id> <st> - Moves a task to another stage." << std::endl;
    }

    else if (role == UserRole::Administrator) {
        std::cout << "[Administrator Commands]" << std::endl;
        std::cout << "  create-project <name>        - Creates a new project template." << std::endl;
        std::cout << "  archive-project <name>       - Archives an old or finished project." << std::endl;
        std::cout << "  add-user-to-project <u_p>    - Adds a user to a specific project." << std::endl;
        std::cout << "  remove-user <user>           - Permanently removes a user from the system." << std::endl;
        std::cout << "  save                         - Saves all data to files." << std::endl;
        std::cout << "  load                         - Loads all data from files." << std::endl;
    }

    std::cout << "==========================================================" << std::endl;
}