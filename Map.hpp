#pragma once
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "Item.hpp"

enum class DecorationType {
    Tree,
    Rock,
    Bush,
    Flower,
    Palm
};

struct Decoration {
    Point position;
    DecorationType type = DecorationType::Rock;
    float scale = 1.0f;
    float collisionHalfExtent = 0.0f;
};

struct Map {
    float width = 50.0f;
    float depth = 40.0f;
    std::vector<Item> trash;
    std::vector<Decoration> decorations;

    Map();
    Map(float _width, float _depth);
    Map(const Map& other);

    Map& operator=(const Map& other);
    bool operator==(const Map& other) const;
    bool operator!=(const Map& other) const;

    void Init();
    int TrashLeft() const;
    int CollectNearest(const Point& playerPos, float range, Point& collectedPosition);
    int SpawnTrashWave(int count, const Point& playerPosition);
    void UpdateFallingTrash(float deltaTime);
    void ResolveMovement(const Point& start, Point& destination,
                        float playerRadius) const;
    void SortByValue();

private:
    std::mt19937 randomEngine{std::random_device{}()};
    float RandomFloat(float minimum, float maximum);
    bool PositionIsOccupied(float x, float z, float clearance) const;
    bool PositionIsBlocked(const Point& position, float playerRadius) const;
    int AddRandomTrash(int count, bool falling, const Point& playerPosition);
};

std::istream& operator>>(std::istream& in, Map& map);
std::ostream& operator<<(std::ostream& out, const Map& map);