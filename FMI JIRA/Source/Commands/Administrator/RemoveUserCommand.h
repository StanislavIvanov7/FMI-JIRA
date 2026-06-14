#pragma once
#include "Commands/Base/Command.h"

class RemoveUserCommand : public Command {
public:
    static constexpr std::string_view NAME = "remove-user";
    static constexpr std::string_view DESCRIPTION = "Removes a user from the system entirely.";

    RemoveUserCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};