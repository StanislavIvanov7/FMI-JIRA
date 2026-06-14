#pragma once
#include "Commands/Base/Command.h"

class ListAllTasksCommand : public Command {
public:
    static constexpr std::string_view NAME = "list-all-tasks";
    static constexpr std::string_view DESCRIPTION = "Lists all tasks across all projects in the system.";

    ListAllTasksCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};