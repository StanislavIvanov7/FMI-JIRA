#pragma once
#include "Commands/Base/Command.h"

class AddUserToProjectCommand : public Command {
public:
    static constexpr std::string_view NAME = "add-user-to-project";
    static constexpr std::string_view DESCRIPTION = "Adds a user to a specific project.";

    AddUserToProjectCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};