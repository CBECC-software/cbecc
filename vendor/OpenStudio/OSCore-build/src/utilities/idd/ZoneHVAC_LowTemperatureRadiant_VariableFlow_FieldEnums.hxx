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

#ifndef UTILITIES_IDD_ZONEHVAC_LOWTEMPERATURERADIANT_VARIABLEFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_LOWTEMPERATURERADIANT_VARIABLEFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_LowTemperatureRadiant_VariableFlowFields
 *  \brief Enumeration of ZoneHVAC:LowTemperatureRadiant:VariableFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields, )
#else
class ZoneHVAC_LowTemperatureRadiant_VariableFlowFields: public ::EnumBase<ZoneHVAC_LowTemperatureRadiant_VariableFlowFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, SurfaceNameorRadiantSurfaceGroupName, HydronicTubingInsideDiameter, HydronicTubingLength, TemperatureControlType, HeatingDesignCapacityMethod, HeatingDesignCapacity, HeatingDesignCapacityPerFloorArea, FractionofAutosizedHeatingDesignCapacity, MaximumHotWaterFlow, HeatingWaterInletNodeName, HeatingWaterOutletNodeName, HeatingControlThrottlingRange, HeatingControlTemperatureScheduleName, CoolingDesignCapacityMethod, CoolingDesignCapacity, CoolingDesignCapacityPerFloorArea, FractionofAutosizedCoolingDesignCapacity, MaximumColdWaterFlow, CoolingWaterInletNodeName, CoolingWaterOutletNodeName, CoolingControlThrottlingRange, CoolingControlTemperatureScheduleName, CondensationControlType, CondensationControlDewpointOffset, NumberofCircuits, CircuitLength,   };
  ZoneHVAC_LowTemperatureRadiant_VariableFlowFields()
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_VariableFlowFields>(Name) {} 
  ZoneHVAC_LowTemperatureRadiant_VariableFlowFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_VariableFlowFields>(t_name) {} 
  ZoneHVAC_LowTemperatureRadiant_VariableFlowFields(int t_value) 
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_VariableFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_LowTemperatureRadiant_VariableFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_LowTemperatureRadiant_VariableFlowFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_LowTemperatureRadiant_VariableFlowFields>;
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
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::Name, "Name", "Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::SurfaceNameorRadiantSurfaceGroupName, "SurfaceNameorRadiantSurfaceGroupName", "Surface Name or Radiant Surface Group Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HydronicTubingInsideDiameter, "HydronicTubingInsideDiameter", "Hydronic Tubing Inside Diameter"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HydronicTubingLength, "HydronicTubingLength", "Hydronic Tubing Length"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::TemperatureControlType, "TemperatureControlType", "Temperature Control Type"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacityMethod, "HeatingDesignCapacityMethod", "Heating Design Capacity Method"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacity, "HeatingDesignCapacity", "Heating Design Capacity"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacityPerFloorArea, "HeatingDesignCapacityPerFloorArea", "Heating Design Capacity Per Floor Area"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::FractionofAutosizedHeatingDesignCapacity, "FractionofAutosizedHeatingDesignCapacity", "Fraction of Autosized Heating Design Capacity"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumHotWaterFlow, "MaximumHotWaterFlow", "Maximum Hot Water Flow"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterInletNodeName, "HeatingWaterInletNodeName", "Heating Water Inlet Node Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterOutletNodeName, "HeatingWaterOutletNodeName", "Heating Water Outlet Node Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingControlThrottlingRange, "HeatingControlThrottlingRange", "Heating Control Throttling Range"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingControlTemperatureScheduleName, "HeatingControlTemperatureScheduleName", "Heating Control Temperature Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacityMethod, "CoolingDesignCapacityMethod", "Cooling Design Capacity Method"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, "CoolingDesignCapacity", "Cooling Design Capacity"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacityPerFloorArea, "CoolingDesignCapacityPerFloorArea", "Cooling Design Capacity Per Floor Area"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::FractionofAutosizedCoolingDesignCapacity, "FractionofAutosizedCoolingDesignCapacity", "Fraction of Autosized Cooling Design Capacity"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, "MaximumColdWaterFlow", "Maximum Cold Water Flow"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterInletNodeName, "CoolingWaterInletNodeName", "Cooling Water Inlet Node Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterOutletNodeName, "CoolingWaterOutletNodeName", "Cooling Water Outlet Node Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingControlThrottlingRange, "CoolingControlThrottlingRange", "Cooling Control Throttling Range"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingControlTemperatureScheduleName, "CoolingControlTemperatureScheduleName", "Cooling Control Temperature Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CondensationControlType, "CondensationControlType", "Condensation Control Type"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CondensationControlDewpointOffset, "CondensationControlDewpointOffset", "Condensation Control Dewpoint Offset"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::NumberofCircuits, "NumberofCircuits", "Number of Circuits"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CircuitLength, "CircuitLength", "Circuit Length"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_LowTemperatureRadiant_VariableFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_LowTemperatureRadiant_VariableFlowFields> OptionalZoneHVAC_LowTemperatureRadiant_VariableFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_LOWTEMPERATURERADIANT_VARIABLEFLOW_FIELDENUMS_HXX
