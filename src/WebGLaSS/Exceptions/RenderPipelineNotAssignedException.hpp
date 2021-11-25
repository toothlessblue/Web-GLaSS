#pragma once
#include <exception>

struct RenderPipelineNotAssignedException: public std::exception {
    const char* what() const throw();
};