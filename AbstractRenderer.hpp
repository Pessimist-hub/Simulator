#pragma once
#include <string>
#include "Map.hpp"
#include "Player.hpp"
#include "UIManager.hpp"
#include "UpgradeManager.hpp"

struct AbstractRenderer {
    virtual void Initialize() = 0;
    virtual bool ShouldClose() const = 0;
    virtual void Close() = 0;
    virtual void Clear() = 0;
    virtual void PutText(const std::string& text) = 0;
    virtual void DrawMap(const Map& map, const Player& player,
                         const UIManager& ui, const UpgradeManager& upgrades) = 0;
    virtual ~AbstractRenderer() = default;
};