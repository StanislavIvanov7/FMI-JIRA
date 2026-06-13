#pragma once
#include <string>
#include <vector>
#include <memory>
#include <string_view>
#include <iostream>
#include "Models/Stage/Stage.h"
#include "Utils/Enums/ProjectStatus.h"

class User;
class Task;

namespace ProjectConstants {
	constexpr std::string_view ERROR_EMPTY_NAME = "Project name cannot be empty.";
	constexpr std::string_view ERROR_STAGE_NOT_FOUND = "Requested stage was not found in this project.";
	constexpr std::string_view ERROR_STAGE_ALREADY_EXISTS = "A stage with this name already exists in the project.";
	constexpr std::string_view ERROR_MEMBER_ALREADY_EXISTS = "User is already a member of this project.";
	constexpr std::string_view ERROR_MEMBER_NOT_FOUND = "User is not a member of this project.";
	constexpr std::string_view ERROR_PROJECT_NOT_FOUND = "Project with this name does not exist.";
	constexpr std::string_view MSG_NO_TASKS = "No tasks found in project: ";
	constexpr std::string_view MSG_PROJECT_TASKS = "Tasks in project ";
	constexpr std::string_view ERROR_TASK_NOT_FOUND = "Task with the requested ID was not found.";
	constexpr std::string_view ERROR_ACCESS_DENIED = "You are not a member of this project and cannot assign tasks to yourself.";
}

class Project {
private:
	std::string name;
	std::string description;
	std::vector<User*> members;
	std::vector<std::shared_ptr<Task>> tasks;
	std::vector<Stage> stages;
	ProjectStatus status;

public:
	Project() = default;
	Project(const std::string& name, const std::string& description = "");


	const std::string& getName() const;
	const std::string& getDescription() const;
	ProjectStatus getStatus() const;
	const std::vector<User*>& getMembers() const;
	const std::vector<std::shared_ptr<Task>>& getTasks() const;
	const std::vector<Stage>& getStages() const;
	std::vector<Stage>& getStages();

	void setDescription(const std::string& description);
	void setStatus(ProjectStatus status);

	void addMember(User* user);
	void removeMember(const std::string& username);
	bool hasMember(const std::string& username) const;
	User* findMember(const std::string& username);
	const User* findMember(const std::string& username) const;

	std::shared_ptr<Task> addTask(std::shared_ptr<Task> task);
	std::shared_ptr<Task> findTask(size_t taskId) const;
	std::shared_ptr<Task> findTaskByFormattedId(const std::string& formattedId) const;

	void addStage(const Stage& stage);
	Stage* findStage(const std::string& stageName);
	const Stage* findStage(const std::string& stageName) const;

	void finalize();
	void archive();

	friend std::ostream& operator<<(std::ostream& os, const Project& project);
};