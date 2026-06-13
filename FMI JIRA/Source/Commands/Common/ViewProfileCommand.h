#pragma once
#include "Commands/Base/Command.h"

class ViewProfileCommand : public Command {
public:
    static constexpr std::string_view NAME = "view-profile";
    static constexpr std::string_view DESCRIPTION = "Displays the current user's profile information.";

    ViewProfileCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};