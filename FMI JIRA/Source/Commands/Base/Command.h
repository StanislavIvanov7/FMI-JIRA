#pragma once
#include<string>
#include <vector>
#include <string_view> 

class AppData;

namespace CommandConstants {

	constexpr std::string_view ERR_COMMAND_NAME_EMPTY = "Command name cannot be empty.";
	constexpr std::string_view ERR_COMMAND_DESC_EMPTY = "Command description cannot be empty.";


	constexpr std::string_view MSG_SUCCESS_LOGIN = "Successfully logged in.";
	constexpr std::string_view MSG_SUCCESS_LOGOUT = "Successfully logged out.";
	constexpr std::string_view ERR_ALREADY_LOGGED_IN = "You are already logged in.";
	constexpr std::string_view ERR_INVALID_CREDENTIALS = "Invalid username or password.";

	constexpr std::string_view ERR_NOT_LOGGED_IN = "No user is currently logged in.";
	constexpr std::string_view MSG_EXITING = "Exiting application...";

	constexpr std::string_view ERR_INVALID_ARGS = "Invalid number of arguments provided.";
	constexpr std::string_view ERR_ACCESS_DENIED = "You do not have permission to execute this command.";
	constexpr std::string_view ERR_MUST_BE_LOGGED_IN = "You must be logged in to execute this command.";
}
class Command
{
	std::string name;
	std::string description;

public:
	Command(const std::string& name, const std::string& description);
	virtual ~Command() = default;

	const std::string& getName() const;
	const std::string& getDescription() const;

	virtual void execute(const std::vector<std::string>& args, AppData& data) = 0;
	virtual bool requiresLogin() const;
};