/* Copyright (c) 2023 Big Ladder Software LLC. All rights reserved.
 * See the LICENSE file for additional terms and conditions. */

#ifndef CUACTOOLMINER_H_
#define CUACTOOLMINER_H_

#include <iostream>
#include <vector>

#include <courierr/courierr.h>
#include <nanodbc/nanodbc.h>

#include <CUACToolMiner/AccessMiner.h>

class CUACToolMiner : public AccessMiner {

  public:
    CUACToolMiner(const std::string sOutputFilename) : AccessMiner(sOutputFilename) {}
    CUACToolMiner() : AccessMiner() {}

    int get_project_ID(const std::string& sProject_name, long& project_ID);
    int get_project_list(std::vector<std::string>& vsProjects);
    int get_project_tables(const int project_ID_in,
                           const std::vector<std::string>& vsTable_names,
                           Tables& tables);

    static const std::vector<std::string> sStandard_global_table_names;
    static const std::vector<std::string> sStandard_project_table_names;

  private:
    int get_dryer_use_project_table(const int projectID_in, Table& table);
    int get_specific_dryer_use_project_table(const int projectID_in,
                                             const std::size_t i_use_col,
                                             Table& table);
    int get_dryer_electric_use_project_table(const int projectID_in, Table& table);
    int get_dryer_gas_use_project_table(const int projectID_in, Table& table);
    int get_summary_electric_use_project_table(const int projectID_in, Table& table);
    int get_summary_gas_use_project_table(const int projectID_in, Table& table);
    int get_summary_Cecpv_project_table(const int projectID_in, Table& table);

    enum DryerFuelColumn { electric_fuel_col = 2, gas_fuel_col = 3 };

}; // class CUACToolMiner

int getProjectList(CUACToolMiner& mainDB, std::vector<std::string>& vsProjects);
int getProjectData(CUACToolMiner& mainDB, std::string sProjectName, std::string sProjDataPath);

int getTables(
    CUACToolMiner& mainDB,
    CUACToolMiner::Tables& tables,
    const std::vector<std::string>& sTablesNames = CUACToolMiner::sStandard_global_table_names);

int getProjectTables(
    CUACToolMiner& mainDB,
    std::string sProjectName,
    CUACToolMiner::Tables& tables,
    const std::vector<std::string>& sTablesNames = CUACToolMiner::sStandard_project_table_names);

int exportTables(
    CUACToolMiner& mainDB,
    std::string sDataPath,
    const std::vector<std::string>& sTablesNames = CUACToolMiner::sStandard_global_table_names);

int exportProjectTables(
    CUACToolMiner& mainDB,
    std::string sProjectName,
    std::string sProjDataPath,
    const std::vector<std::string>& sTablesNames = CUACToolMiner::sStandard_project_table_names);

#endif // define CUACTOOLMINER_H_