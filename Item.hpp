#pragma once
#include <string>
#include <iostream>
#include "Point.hpp"

struct Item {
    std::string name;
    Point position;
    int value = 0;
    float fallSpeed = 0.0f;
    bool falling = false;

    Item();
    Item(const std::string& _name, const Point& _position, int _value);
    Item(const Item& other);

    Item& operator=(const Item& other);
    bool operator==(const Item& other) const;
    bool operator!=(const Item& other) const;
};

std::istream& operator>>(std::istream& in, Item& item);
std::ostream& operator<<(std::ostream& out, const Item& item);