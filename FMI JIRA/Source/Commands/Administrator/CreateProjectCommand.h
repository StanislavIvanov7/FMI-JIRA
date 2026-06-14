#pragma once
#include "Commands/Base/Command.h"

class CreateProjectCommand : public Command {
public:
    static constexpr std::string_view NAME = "create-project";
    static constexpr std::string_view DESCRIPTION = "Creates a new project.";

    CreateProjectCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};