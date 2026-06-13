#pragma once
#include "Commands/Base/Command.h"

class MoveTaskToStageCommand : public Command {
public:
    static constexpr std::string_view NAME = "move-task-to-stage";
    static constexpr std::string_view DESCRIPTION = "Moves a task to a new stage.";

    MoveTaskToStageCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};