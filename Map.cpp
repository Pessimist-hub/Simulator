#include "Map.hpp"

Map::Map() : width(10.0f), depth(10.0f), trash() {}

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
    trash.clear();
    trash.emplace_back("Bottle", Point(2.0f, 0.0f, 5.0f), 10);
    trash.emplace_back("Can", Point(5.0f, 0.0f, 2.0f), 8);
    trash.emplace_back("Plastic", Point(8.0f, 0.0f, 7.0f), 12);
    trash.emplace_back("Paper", Point(1.0f, 0.0f, 9.0f), 6);
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