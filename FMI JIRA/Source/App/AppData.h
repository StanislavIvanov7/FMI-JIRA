#pragma once
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <optional>

class User;
class Project;

class AppData {
private:
	std::vector<std::unique_ptr<User>> users;
	std::vector<std::shared_ptr<Project>> projects;

	User* currentUser = nullptr;
	bool running = true;

public:
	AppData() = default;

	AppData(const AppData&) = delete;
	AppData& operator=(const AppData&) = delete;

	bool isRunning() const;
	void stop();

	void addUser(std::unique_ptr<User> user);
	User* findUser(const std::string& username) const;
	bool removeUser(const std::string& username);

	void setCurrentUser(User* user);
	User* getCurrentUser() const;
	bool isUserLoggedIn() const;
	void logout();

	void addProject(std::shared_ptr<Project> project);
	Project* findProject(const std::string& name) const;
	const std::vector<std::shared_ptr<Project>>& getProjects() const;

	void save() const;
	void load();
};