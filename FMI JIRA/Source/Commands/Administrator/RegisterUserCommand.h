#pragma once
#include "Commands/Base/Command.h"

class RegisterUserCommand : public Command {
public:
    static constexpr std::string_view NAME = "register";
    static constexpr std::string_view DESCRIPTION = "Registers a new user into the system (Admin only).";

    RegisterUserCommand();

    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};