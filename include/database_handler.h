#ifndef DATABASE_HANDLER_H
#define DATABASE_HANDLER_H

#include <iostream>
#include <vector>
#include <sqlite3.h>

class DatabaseHandler {
private:
    sqlite3* db;
    char* errorMessage;

public:
    DatabaseHandler(const std::string& dbName);
    ~DatabaseHandler();
    std::vector<std::pair<int, std::string>> fetchRecords();
    int insertRecord(int key, const std::string& value);
    void deleteRecord(int key);
    std::string getValue(int key);
};

#endif
