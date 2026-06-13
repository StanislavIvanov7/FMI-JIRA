#pragma once
#include "Commands/Base/Command.h"

class JoinProjectCommand : public Command {
public:
    static constexpr std::string_view NAME = "join-project";
    static constexpr std::string_view DESCRIPTION = "Adds the current student to a project.";

    JoinProjectCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};