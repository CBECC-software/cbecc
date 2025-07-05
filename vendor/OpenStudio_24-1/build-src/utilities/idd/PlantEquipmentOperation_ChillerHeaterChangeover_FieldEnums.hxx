/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_PLANTEQUIPMENTOPERATION_CHILLERHEATERCHANGEOVER_FIELDENUMS_HXX
#define UTILITIES_IDD_PLANTEQUIPMENTOPERATION_CHILLERHEATERCHANGEOVER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PlantEquipmentOperation_ChillerHeaterChangeoverFields
 *  \brief Enumeration of PlantEquipmentOperation:ChillerHeaterChangeover's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PlantEquipmentOperation_ChillerHeaterChangeoverFields, )
#else
class PlantEquipmentOperation_ChillerHeaterChangeoverFields: public ::EnumBase<PlantEquipmentOperation_ChillerHeaterChangeoverFields> {
 public: 
  enum domain 
  {
Name, PrimaryCoolingPlantSetpointTemperature, SecondaryDistributionCoolingPlantSetpointTemperature, PrimaryHeatingPlantSetpointatOutdoorHighTemperature, OutdoorHighTemperature, PrimaryHeatingPlantSetpointatOutdoorLowTemperature, OutdoorLowTemperature, SecondaryDistributionHeatingPlantSetpointTemperature, ZoneLoadPollingZoneListName, CoolingOnlyLoadPlantEquipmentOperationCoolingLoadName, HeatingOnlyLoadPlantEquipmentOperationHeatingLoadName, SimultaneousCoolingAndHeatingPlantEquipmentOperationCoolingLoadName, SimultaneousCoolingAndHeatingPlantEquipmentOperationHeatingLoadName, DedicatedChilledWaterReturnRecoveryHeatPumpName, DedicatedHotWaterReturnRecoveryHeatPumpName, BoilerSetpointTemperatureOffset, PrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature, BackupOutdoorLowTemperature,   };
  PlantEquipmentOperation_ChillerHeaterChangeoverFields()
   : EnumBase<PlantEquipmentOperation_ChillerHeaterChangeoverFields>(Name) {} 
  PlantEquipmentOperation_ChillerHeaterChangeoverFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_ChillerHeaterChangeoverFields>(t_name) {} 
  PlantEquipmentOperation_ChillerHeaterChangeoverFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_ChillerHeaterChangeoverFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_ChillerHeaterChangeoverFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_ChillerHeaterChangeoverFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_ChillerHeaterChangeoverFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::Name, "Name", "Name"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryCoolingPlantSetpointTemperature, "PrimaryCoolingPlantSetpointTemperature", "Primary Cooling Plant Setpoint Temperature"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::SecondaryDistributionCoolingPlantSetpointTemperature, "SecondaryDistributionCoolingPlantSetpointTemperature", "Secondary Distribution Cooling Plant Setpoint Temperature"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryHeatingPlantSetpointatOutdoorHighTemperature, "PrimaryHeatingPlantSetpointatOutdoorHighTemperature", "Primary Heating Plant Setpoint at Outdoor High Temperature"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::OutdoorHighTemperature, "OutdoorHighTemperature", "Outdoor High Temperature"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryHeatingPlantSetpointatOutdoorLowTemperature, "PrimaryHeatingPlantSetpointatOutdoorLowTemperature", "Primary Heating Plant Setpoint at Outdoor Low Temperature"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::OutdoorLowTemperature, "OutdoorLowTemperature", "Outdoor Low Temperature"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::SecondaryDistributionHeatingPlantSetpointTemperature, "SecondaryDistributionHeatingPlantSetpointTemperature", "Secondary Distribution Heating Plant Setpoint Temperature"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::ZoneLoadPollingZoneListName, "ZoneLoadPollingZoneListName", "Zone Load Polling ZoneList Name"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::CoolingOnlyLoadPlantEquipmentOperationCoolingLoadName, "CoolingOnlyLoadPlantEquipmentOperationCoolingLoadName", "Cooling Only Load Plant Equipment Operation Cooling Load Name"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::HeatingOnlyLoadPlantEquipmentOperationHeatingLoadName, "HeatingOnlyLoadPlantEquipmentOperationHeatingLoadName", "Heating Only Load Plant Equipment Operation Heating Load Name"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::SimultaneousCoolingAndHeatingPlantEquipmentOperationCoolingLoadName, "SimultaneousCoolingAndHeatingPlantEquipmentOperationCoolingLoadName", "Simultaneous Cooling And Heating Plant Equipment Operation Cooling Load Name"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::SimultaneousCoolingAndHeatingPlantEquipmentOperationHeatingLoadName, "SimultaneousCoolingAndHeatingPlantEquipmentOperationHeatingLoadName", "Simultaneous Cooling And Heating Plant Equipment Operation Heating Load Name"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::DedicatedChilledWaterReturnRecoveryHeatPumpName, "DedicatedChilledWaterReturnRecoveryHeatPumpName", "Dedicated Chilled Water Return Recovery Heat Pump Name"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::DedicatedHotWaterReturnRecoveryHeatPumpName, "DedicatedHotWaterReturnRecoveryHeatPumpName", "Dedicated Hot Water Return Recovery Heat Pump Name"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::BoilerSetpointTemperatureOffset, "BoilerSetpointTemperatureOffset", "Boiler Setpoint Temperature Offset"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature, "PrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature", "Primary Heating Plant Setpoint at Backup Outdoor Low Temperature"},
{ PlantEquipmentOperation_ChillerHeaterChangeoverFields::BackupOutdoorLowTemperature, "BackupOutdoorLowTemperature", "Backup Outdoor Low Temperature"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_ChillerHeaterChangeoverFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_ChillerHeaterChangeoverFields> OptionalPlantEquipmentOperation_ChillerHeaterChangeoverFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PLANTEQUIPMENTOPERATION_CHILLERHEATERCHANGEOVER_FIELDENUMS_HXX
