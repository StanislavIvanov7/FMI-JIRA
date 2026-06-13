#pragma once
#include "Commands/Base/Command.h"

class LoginCommand : public Command {
public:
    static constexpr std::string_view NAME = "login";
    static constexpr std::string_view DESCRIPTION = "Authenticates a user into the system.";
    
    LoginCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};