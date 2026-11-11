#pragma once

#include "Map.hpp"
#include "Player.hpp"
#include "UpgradeManager.hpp"

class UIManager {
public:
    void Update(Map& map, Player& player, UpgradeManager& upgrades, float deltaTime);
    void DrawOverlay(const Player& player, const UpgradeManager& upgrades) const;

    bool ShouldExit() const;
    bool ShouldSimulate() const;
    bool ShouldCollectTrash() const;
    float ChallengeTimeRemaining() const;
    bool IsOvertime() const;

private:
    enum class Screen {
        MainMenu,
        MainMenuUpgrades,
        Playing,
        PlayingUpgrades,
        PauseMenu,
        Victory,
        Exit
    };

    static constexpr float ChallengeDuration = 120.0f;
    static constexpr int OnTimeBonus = 100;

    Screen screen = Screen::MainMenu;
    float challengeTimeRemaining = ChallengeDuration;
    bool overtime = false;
    bool wonInTime = false;

    void StartNewGame(Map& map, Player& player, UpgradeManager& upgrades);
};
