#pragma once
#include "Commands/Base/Command.h"

class SaveCommand : public Command {
public:
    static constexpr std::string_view NAME = "save";
    static constexpr std::string_view DESCRIPTION = "Saves the current system state to a file.";

    SaveCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};