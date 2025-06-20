#pragma once
#include <stdexcept>
#include <string>

class AppError : public std::runtime_error {
public:
    int statusCode;

    explicit AppError(const std::string& message, int statusCode = 500)
        : std::runtime_error(message), statusCode(statusCode) {}
};