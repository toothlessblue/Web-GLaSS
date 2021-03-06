#include "VectorUtils.hpp"

namespace Utils {
    template <typename T> T Vector::remove(std::vector<T> vector, T value) {
        vector.erase(std::remove(vector.begin(), vector.end(), value), vector.end());
        return value;
    }
}

template Transform* Utils::Vector::remove(std::vector<Transform*> vector, Transform* value);