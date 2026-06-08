#pragma once
#include "AppException.h"

namespace ExceptionConstants {
   
    constexpr std::string_view DATE_ERROR_PREFIX = "[Date Format Error] ";
}
class JiraDateFormatException : public AppException {
public:
    explicit JiraDateFormatException(const std::string& message);
};