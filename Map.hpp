#pragma once
#include <vector>
#include <iostream>
#include "Item.hpp"

struct Map {
    float width = 10;
    float depth = 10;
    std::vector<Item> trash;

    Map();
    Map(float _width, float _depth);
    Map(const Map& other);

    Map& operator=(const Map& other);
    bool operator==(const Map& other) const;

    void Init();
    int TrashLeft();
    int Collect(Point playerPos, float range);
};

std::istream& operator>>(std::istream& in, Map& map);
std::ostream& operator<<(std::ostream& out, const Map& map);