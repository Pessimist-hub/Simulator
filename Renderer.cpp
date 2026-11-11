#include "Renderer.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <stdexcept>
#include <raylib.h>
#include <raymath.h>
#include <string>

namespace {

constexpr std::array<const char*, 10> TrashModelFiles{{
    "Assets/Trash/glass_shard.glb",
    "Assets/Trash/glass_vine_bottle.glb",
    "Assets/Trash/metal_aluminium_can.glb",
    "Assets/Trash/metal_soda_can.glb",
    "Assets/Trash/organic_apple.glb",
    "Assets/Trash/organic_banana_peel.glb",
    "Assets/Trash/paper_carton_box.glb",
    "Assets/Trash/paper_bag.glb",
    "Assets/Trash/plastic_milk_bottle.glb",
    "Assets/Trash/plastic_bottle.glb"
}};

constexpr std::array<const char*, 10> TrashModelNames{{
    "GlassShard", "WineBottle", "AluminumCan", "SodaCan", "Apple",
    "BananaPeel", "CartonBox", "PaperBag", "MilkBottle", "PlasticBottle"
}};

Vector3 ToVector3(const Point& point, float height = 0.0f) {
    return Vector3{point.x, point.y + height, point.z};
}

int FindTrashModel(const std::string& name) {
    for (std::size_t index = 0; index < TrashModelNames.size(); ++index) {
        if (name == TrashModelNames[index]) {
            return static_cast<int>(index);
        }
    }
    return -1;
}

void DrawTree(float x, float z) {
    DrawCylinder(Vector3{x, 0.65f, z}, 0.16f, 0.12f, 1.3f, 8, BROWN);
    DrawSphere(Vector3{x, 1.65f, z}, 0.72f, DARKGREEN);
    DrawSphere(Vector3{x - 0.28f, 1.42f, z + 0.18f}, 0.45f, GREEN);
}

Vector3 PlayerPoint(const Vector3& center, float angle, float x, float y, float z,
                    float bob) {
    const float radians = angle * DEG2RAD;
    const float sine = std::sin(radians);
    const float cosine = std::cos(radians);
    return Vector3{center.x + x * cosine + z * sine,
                   y + bob,
                   center.z - x * sine + z * cosine};
}

void DrawLimb(const Vector3& start, const Vector3& end, float radius,
              Color color) {
    DrawCylinderEx(start, end, radius, radius * 0.82f, 8, color);
    DrawSphere(start, radius, color);
    DrawSphere(end, radius * 0.82f, color);
}

void DrawPlayer(const Player& player, const Vector3& position) {
    const float stride = player.isMoving
        ? std::sin(player.animationTime * 10.0f) * 0.23f
        : 0.0f;
    const float armSwing = player.isMoving
        ? std::sin(player.animationTime * 10.0f) * 0.2f
        : 0.0f;
    const float bob = player.isMoving
        ? std::abs(std::sin(player.animationTime * 10.0f)) * 0.025f
        : 0.0f;
    const auto point = [&player, &position, bob](float x, float y, float z) {
        return PlayerPoint(position, player.facingAngle, x, y, z, bob);
    };

    DrawCylinderEx(point(0.0f, 0.78f, 0.0f), point(0.0f, 1.48f, 0.0f),
                   0.24f, 0.3f, 12, Color{35, 155, 106, 255});
    DrawCylinderEx(point(0.0f, 1.18f, 0.0f), point(0.0f, 1.38f, 0.0f),
                   0.305f, 0.305f, 12, YELLOW);
    DrawSphere(point(0.0f, 1.79f, 0.0f), 0.255f, Color{235, 190, 145, 255});
    DrawSphere(point(0.0f, 1.79f, 0.235f), 0.055f, Color{235, 190, 145, 255});

    for (int side : {-1, 1}) {
        const float sideOffset = static_cast<float>(side);
        const float legSwing = sideOffset * stride;
        const float armReach = -sideOffset * armSwing;

        const Vector3 hip = point(sideOffset * 0.135f, 0.79f, 0.0f);
        const Vector3 knee = point(sideOffset * 0.15f, 0.42f, legSwing * 0.45f);
        const Vector3 ankle = point(sideOffset * 0.16f, 0.12f, legSwing);
        const Vector3 toe = point(sideOffset * 0.16f, 0.09f, legSwing + 0.14f);
        DrawLimb(hip, knee, 0.105f, DARKBLUE);
        DrawLimb(knee, ankle, 0.085f, DARKBLUE);
        DrawLimb(ankle, toe, 0.08f, BLACK);

        const Vector3 shoulder = point(sideOffset * 0.29f, 1.38f, 0.0f);
        const Vector3 elbow = point(sideOffset * 0.39f, 1.02f, armReach * 0.5f);
        const Vector3 hand = point(sideOffset * 0.4f, 0.7f, armReach);
        DrawLimb(shoulder, elbow, 0.085f, Color{35, 155, 106, 255});
        DrawLimb(elbow, hand, 0.07f, Color{235, 190, 145, 255});
    }
}

} // namespace

