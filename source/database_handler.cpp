#include "database_handler.h"

// Constructor
DatabaseHandler::DatabaseHandler(const std::string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db)) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
}

// Destructor
DatabaseHandler::~DatabaseHandler() {
    sqlite3_close(db);
}

// Fetch records from the database
std::vector<std::pair<int, std::string>> DatabaseHandler::fetchRecords() {
    std::vector<std::pair<int, std::string>> records;
    sqlite3_stmt* stmt;
    
    const char* sql = "SELECT key, value FROM Cache";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int key = sqlite3_column_int(stmt, 0);
            const unsigned char* value = sqlite3_column_text(stmt, 1);
            records.emplace_back(key, reinterpret_cast<const char*>(value));
        }
    } else {
        std::cerr << "Failed to fetch records: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
    return records;
}

// Insert a record into the database
int DatabaseHandler::insertRecord(int key, const std::string& value) {
    std::string sql = "INSERT INTO Cache (key, value) VALUES (" + std::to_string(key) + ", '" + value + "');";
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "Error inserting record: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return 1;
    }
    return 0;
}

// Delete a record from the database
void DatabaseHandler::deleteRecord(int key) {
    std::string sql = "DELETE FROM Cache WHERE key = " + std::to_string(key) + ";";
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "Error deleting record: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

// Get a value from the database
std::string DatabaseHandler::getValue(int key) {
    sqlite3_stmt* stmt;
    std::string result;

    std::string sql = "SELECT value FROM Cache WHERE key = " + std::to_string(key) + ";";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* value = sqlite3_column_text(stmt, 0);
            result = reinterpret_cast<const char*>(value);
        }
    } else {
        std::cerr << "Failed to get value: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
    return result;
}
