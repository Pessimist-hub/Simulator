#pragma once
#include "Map.hpp"
#include "Player.hpp"
#include "EventListener.hpp"
#include "Renderer.hpp"
#include "AudioController.hpp"

struct GameEngine {
    Map map;
    Player player;
    EventListener listener;
    Renderer renderer;
    AudioController audio;

    void Init();
    void Run();
};