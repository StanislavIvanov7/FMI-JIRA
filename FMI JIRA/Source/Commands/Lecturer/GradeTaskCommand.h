#pragma once
#include "Commands/Base/Command.h"

class GradeTaskCommand : public Command {
public:
    static constexpr std::string_view NAME = "grade-task";
    static constexpr std::string_view DESCRIPTION = "Assigns a grade to a task by its ID.";

    GradeTaskCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};