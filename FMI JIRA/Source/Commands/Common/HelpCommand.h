#pragma once
#include "Commands/Base/Command.h"

class HelpCommand : public Command {
public:
    static constexpr std::string_view NAME = "help";
    static constexpr std::string_view DESCRIPTION = "Displays all available commands.";

    HelpCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};