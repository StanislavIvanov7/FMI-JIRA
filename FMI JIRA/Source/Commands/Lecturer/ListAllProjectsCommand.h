#pragma once
#include "Commands/Base/Command.h"

class ListAllProjectsCommand : public Command {
public:
    static constexpr std::string_view NAME = "list-all-projects";
    static constexpr std::string_view DESCRIPTION = "Lists all projects in the system with their current status.";

    ListAllProjectsCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};