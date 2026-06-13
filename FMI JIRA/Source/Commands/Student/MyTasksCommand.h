#pragma once
#include "Commands/Base/Command.h"

class MyTasksCommand : public Command {
public:
    static constexpr std::string_view NAME = "my-tasks";
    static constexpr std::string_view DESCRIPTION = "Lists all tasks assigned to the current user.";

    MyTasksCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};