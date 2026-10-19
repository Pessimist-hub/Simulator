#pragma once
#include <iostream>
#include "Point.hpp"

struct Player {
    Point position;
    int coins = 0;
    float movementSpeed = 1.0f;
    float pickupRange = 1.5f;

    Player();
    Player(const Point& _position, int _coins, float _speed, float _range);
    Player(const Player& other);

    Player& operator=(const Player& other);
    bool operator==(const Player& other) const;

    void Move(float dx, float dz, float mapWidth, float mapDepth);
    void BuySpeed();
    void BuyRange();
};

std::istream& operator>>(std::istream& in, Player& player);
std::ostream& operator<<(std::ostream& out, const Player& player);