#pragma once
#include "Commands/Base/Command.h"

class ArchiveProjectCommand : public Command {
public:
    static constexpr std::string_view NAME = "archive-project";
    static constexpr std::string_view DESCRIPTION = "Archives an existing project.";

    ArchiveProjectCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};