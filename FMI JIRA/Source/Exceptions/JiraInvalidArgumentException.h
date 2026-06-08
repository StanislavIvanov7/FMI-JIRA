#pragma once
#include "AppException.h"

namespace ExceptionConstants {
    constexpr std::string_view ARGUMENT_ERROR_PREFIX = "[Argument Error] ";
}

class JiraInvalidArgumentException : public AppException{
public:
	explicit JiraInvalidArgumentException(const std::string& message);
};

