#pragma once
#include "Commands/Base/Command.h"

class StartStageCommand : public Command {
public:
    static constexpr std::string_view NAME = "start-stage";
    static constexpr std::string_view DESCRIPTION = "Starts a specific stage in a project.";

    StartStageCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};