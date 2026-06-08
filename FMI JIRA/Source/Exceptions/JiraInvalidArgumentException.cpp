#include"JiraInvalidArgumentException.h"
JiraInvalidArgumentException::JiraInvalidArgumentException(const std::string& message)
    : AppException(std::string(ExceptionConstants::ARGUMENT_ERROR_PREFIX) + message) {
}