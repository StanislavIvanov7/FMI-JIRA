#pragma once
#include "Commands/Base/Command.h"

class SearchTasksCommand : public Command {
public:
    static constexpr std::string_view NAME = "search-tasks";
    static constexpr std::string_view DESCRIPTION = "Searches for tasks containing a specific keyword.";

    SearchTasksCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};