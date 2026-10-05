#include "Renderer.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>

void Renderer::Clear() {
    system("cls"); // sterge ecranul (Windows)
}

void Renderer::PutText(const std::string& text) {
    std::cout << text << "\n";
}

void Renderer::DrawMap(Map& map, Player& player) {
    for (int z = 0; z < map.depth; z++) {
        for (int x = 0; x < map.width; x++) {
            char c = '.';
            for (auto& item : map.trash)
                if (std::lround(item.position.x) == x && std::lround(item.position.z) == z) c = '#';
            if (std::lround(player.position.x) == x && std::lround(player.position.z) == z) c = 'P';
            std::cout << c << ' ';
        }
        std::cout << "\n";
    }
}