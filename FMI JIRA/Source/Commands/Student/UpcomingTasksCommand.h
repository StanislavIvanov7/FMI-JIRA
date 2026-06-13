#pragma once
#include "Commands/Base/Command.h"

class UpcomingTasksCommand : public Command {
public:
    static constexpr std::string_view NAME = "upcoming-tasks";
    static constexpr std::string_view DESCRIPTION = "Lists all tasks with approaching deadlines.";

    UpcomingTasksCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};