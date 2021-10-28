#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

namespace StringUtils {
    template <typename Out>
    void split(const std::string &s, char delim, Out result);

    std::vector<std::string> split(const std::string &s, char delim);

    bool compareCharPointers(char const *a, char const *b);

    struct cmp_str {
        bool operator() (char const *a, char const *b) const;
    };
}