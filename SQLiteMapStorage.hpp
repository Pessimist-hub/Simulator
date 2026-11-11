#pragma once

#include <string>
#include "Map.hpp"

class SQLiteMapStorage {
public:
    static void Save(const Map& map, const std::string& databasePath);
    static Map Load(const std::string& databasePath);
};
