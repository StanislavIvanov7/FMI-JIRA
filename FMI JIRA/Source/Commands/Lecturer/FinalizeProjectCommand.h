#pragma once
#include "Commands/Base/Command.h"

class FinalizeProjectCommand : public Command {
public:
    static constexpr std::string_view NAME = "finalize-project";
    static constexpr std::string_view DESCRIPTION = "Finalizes a project, preventing further task modifications.";

    FinalizeProjectCommand();
    void execute(const std::vector<std::string>& args, AppData& data) override;
    bool requiresLogin() const override;
};