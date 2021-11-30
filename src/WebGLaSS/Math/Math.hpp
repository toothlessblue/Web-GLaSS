#pragma once
#include <vector>

namespace Math {
    float lerp(float a, float b, float t);

    class RollingAverage {
    public:
        RollingAverage(int length);

        void addValue(float value);
        float getAverage();

        int length;
    private:
        std::vector<float> values;
        int currentIndex = 0;
        float total = 0;
    };
}
