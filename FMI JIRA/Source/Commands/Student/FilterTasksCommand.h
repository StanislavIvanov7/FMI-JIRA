#pragma once
#include "Commands/Base/Command.h"

class FilterTasksCommand : public Command {
public:
    static constexpr std::string_view NAME = "filter-tasks";
    static constexpr std::string_view DESCRIPTION = "Filters tasks by status or priority.";

    FilterTasksCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};