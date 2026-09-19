#pragma once
#include "Point.hpp"

struct Player {
    Point position;
    int coins = 0;
    float movementSpeed = 1.0f; 
    float pickupRange = 1.5f;   

    void Move(float dx, float dz, float mapWidth, float mapDepth);
    void BuySpeed();
    void BuyRange();
};