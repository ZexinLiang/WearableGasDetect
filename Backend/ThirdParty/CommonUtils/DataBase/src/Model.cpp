#include "Utils/DataBase/Model.hpp"
#include <stdexcept>

namespace Utils :: DataBase {
    bool Model::CreateTable(sqlite3 *db, const std::string& tableName, const SQLiteKeyType & columns) {
        std::string sql = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
        for (const auto& [key, value] : columns) {
            if(value == SQLiteDataType::TEXT) sql += key + " TEXT, ";
            else if(value == SQLiteDataType::INTEGER) sql += key + " INTEGER, ";
            else if(value == SQLiteDataType::REAL) sql += key + " REAL, ";
            else if(value == SQLiteDataType::BLOB) sql += key + " BLOB, ";
            else if(value == SQLiteDataType::NONE) sql += key + " NULL, ";
        }
        sql.resize(sql.length() - 2);
        sql += ");";
        int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
        if (rc != SQLITE_OK) {
            // 处理错误
            return false;
        }
        return true;
    }

    bool Model::Insert(sqlite3 *db, const std::string &tableName, const SQLiteKeyValue &data) {
        std::string columns, values;
        for (const auto& [key, value] : data) {
            columns += key + ", ";
            values += "'" + value + "', ";
        }
        columns.resize(columns.length() - 2);
        values.resize(values.length() - 2);

        std::string sql = "INSERT INTO " + tableName + " (" + columns + ") VALUES (" + values + ");";
        int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
        if (rc != SQLITE_OK) {
            // 处理错误
            return false;
        }
        return true;
    }

    SQLiteQueryResult Model::ExecuteQuery(sqlite3 *db, const std::string& sql) {
        SQLiteQueryResult result;
        sqlite3_stmt* stmt = nullptr;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
        }

        int columnCount = sqlite3_column_count(stmt);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::map<std::string, std::string> row;
            for (int i = 0; i < columnCount; ++i) {
                const char* columnName = sqlite3_column_name(stmt, i);
                const unsigned char* columnValue = sqlite3_column_text(stmt, i);
                row[columnName] = columnValue ? reinterpret_cast<const char*>(columnValue) : "";
            }
            result.push_back(row);
        }
        sqlite3_finalize(stmt);
        return result;
    }

    SQLiteQueryResult Model::QueryColumnAll(sqlite3 *db, const std::string& tableName) {
        std::string sql = "SELECT * FROM " + tableName + ";";
        return ExecuteQuery(db, sql);
    }

    SQLiteQueryResult Model::QueryColumnAllCondition(sqlite3 *db, const std::string& tableName, const std::string& condition) {
        std::string sql = "SELECT * FROM " + tableName + " WHERE " + condition + ";";
        return ExecuteQuery(db, sql);
    }

    SQLiteQueryResult Model::QueryColumn(sqlite3 *db, const std::string& tableName, std::vector<std::string> &columns) {
        std::string sql = "SELECT ";
        for(auto &column : columns) {
            sql += column + ", ";
        }
        sql.resize(sql.length() - 2);
        sql += " FROM " + tableName + ";";
        return ExecuteQuery(db, sql);
    }

    SQLiteQueryResult Model::QueryColumnCondition(sqlite3 *db, const std::string& tableName, std::vector<std::string> &columns, const std::string& condition) {
        std::string sql = "SELECT ";
        for(auto &column : columns) {
            sql += column + ", ";
        }
        sql.resize(sql.length() - 2);
        sql += " FROM " + tableName + " WHERE " + condition + ";";
        return ExecuteQuery(db, sql);
    }

    bool Model::Update(sqlite3 *db, const std::string& tableName, const SQLiteKeyValue &data, const std::string& condition) {
        std::string sql = "UPDATE " + tableName + " SET ";
        for (const auto& [key, value] : data) {
            sql += key + "='" ;
            sql += value + "', ";
        }
        sql.resize(sql.length() - 2);
        sql += " WHERE " + condition + ";";
        int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
        if (rc != SQLITE_OK) {
            // 处理错误
            return false;
        }
        return true;
    }

    bool Model::Remove(sqlite3 *db, const std::string& tableName, const std::string& condition) {
        std::string sql = "DELETE FROM " + tableName + " WHERE " + condition + ";";
        int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
        if (rc != SQLITE_OK) {
            // 处理错误
            return false;
        }
        return true;
    }
}