Renderer::~Renderer() {
    Close();
}

void Renderer::Initialize() {
    if (initialized) {
        return;
    }

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 800, "Island Cleaner - 3D");
    if (!IsWindowReady()) {
        throw std::runtime_error("Could not initialize the 3D window");
    }
    initialized = true;

    for (std::size_t index = 0; index < TrashModelFiles.size(); ++index) {
        trashModels[index] = LoadModel(TrashModelFiles[index]);
        if (trashModels[index].meshCount == 0) {
            Close();
            throw std::runtime_error(
                std::string("Could not load trash model: ") + TrashModelFiles[index]);
        }
        loadedTrashModels[index] = true;
    }
    SetExitKey(KEY_NULL);
}

bool Renderer::ShouldClose() const {
    return !initialized || WindowShouldClose();
}

void Renderer::Close() {
    for (std::size_t index = 0; index < trashModels.size(); ++index) {
        if (loadedTrashModels[index]) {
            UnloadModel(trashModels[index]);
            loadedTrashModels[index] = false;
        }
    }
    if (initialized) {
        CloseWindow();
        initialized = false;
    }
}

void Renderer::Clear() {
    BeginDrawing();
    ClearBackground(Color{125, 196, 230, 255});
}

void Renderer::PutText(const std::string& text) {
    DrawText(text.c_str(), 24, 22, 24, WHITE);
}

void Renderer::SpawnCollectionEffect(const Point& position, int reward) {
    constexpr float ParticleLifetime = 0.75f;
    for (std::size_t index = 0; index < collectionParticles.size(); ++index) {
        const float angle = 2.0f * PI * static_cast<float>(index) /
                            static_cast<float>(collectionParticles.size());
        const float speed = 0.8f + 0.12f * static_cast<float>(index % 5);
        collectionParticles[index] = CollectionParticle{
            ToVector3(position, 0.35f),
            Vector3{std::cos(angle) * speed,
                    1.2f + 0.15f * static_cast<float>(index % 4),
                    std::sin(angle) * speed},
            ParticleLifetime,
            index % 2 == 0 ? LIME : GOLD
        };
    }

    rewardPopupPosition = position;
    rewardPopupValue = reward;
    rewardPopupTimer = ParticleLifetime;
}

