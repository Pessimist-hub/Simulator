#pragma once
#include <string>
#include "Map.hpp"
#include "Player.hpp"

struct AbstractRenderer {
    virtual void Clear() = 0;
    virtual void PutText(const std::string& text) = 0;
    virtual void DrawMap(Map& map, Player& player) = 0;
    virtual ~AbstractRenderer() = default;
};