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
    int WaveNumber() const;
    int LastWaveTrashCount() const;
    bool IsWaveAnnouncementVisible() const;

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
    static constexpr int FirstWaveTrashCount = 12;
    static constexpr int AdditionalTrashPerWave = 6;

    Screen screen = Screen::MainMenu;
    float challengeTimeRemaining = ChallengeDuration;
    float waveAnnouncementTimer = 0.0f;
    int waveNumber = 0;
    int lastWaveTrashCount = 0;
    bool wonInTime = false;

    void StartNewGame(Map& map, Player& player, UpgradeManager& upgrades);
};
