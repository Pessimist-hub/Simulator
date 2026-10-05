#include "Map.hpp"

void Map::Init() {
    trash.push_back({"Sticla",  {2, 0, 3}, 5});
    trash.push_back({"Punga",   {5, 0, 1}, 5});
    trash.push_back({"Doza",    {7, 0, 7}, 5});
    trash.push_back({"Anvelopa",{1, 0, 8}, 5});
    trash.push_back({"Cutie",   {8, 0, 4}, 5});
}

int Map::TrashLeft() {
    return (int)trash.size();
}

int Map::Collect(Point playerPos, float range) {
    int coins = 0;
    for (int i = (int)trash.size() - 1; i >= 0; i--) {
        if (trash[i].position.DistanceTo(playerPos) <= range) {
            coins += trash[i].value;
            trash.erase(trash.begin() + i);
        }
    }
    return coins;
}