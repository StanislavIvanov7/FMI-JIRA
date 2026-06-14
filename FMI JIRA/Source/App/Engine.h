#pragma once
#include <vector>
#include <memory>
#include "Commands/Base/Command.h"
#include "App/AppData.h"

class Engine {
private:
    AppData& data;
    std::vector<std::unique_ptr<Command>> commands;

    void processCommand(const std::string& input);

public:
    explicit Engine(AppData& data);
    void run();
};