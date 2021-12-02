#include "Math.hpp"
#include <iostream>

float Math::lerp(float a, float b, float t) {
    return (a * (1.0 - t)) + (b * t);
}

Math::RollingAverage::RollingAverage(int length, bool ignoreZeros): ignoreZeros(ignoreZeros), length(length) {
    for (int i = 0; i < this->length; i++) {
        this->values.push_back(0);
    }
}

void Math::RollingAverage::addValue(float value) {
    this->total -= this->values[this->currentIndex];
    this->values[this->currentIndex] = value;
    this->total += this->values[this->currentIndex];

    this->currentIndex++;
    
    if (this->currentIndex > this->maxIndex) this->maxIndex = this->currentIndex;

    if (this->currentIndex >= this->length) {
        this->currentIndex = 0;
    }
}

float Math::RollingAverage::getAverage() {
    return this->total / this->maxIndex;
}