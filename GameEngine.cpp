#include "GameEngine.hpp"
#include <iostream>

void GameEngine::Init() {
    map.Init();
    player = Player(Point(0.0f, 0.0f, 0.0f), 0, 1.0f, 1.5f);
    listener = std::make_unique<EventListener>();
    renderer = std::make_unique<Renderer>();
    audio = std::make_unique<AudioController>();

    if (renderer) {
        renderer->Clear();
    }

    std::cout << "Game engine initialized..." << std::endl;
}

void GameEngine::Run() {
    if (renderer) {
        renderer->DrawMap(map, player);
    }

    if (listener) {
        const char event = listener->GetEvent();
        std::cout << "Last input event: " << event << std::endl;
    }

    std::cout << "Trash remaining: " << map.TrashLeft() << std::endl;

    if (audio) {
        audio->PlayPickup();
    }

    std::cout << "Game engine is running..." << std::endl;
}