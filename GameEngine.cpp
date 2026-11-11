#include "GameEngine.hpp"
#include <raylib.h>

void GameEngine::Init() {
    map.Init();
    player = Player(Point(map.width * 0.5f, 0.0f, map.depth * 0.5f), 0, 2.2f, 1.5f);
    listener = std::make_unique<EventListener>();
    renderer = std::make_unique<Renderer>();
    audio = std::make_unique<AudioController>();
    renderer->Initialize();
}

void GameEngine::Run() {
    while (renderer && !renderer->ShouldClose() && !ui.ShouldExit()) {
        const float deltaTime = GetFrameTime();
        ui.Update(map, player, upgrades, deltaTime);

        float dx = 0.0f;
        float dz = 0.0f;
        if (ui.ShouldSimulate()) {
            map.UpdateFallingTrash(deltaTime);
            listener->GetMovement(dx, dz);
            const bool sprinting = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
            const Point previousPosition = player.position;
            player.Move(dx, dz, map.width, map.depth, deltaTime, sprinting);
            map.ResolveMovement(previousPosition, player.position, 0.4f);

            if (ui.ShouldCollectTrash() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Point collectedPosition;
                const int reward = map.CollectNearest(
                    player.position, player.pickupRange, collectedPosition);
                if (reward > 0) {
                    player.coins += reward * player.coinMultiplier;
                    renderer->SpawnCollectionEffect(collectedPosition, reward);
                    audio->PlayPickup();
                }
            }
        }

        renderer->DrawMap(map, player, ui, upgrades);
    }

    if (renderer) {
        renderer->Close();
    }
}