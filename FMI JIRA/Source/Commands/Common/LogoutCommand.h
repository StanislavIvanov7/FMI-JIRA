#pragma once
#include "../Base/Command.h"

class LogoutCommand : public Command {
public:
    static constexpr std::string_view NAME = "logout";
    static constexpr std::string_view DESCRIPTION = "Logs the current user out of the system.";

    LogoutCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};