void Renderer::DrawMap(const Map& map, const Player& player,
                       const UIManager& ui, const UpgradeManager& upgrades) {
    const float centerX = map.width * 0.5f;
    const float centerZ = map.depth * 0.5f;
    const Vector3 playerPosition = ToVector3(player.position);
    const float cameraDistance = std::max(map.width, map.depth) * 0.4f;
    const Camera3D camera{
        Vector3{player.position.x + cameraDistance * 0.55f,
                cameraDistance * 0.8f,
                player.position.z + cameraDistance * 0.7f},
        Vector3{playerPosition.x, 0.6f, playerPosition.z},
        Vector3{0.0f, 1.0f, 0.0f},
        45.0f,
        CAMERA_PERSPECTIVE
    };

    Clear();
    BeginMode3D(camera);
    DrawPlane(Vector3{centerX, -0.22f, centerZ},
              Vector2{map.width + 90.0f, map.depth + 90.0f}, BLUE);
    DrawPlane(Vector3{centerX, -0.02f, centerZ},
              Vector2{map.width + 2.0f, map.depth + 2.0f}, BEIGE);
    DrawPlane(Vector3{centerX, 0.0f, centerZ},
              Vector2{map.width, map.depth}, Color{89, 160, 76, 255});
    DrawCubeWires(Vector3{centerX, 0.1f, centerZ},
                  map.width, 0.2f, map.depth, DARKGREEN);

    for (float x = 3.0f; x < map.width; x += 7.0f) {
        DrawTree(x, 2.0f);
        DrawTree(x, map.depth - 2.0f);
    }
    for (float z = 9.0f; z < map.depth - 2.0f; z += 8.0f) {
        DrawTree(2.0f, z);
        DrawTree(map.width - 2.0f, z);
    }

    Point nearestCollectiblePosition;
    bool hasNearbyCollectible = false;
    float nearestDistance = player.pickupRange;
    for (const Item& item : map.trash) {
        const int modelIndex = FindTrashModel(item.name);
        const float distance = item.position.DistanceTo(player.position);
        if (distance <= nearestDistance) {
            nearestDistance = distance;
            nearestCollectiblePosition = item.position;
            hasNearbyCollectible = true;
        }

        if (modelIndex >= 0) {
            Color tint = WHITE;
            if (item.name == "GlassShard" || item.name == "WineBottle") {
                tint = SKYBLUE;
            } else if (item.name == "AluminumCan" || item.name == "SodaCan") {
                tint = LIGHTGRAY;
            } else if (item.name == "Apple") {
                tint = RED;
            } else if (item.name == "BananaPeel") {
                tint = GOLD;
            } else if (item.name == "CartonBox" || item.name == "PaperBag") {
                tint = BEIGE;
            } else if (item.name == "MilkBottle") {
                tint = LIME;
            } else if (item.name == "PlasticBottle") {
                tint = ORANGE;
            }

            DrawModel(trashModels[static_cast<std::size_t>(modelIndex)],
                      ToVector3(item.position, 0.45f), 1.0f, tint);
        }
    }

    if (hasNearbyCollectible) {
        DrawCircle3D(ToVector3(nearestCollectiblePosition, 0.04f),
                     0.55f, Vector3{1.0f, 0.0f, 0.0f}, 90.0f, GOLD);
    }

    const float effectDelta = std::min(GetFrameTime(), 0.1f);
    for (CollectionParticle& particle : collectionParticles) {
        if (particle.lifetime <= 0.0f) {
            continue;
        }
        particle.lifetime -= effectDelta;
        particle.position.x += particle.velocity.x * effectDelta;
        particle.position.y += particle.velocity.y * effectDelta;
        particle.position.z += particle.velocity.z * effectDelta;
        particle.velocity.y -= 2.8f * effectDelta;
        const float alpha = std::clamp(particle.lifetime / 0.75f, 0.0f, 1.0f);
        Color color = particle.color;
        color.a = static_cast<unsigned char>(255.0f * alpha);
        DrawSphere(particle.position, 0.075f * alpha, color);
    }

    DrawPlayer(player, playerPosition);
    EndMode3D();

    PutText("ISLAND CLEANER");
    DrawText(TextFormat("Gunoi ramas: %i", map.TrashLeft()),
             24, 58, 20, WHITE);
    DrawText(TextFormat("Monede: %i", player.coins),
             24, 84, 20, YELLOW);
    const float staminaRatio = player.maxStamina > 0.0f
        ? std::clamp(player.stamina / player.maxStamina, 0.0f, 1.0f)
        : 0.0f;
    DrawText("Stamina", 24, 115, 16, WHITE);
    DrawRectangle(94, 115, 220, 18, Color{35, 55, 66, 230});
    DrawRectangle(96, 117, static_cast<int>(216.0f * staminaRatio), 14,
                  staminaRatio > 0.25f ? LIME : ORANGE);
    DrawText(TextFormat("%i / %i", static_cast<int>(player.stamina),
                        static_cast<int>(player.maxStamina)),
             322, 115, 16, WHITE);
    if (ui.IsOvertime()) {
        DrawText("PRELUNGIRI - curata insula fara limita de timp",
                 24, 143, 18, ORANGE);
    } else {
        const int seconds = static_cast<int>(ui.ChallengeTimeRemaining());
        DrawText(TextFormat("Timp ramas: %02i:%02i", seconds / 60, seconds % 60),
                 24, 143, 18, seconds <= 20 ? ORANGE : WHITE);
    }

    DrawText("W A S D - miscare | Shift - sprint | Click - colecteaza | Esc - meniu",
             24, GetScreenHeight() - 34, 18, WHITE);
    DrawText("Apropie-te de un obiect; cercul auriu indica ce poti colecta.",
             24, GetScreenHeight() - 60, 16, WHITE);

    if (rewardPopupTimer > 0.0f) {
        rewardPopupTimer = std::max(0.0f, rewardPopupTimer - GetFrameTime());
        const float rise = (0.75f - rewardPopupTimer) * 1.25f;
        const Vector2 screenPosition = GetWorldToScreen(
            ToVector3(rewardPopupPosition, 1.8f + rise), camera);
        DrawText(TextFormat("+%i monede", rewardPopupValue),
                 static_cast<int>(screenPosition.x - 45.0f),
                 static_cast<int>(screenPosition.y), 20, GOLD);
    }

    if (map.TrashLeft() == 0) {
        DrawText("Insula este curata! Ai castigat!",
                 GetScreenWidth() / 2 - 180, 34, 24, YELLOW);
    }

    ui.DrawOverlay(player, upgrades);
    EndDrawing();
}
