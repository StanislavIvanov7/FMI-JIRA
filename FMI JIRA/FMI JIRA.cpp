#include <iostream>
#include <exception>
#include "App/AppData.h"
#include "App/Engine.h"

int main() {
   
    AppData data;

    
    try {
        data.load();
    }
    catch (const std::exception& e) {
        
        std::clog << "[System] No existing state found or load failed. Starting with empty system." << std::endl;
    }

    data.ensureDefaultAdmin();

    try {
        Engine engine(data);
        engine.run();
    }
    catch (const std::exception& e) {
        
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return 1;
    }

    
    return 0;
}