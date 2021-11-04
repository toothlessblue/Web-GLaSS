#include "VectorUtils.hpp"

namespace Utils {
    namespace Vector {
        template <class T> T remove(std::vector<T> vector, T value) {
            vector.erase(std::remove(vector.begin(), vector.end(), value), vector.end());
            return value;
        }
    }
}