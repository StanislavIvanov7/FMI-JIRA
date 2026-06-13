#pragma once
#include "Commands/Base/Command.h"

class ReviewTaskCommand : public Command {
public:
    static constexpr std::string_view NAME = "review-task";
    static constexpr std::string_view DESCRIPTION = "Sets a task status to 'Review'.";

    ReviewTaskCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};