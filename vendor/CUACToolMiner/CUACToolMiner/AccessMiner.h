/* Copyright (c) 2023 Big Ladder Software LLC. All rights reserved.
 * See the LICENSE file for additional terms and conditions. */

#ifndef ACCESSMINER_H_
#define ACCESSMINER_H_

#include <iostream>
#include <fstream>
#include <vector>

// vendor
#include <courierr/courierr.h>
#include <nanodbc/nanodbc.h>

class AccessMiner {
  public:
    class Logger : public Courierr::Courierr {
      public:
        Logger(const std::string& sLogFilename = "",
               const unsigned logFileMode = std::ofstream::out | std::ofstream::trunc)
            : logStream(&std::cout)
        {
            isFile = false;
            if (sLogFilename != "") {
                std::ostream* tempStream = new std::ofstream;
                std::ofstream* outputFile = static_cast<std::ofstream*>(tempStream);
                outputFile->open(sLogFilename.c_str(), logFileMode);
                isFile = outputFile->is_open();
                if (isFile) {
                    logStream = tempStream;
                }
                else {
                    std::cout << "Could not open output file " << sLogFilename << "\n";
                }
            }
        }
        ~Logger()
        {
            if (isFile) {
                delete logStream;
            }
        }

        void error(const std::string_view message) override { write_message("ERROR", message); }
        void warning(const std::string_view message) override
        {
            if (isFile)
                write_message("WARNING", message);
        }
        void info(const std::string_view message) override
        {
            if (isFile)
                write_message("NOTE", message);
        }
        void debug(const std::string_view message) override
        {
            if (isFile)
                write_message("DEBUG", message);
        }

      protected:
        void write_message(const std::string_view message_type, const std::string_view message)
        {
            std::string context_string =
                message_context
                    ? fmt::format(" ({})", *(reinterpret_cast<std::string*>(message_context)))
                    : "";

            *logStream << fmt::format(" [{}]{} {}", message_type, context_string, message)
                       << std::endl;
        }

      private:
        std::ostream* logStream;
        bool isFile;
    };

    class Exception : public Courierr::CourierrException {
      public:
        explicit Exception(const std::string& message, Courierr::Courierr& logger)
            : CourierrException(message, logger)
        {
        }
    };

    enum DataType { bool_type, int_type, double_type, string_type };

    static DataType get_data_type(const std::string& type_name);

    typedef std::variant<bool, int, double, std::string> DataVariant;
    struct DataValue : public DataVariant {

        DataValue() : DataVariant(false) {}
        DataValue(const bool x) : DataVariant(x) {}
        DataValue(const int x) : DataVariant(x) {}
        DataValue(const double x) : DataVariant(x) {}
        DataValue(const std::string& x) : DataVariant(x) {}
        ~DataValue() {}

        bool as_bool() const;
        int as_int() const;
        double as_double() const;
        std::string as_string() const;

    }; // struct DataValue

    typedef std::pair<std::string, DataType> ColumnDesc;          // column name, datatype
    typedef std::pair<ColumnDesc, std::vector<DataValue>> Column; // column info, data
    typedef std::pair<std::string, std::vector<Column>> Table;    // table name, table data
    typedef std::vector<Table> Tables;

    static Column make_column(const std::string& sCol_name,
                              const DataType data_type,
                              const std::vector<DataValue>& vColVals = {});

    std::shared_ptr<Logger> logger;

  private:
    nanodbc::connection conn;

  public:
    enum Error {
        no_error = 0,
        data_error = 1,
        odbc_error = 2,
        fileio_error = 3,
        runtime_error = 4,
    };

    AccessMiner(const std::shared_ptr<Logger>& logger_in = std::make_shared<Logger>());
    AccessMiner(const std::string& sLogFilename, const unsigned logFileMode = std::ifstream::app);
    int open_connection(std::string sDBPathFilename);
    int do_query(const std::string& command, nanodbc::result& found_values);
    int get_column_names(std::string sTable_name, std::vector<std::string>& vsCol_names);
    int get_column_descriptions(std::string sTable_name, std::vector<ColumnDesc>& vCol_descs);

    int get_table(const std::string& sTable_name, Table& table);

    int export_table(const Table& table, const std::string& sDataPathFilename);

    int
    combine_tables(Tables& tables, const std::string& sCombined_table_name, Table& combined_table);
    int get_tables(const std::vector<std::string>& vsTable_names, Tables& tables);

    int get_column(std::string sTable_name,
                   std::string sCol_name,
                   Column& col,
                   std::string condition = "");

    template <typename Tvalue>
    int get_column_values(std::string sTable_name,
                          std::string sCol_name,
                          std::vector<Tvalue>& vtValues,
                          std::string condition = "");

    template <typename Tvalue>
    int get_column_value(std::string sTable_name,
                         std::string sCol_name,
                         Tvalue& tValue,
                         std::string condition = "");

    template <typename Tkey, typename Tvalue>
    int get_key_values(const std::string& sTable_name,
                       const std::string& sKey_name,
                       const std::string& sCol_name,
                       const Tkey& tKey,
                       std::vector<Tvalue>& vtValues);

    template <typename Tkey, typename Tvalue>
    int get_key_value(const std::string& sTable_name,
                      const std::string& sKey_name,
                      const std::string& sValue_name,
                      const Tkey& tKey,
                      Tvalue& tValue);

    template <typename Tkey, typename Tvalue, typename Tvaluep = Tvalue>
    int get_key_column(const std::string& sTable_name,
                       const std::string& sCol_name,
                       const std::string& sKey_name,
                       const Tkey& tKey,
                       std::vector<DataValue>& col_vals);

