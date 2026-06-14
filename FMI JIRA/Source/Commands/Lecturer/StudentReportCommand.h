#pragma once
#include "Commands/Base/Command.h"

class StudentReportCommand : public Command {
public:
    static constexpr std::string_view NAME = "student-report";
    static constexpr std::string_view DESCRIPTION = "Generates a report for a specific student, showing all their tasks and grades.";

    StudentReportCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};