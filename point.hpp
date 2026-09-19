#pragma once
#include <cmath>

struct Point {
    float x = 0;
    float y = 0;
    float z = 0;

    float DistanceTo(Point other) {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
};