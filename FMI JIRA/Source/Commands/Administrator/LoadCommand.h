#pragma once
#include "Commands/Base/Command.h"

class LoadCommand : public Command {
public:
    static constexpr std::string_view NAME = "load";
    static constexpr std::string_view DESCRIPTION = "Loads the system state from the data files.";

    LoadCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};