#pragma once
#include "AbstractRenderer.hpp"

struct Renderer : public AbstractRenderer {
    void Clear() override;
    void PutText(const std::string& text) override;
    void DrawMap(Map& map, Player& player) override;
};