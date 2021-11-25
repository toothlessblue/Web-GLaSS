#include "Math.hpp"

float Math::lerp(float a, float b, float t) {
    return (a * (1.0 - t)) + (b * t);
}