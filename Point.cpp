#include "Point.hpp"

Point::Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

Point::Point(const Point& other) : x(other.x), y(other.y), z(other.z) {}

Point& Point::operator=(const Point& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y && z == other.z;
}

std::istream& operator>>(std::istream& in, Point& point) {
    float x, y, z;
    in >> x >> y >> z;
    point = Point(x, y, z);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << point.x << " " << point.y << " " << point.z;
    return out;
}
