#pragma once
#include<string>
#include<stdexcept>
#include<string_view>
class AppException : public std::runtime_error {
public:
  
    explicit AppException(const std::string& message);

    virtual ~AppException() noexcept override = default;
};
