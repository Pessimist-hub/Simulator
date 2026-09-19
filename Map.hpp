#pragma once
#include <vector>
#include "Item.hpp"


struct Map {
    float width = 10; 
    float depth = 10; 
    std::vector<Item> trash;

    void Init();
    int TrashLeft();
    int Collect(Point playerPos, float range); 
};