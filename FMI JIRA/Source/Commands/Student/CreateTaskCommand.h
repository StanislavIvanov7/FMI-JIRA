#pragma once
#include "Commands/Base/Command.h"

class CreateTaskCommand : public Command {
public:
    static constexpr std::string_view NAME = "create-task";
    static constexpr std::string_view DESCRIPTION = "Creates a new task in a specified project.";

    CreateTaskCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};