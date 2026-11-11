#pragma once

#include "Map.hpp"
#include "Player.hpp"
#include "UpgradeManager.hpp"

class UIManager {
public:
    void Update(Map& map, Player& player, UpgradeManager& upgrades);
    void DrawOverlay(const Player& player, const UpgradeManager& upgrades) const;

    bool ShouldExit() const;
    bool ShouldSimulate() const;

private:
    enum class Screen {
        MainMenu,
        MainMenuUpgrades,
        Playing,
        PlayingUpgrades,
        Victory,
        Exit
    };

    Screen screen = Screen::MainMenu;

    void StartNewGame(Map& map, Player& player, UpgradeManager& upgrades);
};
