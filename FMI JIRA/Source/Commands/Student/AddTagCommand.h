#pragma once
#include "Commands/Base/Command.h"

class AddTagCommand : public Command {
public:
    static constexpr std::string_view NAME = "add-tag";
    static constexpr std::string_view DESCRIPTION = "Adds a tag to a specific task.";

    AddTagCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};