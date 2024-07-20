#pragma once
#include "common.h"

// FileLoadException class for file loading errors
class FileLoadException : public std::runtime_error {
public:
    /**
     * Constructor to initialize the FileLoadException with an error message.
     * @param message The error message to be stored.
     */
    explicit FileLoadException(const std::string& message) : std::runtime_error(message) {}
};
