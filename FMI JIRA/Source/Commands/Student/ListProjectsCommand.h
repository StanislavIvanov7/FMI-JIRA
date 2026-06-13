#pragma once
#include "Commands/Base/Command.h"

class ListProjectsCommand : public Command {
public:
    static constexpr std::string_view NAME = "list-projects";
    static constexpr std::string_view DESCRIPTION = "Lists all available projects in the system.";

    ListProjectsCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};