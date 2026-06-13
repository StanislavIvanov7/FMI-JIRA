#pragma once
#include "Commands/Base/Command.h"

class ApproveTaskCommand : public Command {
public:
    static constexpr std::string_view NAME = "approve-task";
    static constexpr std::string_view DESCRIPTION = "Approves a specific task.";

    ApproveTaskCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};