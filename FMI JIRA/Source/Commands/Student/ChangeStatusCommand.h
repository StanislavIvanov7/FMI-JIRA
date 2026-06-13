#pragma once
#include "Commands/Base/Command.h"

class ChangeStatusCommand : public Command {
public:
    static constexpr std::string_view NAME = "change-status";
    static constexpr std::string_view DESCRIPTION = "Changes the status of a task.";

    ChangeStatusCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};