    template <typename Tkey>
    int get_key_table(const std::string& sTable_name,
                      const std::string& sKey_name,
                      const Tkey& tKey,
                      Table& table);

    int get_column_data_type(std::string sTable_name, std::string sCol_name, DataType& data_type);
}; // class AccessMiner

std::string fix_sql_string(const std::string& sIn);

template <typename Tvalue>
int AccessMiner::get_column_values(std::string sTable_name,
                                   std::string sCol_name,
                                   std::vector<Tvalue>& vtValues,
                                   std::string condition)
{
    int res = no_error;
    try {
        sCol_name = fix_sql_string(sCol_name);
        sTable_name = fix_sql_string(sTable_name);

        std::string command = fmt::format("SELECT {} FROM {}", sCol_name, sTable_name);
        if (!condition.empty())
            command = fmt::format("{} WHERE {}", command, condition);
        nanodbc::result found_values = execute(conn, NANODBC_TEXT(command));
        for (int i = 1; found_values.next(); ++i) {
            auto s = found_values.get<Tvalue>(0, Tvalue());
            vtValues.push_back(s);
        }
    }
    catch (nanodbc::database_error const& e) {
        logger->error(fmt::format(
            "Error reading column values from table {}, column {}", sTable_name, sCol_name));
        logger->error(fmt::format("odbc error: {}", std::string(e.what())));
        res = odbc_error;
    }
    return res;
}

template <typename Tvalue>
int AccessMiner::get_column_value(std::string sTable_name,
                                  std::string sCol_name,
                                  Tvalue& tValue,
                                  std::string condition)
{
    std::vector<Tvalue> found_values;
    int res = get_column_values(sTable_name, sCol_name, found_values, condition);
    if (res != no_error)
        return res;

    if (!found_values.empty())
        tValue = found_values[0];

    return res;
}

template <typename Tkey, typename Tvalue>
int AccessMiner::get_key_values(const std::string& sTable_name,
                                const std::string& sKey_name,
                                const std::string& sCol_name,
                                const Tkey& tKey,
                                std::vector<Tvalue>& vtValues)
{
    std::vector<std::string> vsCol_names;
    int res = get_column_names(sTable_name, vsCol_names);
    if (res != no_error)
        return res;

    std::vector<Tkey> found_keys;
    res = get_column_values(sTable_name, sKey_name, found_keys);
    if (res != no_error)
        return res;

    std::vector<Tvalue> found_values;
    res = get_column_values(sTable_name, sCol_name, found_values);
    if (res != no_error)
        return res;

    long iRow = 0;
    bool found = false;
    for (auto& keyp : found_keys) {
        if (keyp == tKey) {
            vtValues.push_back(found_values[iRow]);
            found = true;
        }
        ++iRow;
    }
    return res;
}

template <typename Tkey, typename Tvalue>
int AccessMiner::get_key_value(const std::string& sTable_name,
                               const std::string& sKey_name,
                               const std::string& sCol_name,
                               const Tkey& key,
                               Tvalue& tValue)
{
    std::vector<Tvalue> found_values;
    int res = get_key_values(sTable_name, sKey_name, sCol_name, key, found_values);
    if (res != no_error)
        return res;

    if (!found_values.empty())
        tValue = found_values[0]; // Take first matching entry (may not be unique)
    return res;
}

template <typename Tkey, typename Tvalue, typename Tvaluep>
int AccessMiner::get_key_column(const std::string& sTable_name,
                                const std::string& sCol_name,
                                const std::string& sKey_name,
                                const Tkey& tKey,
                                std::vector<DataValue>& col_vals)
{
    std::vector<Tvaluep> vals;
    int res = get_key_values(sTable_name, sKey_name, sCol_name, tKey, vals);
    if (res != no_error)
        return res;
    for (auto& val : vals)
        col_vals.emplace_back(Tvalue(val));
    return res;
}

template <typename Tkey>
int AccessMiner::get_key_table(const std::string& sTable_name,
                               const std::string& sKey_name,
                               const Tkey& tKey,
                               AccessMiner::Table& table)
{

    AccessMiner::Table full_table;
    int res = get_table(sTable_name, full_table);
    if (res != no_error)
        return res;

    table.first = sTable_name;
    std::vector<std::string> col_names;

    for (auto& col : full_table.second) {
        auto& col_desc = col.first;
        auto& col_name = col_desc.first;
        col_names.push_back(col_name);
    }

    std::size_t iCol(0);
    std::vector<std::size_t> col_nums;
    AccessMiner::Column key_col;
    bool has_key(false);
    for (auto& col_name : col_names) {
        if (col_name == sKey_name) {
            has_key = true;
            key_col = full_table.second[iCol];
        }
        else
            col_nums.push_back(iCol);
        ++iCol;
    }

    if (!has_key)
        return res;

    std::size_t iRow(0);
    std::vector<std::size_t> row_nums;
    for (auto& key : key_col.second) {
        if (Tkey(key.as_int()) == tKey) { // keys required to be int
            row_nums.push_back(iRow);
        }
        ++iRow;
    }

    for (auto col_num : col_nums) {
        auto& full_col = full_table.second[col_num];
        auto& col_desc = full_col.first;
        auto& col_name = col_desc.first;
        DataType data_type = col_desc.second;

        table.second.emplace_back(std::make_pair(col_name, data_type), std::vector<DataValue>());
        auto& col = table.second.back();
        for (auto& row_num : row_nums) {
            DataValue& val = full_col.second[row_num];
            col.second.push_back(val);
        }
    }
    return res;
}

#endif // define ACCESSMINER_H_