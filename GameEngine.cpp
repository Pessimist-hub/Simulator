#include "GameEngine.hpp"
#include <iostream>

void GameEngine::Init() {
    map.Init();
    std::cout << "Game engine initialized..." << std::endl;
}

void GameEngine::Run() {
    std::cout << "Game engine is running..." << std::endl;
}