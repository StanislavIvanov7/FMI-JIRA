#pragma once
#include "Commands/Base/Command.h"

class AddCommentCommand : public Command {
public:
    static constexpr std::string_view NAME = "add-comment";
    static constexpr std::string_view DESCRIPTION = "Adds a comment to a task.";

    AddCommentCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};