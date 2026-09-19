#pragma once
#include <string>
#include "Map.hpp"
#include "Player.hpp"


struct Renderer {
    void Clear();
    void PutText(const std::string & text);
    void DrawMap(Map& map, Player & player); 
};