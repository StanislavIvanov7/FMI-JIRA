#include "JiraDateFormatException.h"

JiraDateFormatException::JiraDateFormatException(const std::string& message)
	: AppException(std::string(ExceptionConstants::DATE_ERROR_PREFIX) + message) {}