#include <iostream>
#include <stdexcept>
#include "GameEngine.hpp"

int main() {
    try {
        GameEngine game;
        game.Init();
        game.Run();
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Application error: " << error.what() << "\n";
        return 1;
    }
}