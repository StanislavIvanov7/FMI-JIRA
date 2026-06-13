#pragma once
#include "Commands/Base/Command.h"

class CloseCommand : public Command {
public:
    static constexpr std::string_view NAME = "close";
    static constexpr std::string_view DESCRIPTION = "Terminates the application.";

    CloseCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};