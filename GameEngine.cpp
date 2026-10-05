#include "GameEngine.hpp"
#include <cmath>

void GameEngine::Init() {
    map.Init();
}

void GameEngine::Run() {
    while (true) {
        renderer.Clear();
        renderer.DrawMap(map, player);
        renderer.PutText("Pozitie: (" + std::to_string(std::lround(player.position.x)) + ", " +
                         std::to_string(std::lround(player.position.y)) + ", " +
                         std::to_string(std::lround(player.position.z)) + ")");
        renderer.PutText("Coins: " + std::to_string(player.coins) +
                         " | Gunoi ramas: " + std::to_string(map.TrashLeft()));

        if (map.TrashLeft() == 0) {
            renderer.PutText("Insula e curata! A aparut barca. Ai castigat!");
            break;
        }

        renderer.PutText("W A S D = miscare, E = ia gunoi, 1 = viteza, 2 = raza, Q = iesire");
        char key = listener.GetEvent();

        if (key == 'Q') break;
        if (key == 'W') player.Move(0, -1, map.width, map.depth);
        if (key == 'S') player.Move(0, 1, map.width, map.depth);
        if (key == 'A') player.Move(-1, 0, map.width, map.depth);
        if (key == 'D') player.Move(1, 0, map.width, map.depth);
        if (key == '1') player.BuySpeed();
        if (key == '2') player.BuyRange();
        if (key == 'E') {
            int coins = map.Collect(player.position, player.pickupRange);
            if (coins > 0) { player.coins += coins; audio.PlayPickup(); }
        }
    }
}