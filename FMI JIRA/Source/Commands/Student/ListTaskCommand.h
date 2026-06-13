#pragma once
#include "Commands/Base/Command.h"

class ListTasksCommand : public Command {
public:
    static constexpr std::string_view NAME = "list-tasks";
    static constexpr std::string_view DESCRIPTION = "Lists all tasks for a specified project.";

    ListTasksCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};