#pragma once
#include <cmath>
#include <iostream>

struct Point {
    float x = 0;
    float y = 0;
    float z = 0;

    Point(float _x = 0, float _y = 0, float _z = 0); 
    Point(const Point& other);                       

    Point& operator=(const Point& other);
    bool operator==(const Point& other) const;

    float DistanceTo(const Point& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
};

std::istream& operator>>(std::istream& in, Point& point);
std::ostream& operator<<(std::ostream& out, const Point& point);