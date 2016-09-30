/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_COIL_COOLING_DX_TWOSTAGEWITHHUMIDITYCONTROLMODE_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_DX_TWOSTAGEWITHHUMIDITYCONTROLMODE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_DX_TwoStageWithHumidityControlModeFields
 *  \brief Enumeration of Coil:Cooling:DX:TwoStageWithHumidityControlMode's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_DX_TwoStageWithHumidityControlModeFields, )
#else
class Coil_Cooling_DX_TwoStageWithHumidityControlModeFields: public ::EnumBase<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, CrankcaseHeaterCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, NumberofCapacityStages, NumberofEnhancedDehumidificationModes, NormalModeStage1CoilPerformanceObjectType, NormalModeStage1CoilPerformanceName, NormalModeStage1_PLUS_2CoilPerformanceObjectType, NormalModeStage1_PLUS_2CoilPerformanceName, DehumidificationMode1Stage1CoilPerformanceObjectType, DehumidificationMode1Stage1CoilPerformanceName, DehumidificationMode1Stage1_PLUS_2CoilPerformanceObjectType, DehumidificationMode1Stage1_PLUS_2CoilPerformanceName, SupplyWaterStorageTankName, CondensateCollectionWaterStorageTankName, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName,   };
  Coil_Cooling_DX_TwoStageWithHumidityControlModeFields()
   : EnumBase<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields>(Name) {} 
  Coil_Cooling_DX_TwoStageWithHumidityControlModeFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields>(t_name) {} 
  Coil_Cooling_DX_TwoStageWithHumidityControlModeFields(int t_value) 
   : EnumBase<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_DX_TwoStageWithHumidityControlModeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields>;
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
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::Name, "Name", "Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NumberofCapacityStages, "NumberofCapacityStages", "Number of Capacity Stages"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NumberofEnhancedDehumidificationModes, "NumberofEnhancedDehumidificationModes", "Number of Enhanced Dehumidification Modes"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1CoilPerformanceObjectType, "NormalModeStage1CoilPerformanceObjectType", "Normal Mode Stage 1 Coil Performance Object Type"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1CoilPerformanceName, "NormalModeStage1CoilPerformanceName", "Normal Mode Stage 1 Coil Performance Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1_PLUS_2CoilPerformanceObjectType, "NormalModeStage1_PLUS_2CoilPerformanceObjectType", "Normal Mode Stage 1+2 Coil Performance Object Type"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1_PLUS_2CoilPerformanceName, "NormalModeStage1_PLUS_2CoilPerformanceName", "Normal Mode Stage 1+2 Coil Performance Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1CoilPerformanceObjectType, "DehumidificationMode1Stage1CoilPerformanceObjectType", "Dehumidification Mode 1 Stage 1 Coil Performance Object Type"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1CoilPerformanceName, "DehumidificationMode1Stage1CoilPerformanceName", "Dehumidification Mode 1 Stage 1 Coil Performance Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1_PLUS_2CoilPerformanceObjectType, "DehumidificationMode1Stage1_PLUS_2CoilPerformanceObjectType", "Dehumidification Mode 1 Stage 1+2 Coil Performance Object Type"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1_PLUS_2CoilPerformanceName, "DehumidificationMode1Stage1_PLUS_2CoilPerformanceName", "Dehumidification Mode 1 Stage 1+2 Coil Performance Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::CondensateCollectionWaterStorageTankName, "CondensateCollectionWaterStorageTankName", "Condensate Collection Water Storage Tank Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_DX_TwoStageWithHumidityControlModeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields> OptionalCoil_Cooling_DX_TwoStageWithHumidityControlModeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_DX_TWOSTAGEWITHHUMIDITYCONTROLMODE_FIELDENUMS_HXX
