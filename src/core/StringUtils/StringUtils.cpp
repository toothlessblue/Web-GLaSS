#include "StringUtils.hpp"

namespace StringUtils {
    template <typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::istringstream iss(s);
        std::string item;
        while (std::getline(iss, item, delim)) {
            *result++ = item;
        }
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }

    bool compareCharPointers(char const *a, char const *b) {
        return std::strcmp(a, b) < 0;
    }

    bool cmp_str::operator() (char const *a, char const *b) const {
        return compareCharPointers(a, b);
    }
}