#pragma once
#include "Commands/Base/Command.h"

class StageReportCommand : public Command {
public:
    static constexpr std::string_view NAME = "stage-report";
    static constexpr std::string_view DESCRIPTION = "Shows a report for all stages in all projects the user is part of.";

    StageReportCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};