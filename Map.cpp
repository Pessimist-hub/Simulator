#include "Map.hpp"

Map::Map() : width(50.0f), depth(40.0f), trash() {}

Map::Map(float _width, float _depth) : width(_width), depth(_depth), trash() {}

Map::Map(const Map& other)
    : width(other.width), depth(other.depth), trash(other.trash) {}

Map& Map::operator=(const Map& other) {
    width = other.width;
    depth = other.depth;
    trash = other.trash;
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
    static const char* const trashTypes[] = {
        "GlassShard", "WineBottle", "AluminumCan", "SodaCan",
        "Apple", "BananaPeel", "CartonBox", "PaperBag",
        "MilkBottle", "PlasticBottle"
    };

    trash.clear();
    for (int row = 0; row < 5; ++row) {
        for (int column = 0; column < 8; ++column) {
            const int index = row * 8 + column;
            const float x = width * (static_cast<float>(column) + 0.5f) / 8.0f;
            const float z = depth * (static_cast<float>(row) + 0.5f) / 5.0f;
            const int value = 5 + (index % 6);
            trash.emplace_back(trashTypes[index % 10], Point(x, 0.0f, z), value);
        }
    }
    SortByValue();
}

int Map::TrashLeft() const {
    return static_cast<int>(std::count_if(
        trash.begin(), trash.end(), [](const Item& item) { return item.value > 0; }));
}

int Map::Collect(const Point& playerPos, float range) {
    const auto end = std::remove_if(trash.begin(), trash.end(),
        [&playerPos, range](const Item& item) {
            return item.position.DistanceTo(playerPos) <= range;
        });

    const int removed = static_cast<int>(std::distance(end, trash.end()));
    trash.erase(end, trash.end());
    return removed;
}

void Map::SortByValue() {
    std::sort(trash.begin(), trash.end(),
        [](const Item& left, const Item& right) {
            return left.value > right.value;
        });
}