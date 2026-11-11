#include "Map.hpp"

#include <algorithm>
#include <cmath>

Map::Map() : width(50.0f), depth(40.0f), trash() {}

Map::Map(float _width, float _depth) : width(_width), depth(_depth), trash() {}

Map::Map(const Map& other)
    : width(other.width), depth(other.depth), trash(other.trash),
      decorations(other.decorations), randomEngine(other.randomEngine) {}

Map& Map::operator=(const Map& other) {
    width = other.width;
    depth = other.depth;
    trash = other.trash;
    decorations = other.decorations;
    randomEngine = other.randomEngine;
    return *this;
}

bool Map::operator==(const Map& other) const {
    return width == other.width && depth == other.depth && trash == other.trash;
}

bool Map::operator!=(const Map& other) const {
    return !(*this == other);
}

std::istream& operator>>(std::istream& in, Map& map) {
    float width, depth;
    int count;
    if (!(in >> width >> depth >> count)) {
        return in;
    }
    if (count < 0) {
        in.setstate(std::ios::failbit);
        return in;
    }

    Map result(width, depth);
    for (int i = 0; i < count; ++i) {
        Item item;
        if (!(in >> item)) {
            return in;
        }
        result.trash.push_back(item);
    }
    result.SortByValue();
    map = result;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Map& map) {
    out << map.width << " " << map.depth << " " << map.trash.size();
    for (const Item& item : map.trash) {
        out << "\n" << item;
    }
    return out;
}

void Map::Init() {
    trash.clear();
    decorations.clear();

    const auto addDecoration = [this](DecorationType type, float scale,
                                      float collisionHalfExtent) {
        for (int attempt = 0; attempt < 120; ++attempt) {
            const float x = RandomFloat(3.0f, width - 3.0f);
            const float z = RandomFloat(3.0f, depth - 3.0f);
            const float clearance = std::max(2.0f, collisionHalfExtent + 1.0f);
            if (std::hypot(x - width * 0.5f, z - depth * 0.5f) < 5.0f ||
                PositionIsOccupied(x, z, clearance)) {
                continue;
            }

            decorations.push_back(Decoration{
                Point(x, 0.0f, z), type, scale, collisionHalfExtent
            });
            return;
        }
    };

    for (float x = 4.0f; x < width - 2.0f; x += 8.0f) {
        decorations.push_back(Decoration{
            Point(x, 0.0f, 2.0f), DecorationType::Tree, 1.0f, 0.85f
        });
        decorations.push_back(Decoration{
            Point(x, 0.0f, depth - 2.0f), DecorationType::Tree, 1.0f, 0.85f
        });
    }
    for (float z = 10.0f; z < depth - 3.0f; z += 9.0f) {
        decorations.push_back(Decoration{
            Point(2.0f, 0.0f, z), DecorationType::Tree, 1.0f, 0.85f
        });
        decorations.push_back(Decoration{
            Point(width - 2.0f, 0.0f, z), DecorationType::Tree, 1.0f, 0.85f
        });
    }

    for (int i = 0; i < 8; ++i) {
        addDecoration(DecorationType::Tree, RandomFloat(0.8f, 1.2f), 0.85f);
    }
    for (int i = 0; i < 18; ++i) {
        addDecoration(DecorationType::Rock, RandomFloat(0.7f, 1.35f), 0.55f);
    }
    for (int i = 0; i < 20; ++i) {
        addDecoration(DecorationType::Bush, RandomFloat(0.7f, 1.2f), 0.55f);
    }
    for (int i = 0; i < 34; ++i) {
        addDecoration(DecorationType::Flower, RandomFloat(0.65f, 1.25f), 0.0f);
    }
    for (int i = 0; i < 5; ++i) {
        addDecoration(DecorationType::Palm, RandomFloat(0.8f, 1.15f), 0.8f);
    }

    AddRandomTrash(40, false, Point(width * 0.5f, 0.0f, depth * 0.5f));
    SortByValue();
}

int Map::TrashLeft() const {
    return static_cast<int>(std::count_if(
        trash.begin(), trash.end(), [](const Item& item) { return item.value > 0; }));
}

int Map::CollectNearest(const Point& playerPos, float range, Point& collectedPosition) {
    const auto nearest = std::min_element(trash.begin(), trash.end(),
        [&playerPos](const Item& left, const Item& right) {
            if (left.falling != right.falling) {
                return !left.falling;
            }
            return left.position.DistanceTo(playerPos) <
                   right.position.DistanceTo(playerPos);
        });
    if (nearest == trash.end() || nearest->falling ||
        nearest->position.DistanceTo(playerPos) > range) {
        return 0;
    }

    const int reward = nearest->value;
    collectedPosition = nearest->position;
    trash.erase(nearest);
    return reward;
}

