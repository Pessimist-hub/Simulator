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
    void SpawnCollectionEffect(const Point& position, int reward) override;

private:
    struct CollectionParticle {
        Vector3 position{};
        Vector3 velocity{};
        float lifetime = 0.0f;
        Color color{};
    };

    bool initialized = false;
    std::array<Model, 10> trashModels{};
    std::array<bool, 10> loadedTrashModels{};
    std::array<CollectionParticle, 20> collectionParticles{};
    float rewardPopupTimer = 0.0f;
    int rewardPopupValue = 0;
    Point rewardPopupPosition;
};