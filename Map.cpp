#include "Map.hpp"

Map::Map() : width(10), depth(10), trash() {}

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

std::istream& operator>>(std::istream& in, Map& map) {
    float width, depth;
    int count;
    in >> width >> depth >> count;
    Map result(width, depth);
    for (int i = 0; i < count; i++) {
        Item item;
        in >> item;
        result.trash.push_back(item);
    }
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

void Map::Init() {}
int Map::TrashLeft() { return 0; }
int Map::Collect(Point playerPos, float range) { return 0; }