int Map::SpawnTrashWave(int count, const Point& playerPosition) {
    return AddRandomTrash(count, true, playerPosition);
}

void Map::UpdateFallingTrash(float deltaTime) {
    if (deltaTime <= 0.0f) {
        return;
    }

    constexpr float Gravity = 18.0f;
    for (Item& item : trash) {
        if (!item.falling) {
            continue;
        }
        item.fallSpeed += Gravity * deltaTime;
        item.position.y -= item.fallSpeed * deltaTime;
        if (item.position.y <= 0.0f) {
            item.position.y = 0.0f;
            item.fallSpeed = 0.0f;
            item.falling = false;
        }
    }
}

void Map::ResolveMovement(const Point& start, Point& destination,
                          float playerRadius) const {
    Point xCandidate(destination.x, destination.y, start.z);
    if (PositionIsBlocked(xCandidate, playerRadius)) {
        destination.x = start.x;
    }

    Point zCandidate(destination.x, destination.y, destination.z);
    if (PositionIsBlocked(zCandidate, playerRadius)) {
        destination.z = start.z;
    }
}

float Map::RandomFloat(float minimum, float maximum) {
    std::uniform_real_distribution<float> distribution(minimum, maximum);
    return distribution(randomEngine);
}

bool Map::PositionIsOccupied(float x, float z, float clearance) const {
    for (const Decoration& decoration : decorations) {
        if (decoration.collisionHalfExtent > 0.0f &&
            std::abs(x - decoration.position.x) <
                clearance + decoration.collisionHalfExtent &&
            std::abs(z - decoration.position.z) <
                clearance + decoration.collisionHalfExtent) {
            return true;
        }
    }
    for (const Item& item : trash) {
        if (std::abs(x - item.position.x) < clearance + 0.65f &&
            std::abs(z - item.position.z) < clearance + 0.65f) {
            return true;
        }
    }
    return false;
}

bool Map::PositionIsBlocked(const Point& position, float playerRadius) const {
    for (const Decoration& decoration : decorations) {
        if (decoration.collisionHalfExtent > 0.0f &&
            std::abs(position.x - decoration.position.x) <
                playerRadius + decoration.collisionHalfExtent &&
            std::abs(position.z - decoration.position.z) <
                playerRadius + decoration.collisionHalfExtent) {
            return true;
        }
    }
    for (const Item& item : trash) {
        if (!item.falling &&
            std::abs(position.x - item.position.x) < playerRadius + 0.48f &&
            std::abs(position.z - item.position.z) < playerRadius + 0.48f) {
            return true;
        }
    }
    return false;
}

int Map::AddRandomTrash(int count, bool falling, const Point& playerPosition) {
    static const char* const trashTypes[] = {
        "GlassShard", "WineBottle", "AluminumCan", "SodaCan",
        "Apple", "BananaPeel", "CartonBox", "PaperBag",
        "MilkBottle", "PlasticBottle"
    };

    std::uniform_int_distribution<int> typeDistribution(0, 9);
    std::uniform_int_distribution<int> valueDistribution(5, 14);
    int added = 0;
    for (int itemIndex = 0; itemIndex < count; ++itemIndex) {
        bool placed = false;
        float chosenX = 0.0f;
        float chosenZ = 0.0f;
        for (int attempt = 0; attempt < 320; ++attempt) {
            const float x = RandomFloat(1.5f, width - 1.5f);
            const float z = RandomFloat(1.5f, depth - 1.5f);
            bool occupied = false;
            if (attempt < 220) {
                occupied = PositionIsOccupied(x, z, attempt < 120 ? 1.15f : 0.3f);
            } else {
                for (const Decoration& decoration : decorations) {
                    if (decoration.collisionHalfExtent > 0.0f &&
                        std::abs(x - decoration.position.x) <
                            0.5f + decoration.collisionHalfExtent &&
                        std::abs(z - decoration.position.z) <
                            0.5f + decoration.collisionHalfExtent) {
                        occupied = true;
                        break;
                    }
                }
            }
            if (std::hypot(x - playerPosition.x, z - playerPosition.z) < 3.0f ||
                occupied) {
                continue;
            }
            chosenX = x;
            chosenZ = z;
            placed = true;
            break;
        }

        if (!placed) {
            break;
        }

        const int typeIndex = typeDistribution(randomEngine);
        const float dropHeight = falling ? RandomFloat(12.0f, 20.0f) : 0.0f;
        Item item(trashTypes[typeIndex], Point(chosenX, dropHeight, chosenZ),
                  valueDistribution(randomEngine));
        item.falling = falling;
        trash.push_back(item);
        ++added;
    }
    SortByValue();
    return added;
}

void Map::SortByValue() {
    std::sort(trash.begin(), trash.end(),
        [](const Item& left, const Item& right) {
            return left.value > right.value;
        });
}