#include "SaveCommand.h"
#include "App/AppData.h"                       
#include "Models/Users/User.h"                    
#include "Exceptions/JiraInvalidArgumentException.h" 
#include "Utils/Enums/UserRole.h"                    
#include <iostream>

SaveCommand::SaveCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool SaveCommand::requiresLogin() const {
    return true;
}

void SaveCommand::execute(const std::vector<std::string>& args, AppData& data) {
   
    if (!args.empty()) {
        throw JiraInvalidArgumentException("Error: Command 'save' does not accept any arguments.");
    }

    User* currentUser = data.getCurrentUser();
    if (!currentUser || currentUser->getRole() != UserRole::Administrator) {
        throw JiraInvalidArgumentException("Permission Denied: Only Administrators can save the system state.");
    }

  
    try {
        data.save(); 
        std::cout << "[System] All data (users, projects, tasks) saved successfully." << std::endl;
    }
    catch (const std::exception& e) {
       
        throw JiraInvalidArgumentException("Save Failed: " + std::string(e.what()));
    }
}