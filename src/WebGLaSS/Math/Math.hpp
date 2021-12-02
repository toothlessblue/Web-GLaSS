#pragma once
#include <vector>

namespace Math {
    float lerp(float a, float b, float t);

    class RollingAverage {
    public:
        int length;
        bool ignoreZeros;

        RollingAverage(int length, bool ignoreZeros = true);

        void addValue(float value);
        float getAverage();
    private:
        std::vector<float> values;
        int currentIndex = 0;
        int maxIndex = 0;
        float total = 0;
    };
}
