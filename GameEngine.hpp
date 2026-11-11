#pragma once
#include <memory>
#include "Map.hpp"
#include "Player.hpp"
#include "EventListener.hpp"
#include "Renderer.hpp"
#include "AudioController.hpp"
#include "UIManager.hpp"
#include "UpgradeManager.hpp"

struct GameEngine {
    Map map;
    Player player;
    std::unique_ptr<EventListener> listener;
    std::unique_ptr<AbstractRenderer> renderer;
    std::unique_ptr<AudioController> audio;
    UIManager ui;
    UpgradeManager upgrades;

    void Init();
    void Run();
};