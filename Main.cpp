#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "GameEngine.hpp"
#include "SQLiteMapStorage.hpp"

int main() {
    try {
        Point a(1.0f, 2.0f, 3.0f);
        Point b = a;
        Point c;
        c = a;
        std::cout << "Point b: " << b << "\n";
        std::cout << "a == c: " << (a == c) << "\n";
        std::cout << "a != Point(): " << (a != Point()) << "\n";

        Item bottle("Bottle", Point(2.0f, 0.0f, 5.0f), 10);
        Item copy = bottle;
        std::cout << "Item: " << bottle << "\n";
        std::cout << "bottle == copy: " << (bottle == copy) << "\n";

        Player player(Point(0.0f, 0.0f, 0.0f), 5, 1.0f, 1.5f);
        std::cout << "Player: " << player << "\n";

        std::istringstream input("12 20 2 Bottle 1 0 1 10 Can 3 0 4 5");
        Map map;
        input >> map;
        std::cout << "Map:\n" << map << "\n";

        const std::string databasePath = "island_cleaner.db";
        SQLiteMapStorage::Save(map, databasePath);
        const Map restoredMap = SQLiteMapStorage::Load(databasePath);
        std::cout << "Map restored from SQLite: "
                  << (restoredMap == map ? "yes" : "no") << "\n";

        std::vector<std::string> names;
        std::transform(map.trash.begin(), map.trash.end(), std::back_inserter(names),
            [](const Item& item) { return item.name; });
        std::sort(names.begin(), names.end());
        std::cout << "Item names sorted:\n";
        std::copy(names.begin(), names.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

        const auto it = std::find_if(names.begin(), names.end(),
            [](const std::string& name) { return name == "Bottle"; });
        std::cout << "Bottle found: " << (it != names.end()) << "\n";

        GameEngine game;
        game.Init();
        game.Run();
        return restoredMap == map ? 0 : 1;
    } catch (const std::exception& error) {
        std::cerr << "Application error: " << error.what() << "\n";
        return 1;
    }
}