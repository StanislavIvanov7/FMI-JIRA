#pragma once
#include "Commands/Base/Command.h"

class AssignTaskCommand : public Command {
public:
    static constexpr std::string_view NAME = "assign-task";
    static constexpr std::string_view DESCRIPTION = "Assigns a task to a user in the project.";

    AssignTaskCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};