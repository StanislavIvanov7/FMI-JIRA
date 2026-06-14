#include "LoadCommand.h"
#include "App/AppData.h"                          
#include "Models/Users/User.h"                    
#include "Exceptions/JiraInvalidArgumentException.h" 
#include "Utils/Enums/UserRole.h"                  
#include <iostream>

LoadCommand::LoadCommand()
    : Command(std::string(NAME), std::string(DESCRIPTION)) {
}

bool LoadCommand::requiresLogin() const {
    return true;
}

void LoadCommand::execute(const std::vector<std::string>& args, AppData& data) {
   
    if (!args.empty()) {
        throw JiraInvalidArgumentException("Error: Command 'load' does not accept any arguments.");
    }

   
    User* currentUser = data.getCurrentUser();
    if (!currentUser || currentUser->getRole() != UserRole::Administrator) {
        throw JiraInvalidArgumentException("Permission Denied: Only Administrators can load the system state.");
    }

 
    try {
        data.load(); 
        std::cout << "[System] All data (users, projects, tasks) loaded successfully." << std::endl;
    }
    catch (const std::exception& e) {
        
        throw JiraInvalidArgumentException("Load Failed: " + std::string(e.what()));
    }
}