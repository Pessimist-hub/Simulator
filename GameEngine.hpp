#pragma once
#include <memory>
#include "Map.hpp"
#include "Player.hpp"
#include "EventListener.hpp"
#include "Renderer.hpp"
#include "AudioController.hpp"

struct GameEngine {
    Map map;
    Player player;
    std::unique_ptr<EventListener> listener;
    std::unique_ptr<AbstractRenderer> renderer;
    std::unique_ptr<AudioController> audio;

    void Init();
    void Run();
};