#pragma once
#include "Commands/Base/Command.h"

class AddStageCommand : public Command {
public:
    static constexpr std::string_view NAME = "add-stage";
    static constexpr std::string_view DESCRIPTION = "Adds a new stage to a project.";

    AddStageCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override { return true; }
};