#pragma once
#include <array>
#include <raylib.h>
#include "AbstractRenderer.hpp"

struct Renderer : public AbstractRenderer {
    ~Renderer() override;

    void Initialize() override;
    bool ShouldClose() const override;
    void Close() override;
    void Clear() override;
    void PutText(const std::string& text) override;
    void DrawMap(const Map& map, const Player& player,
                 const UIManager& ui, const UpgradeManager& upgrades) override;

private:
    bool initialized = false;
    std::array<Model, 10> trashModels{};
    std::array<bool, 10> loadedTrashModels{};
};