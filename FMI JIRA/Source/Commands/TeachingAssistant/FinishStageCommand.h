#pragma once
#include "Commands/Base/Command.h"

class FinishStageCommand : public Command {
public:
    static constexpr std::string_view NAME = "finish-stage";
    static constexpr std::string_view DESCRIPTION = "Finishes a specific stage in a project.";

    FinishStageCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};