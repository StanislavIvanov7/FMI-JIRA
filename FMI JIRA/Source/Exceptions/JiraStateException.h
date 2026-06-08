#pragma once
#include "AppException.h"
namespace ExceptionConstants {
	constexpr std::string_view STATE_ERROR_PREFIX = "[STATE Error] ";
}
class JiraStateException : public AppException
{
public:
	explicit JiraStateException(const std::string& message);
};
