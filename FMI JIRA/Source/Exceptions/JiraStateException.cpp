#include "JiraStateException.h"

JiraStateException::JiraStateException(const std::string& message)
	: AppException(message) {
}
