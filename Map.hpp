#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include "Item.hpp"

struct Map {
    float width = 50.0f;
    float depth = 40.0f;
    std::vector<Item> trash;

    Map();
    Map(float _width, float _depth);
    Map(const Map& other);

    Map& operator=(const Map& other);
    bool operator==(const Map& other) const;
    bool operator!=(const Map& other) const;

    void Init();
    int TrashLeft() const;
    int Collect(const Point& playerPos, float range);
    void SortByValue();
};

std::istream& operator>>(std::istream& in, Map& map);
std::ostream& operator<<(std::ostream& out, const Map& map);