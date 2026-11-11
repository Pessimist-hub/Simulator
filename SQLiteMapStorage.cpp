#include "SQLiteMapStorage.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <sqlite3.h>

namespace {

struct DatabaseCloser {
    void operator()(sqlite3* database) const noexcept {
        if (database != nullptr) {
            sqlite3_close(database);
        }
    }
};

struct StatementFinalizer {
    void operator()(sqlite3_stmt* statement) const noexcept {
        if (statement != nullptr) {
            sqlite3_finalize(statement);
        }
    }
};

using Database = std::unique_ptr<sqlite3, DatabaseCloser>;
using Statement = std::unique_ptr<sqlite3_stmt, StatementFinalizer>;

[[noreturn]] void ThrowDatabaseError(sqlite3* database, const std::string& action) {
    throw std::runtime_error(action + ": " + sqlite3_errmsg(database));
}

Database OpenDatabase(const std::string& path) {
    sqlite3* rawDatabase = nullptr;
    const int result = sqlite3_open(path.c_str(), &rawDatabase);
    Database database(rawDatabase);
    if (result != SQLITE_OK) {
        if (database == nullptr) {
            throw std::runtime_error("Could not open SQLite database");
        }
        ThrowDatabaseError(database.get(), "Could not open SQLite database");
    }
    return database;
}

void Execute(sqlite3* database, const char* sql) {
    char* errorMessage = nullptr;
    const int result = sqlite3_exec(database, sql, nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        const std::string message = errorMessage != nullptr
            ? errorMessage
            : sqlite3_errmsg(database);
        sqlite3_free(errorMessage);
        throw std::runtime_error("SQLite command failed: " + message);
    }
}

Statement Prepare(sqlite3* database, const char* sql) {
    sqlite3_stmt* rawStatement = nullptr;
    if (sqlite3_prepare_v2(database, sql, -1, &rawStatement, nullptr) != SQLITE_OK) {
        ThrowDatabaseError(database, "Could not prepare SQLite statement");
    }
    return Statement(rawStatement);
}

void CheckBind(sqlite3* database, int result) {
    if (result != SQLITE_OK) {
        ThrowDatabaseError(database, "Could not bind SQLite parameter");
    }
}

void CheckStep(sqlite3* database, int result, int expected, const char* action) {
    if (result == expected) {
        return;
    }
    if (result != SQLITE_DONE && result != SQLITE_ROW) {
        ThrowDatabaseError(database, action);
    } else {
        throw std::runtime_error(action);
    }
}

class Transaction {
public:
    explicit Transaction(sqlite3* database) : database_(database), active_(true) {
        Execute(database_, "BEGIN TRANSACTION");
    }

    ~Transaction() {
        if (active_) {
            sqlite3_exec(database_, "ROLLBACK", nullptr, nullptr, nullptr);
        }
    }

    void Commit() {
        Execute(database_, "COMMIT");
        active_ = false;
    }

private:
    sqlite3* database_;
    bool active_;
};

void CreateSchema(sqlite3* database) {
    Execute(database,
        "CREATE TABLE IF NOT EXISTS map_metadata ("
        "id INTEGER PRIMARY KEY CHECK (id = 1), "
        "width REAL NOT NULL, "
        "depth REAL NOT NULL)");
    Execute(database,
        "CREATE TABLE IF NOT EXISTS trash_items ("
        "id INTEGER PRIMARY KEY, "
        "name TEXT NOT NULL, "
        "x REAL NOT NULL, "
        "y REAL NOT NULL, "
        "z REAL NOT NULL, "
        "value INTEGER NOT NULL)");
}

} // namespace

void SQLiteMapStorage::Save(const Map& map, const std::string& databasePath) {
    Database database = OpenDatabase(databasePath);
    CreateSchema(database.get());
    Transaction transaction(database.get());

    Statement metadata = Prepare(database.get(),
        "INSERT OR REPLACE INTO map_metadata (id, width, depth) VALUES (1, ?, ?)");
    CheckBind(database.get(), sqlite3_bind_double(metadata.get(), 1, map.width));
    CheckBind(database.get(), sqlite3_bind_double(metadata.get(), 2, map.depth));
    CheckStep(database.get(), sqlite3_step(metadata.get()), SQLITE_DONE,
              "Could not save map dimensions");

    Execute(database.get(), "DELETE FROM trash_items");
    Statement itemInsert = Prepare(database.get(),
        "INSERT INTO trash_items (name, x, y, z, value) VALUES (?, ?, ?, ?, ?)");
    for (const Item& item : map.trash) {
        CheckBind(database.get(), sqlite3_bind_text(
            itemInsert.get(), 1, item.name.c_str(), -1, SQLITE_TRANSIENT));
        CheckBind(database.get(), sqlite3_bind_double(
            itemInsert.get(), 2, item.position.x));
        CheckBind(database.get(), sqlite3_bind_double(
            itemInsert.get(), 3, item.position.y));
        CheckBind(database.get(), sqlite3_bind_double(
            itemInsert.get(), 4, item.position.z));
        CheckBind(database.get(), sqlite3_bind_int(itemInsert.get(), 5, item.value));
        CheckStep(database.get(), sqlite3_step(itemInsert.get()), SQLITE_DONE,
                  "Could not save map item");
        if (sqlite3_reset(itemInsert.get()) != SQLITE_OK ||
            sqlite3_clear_bindings(itemInsert.get()) != SQLITE_OK) {
            ThrowDatabaseError(database.get(), "Could not reset SQLite statement");
        }
    }

    transaction.Commit();
}

Map SQLiteMapStorage::Load(const std::string& databasePath) {
    Database database = OpenDatabase(databasePath);
    CreateSchema(database.get());

    Statement metadata = Prepare(database.get(),
        "SELECT width, depth FROM map_metadata WHERE id = 1");
    const int metadataResult = sqlite3_step(metadata.get());
    if (metadataResult == SQLITE_DONE) {
        throw std::runtime_error("SQLite database does not contain a saved map");
    }
    CheckStep(database.get(), metadataResult, SQLITE_ROW,
              "Could not read map dimensions");

    Map map(
        static_cast<float>(sqlite3_column_double(metadata.get(), 0)),
        static_cast<float>(sqlite3_column_double(metadata.get(), 1)));

    Statement items = Prepare(database.get(),
        "SELECT name, x, y, z, value FROM trash_items ORDER BY id");
    int itemResult = SQLITE_ROW;
    while ((itemResult = sqlite3_step(items.get())) == SQLITE_ROW) {
        const auto* name = sqlite3_column_text(items.get(), 0);
        if (name == nullptr) {
            throw std::runtime_error("SQLite map item has no name");
        }
        map.trash.emplace_back(
            reinterpret_cast<const char*>(name),
            Point(
                static_cast<float>(sqlite3_column_double(items.get(), 1)),
                static_cast<float>(sqlite3_column_double(items.get(), 2)),
                static_cast<float>(sqlite3_column_double(items.get(), 3))),
            sqlite3_column_int(items.get(), 4));
    }
    if (itemResult != SQLITE_DONE) {
        ThrowDatabaseError(database.get(), "Could not read map items");
    }
    return map;
}
