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

#ifndef UTILITIES_IDD_ZONEHVAC_BASEBOARD_CONVECTIVE_WATER_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_BASEBOARD_CONVECTIVE_WATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_Baseboard_Convective_WaterFields
 *  \brief Enumeration of ZoneHVAC:Baseboard:Convective:Water's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_Baseboard_Convective_WaterFields, )
#else
class ZoneHVAC_Baseboard_Convective_WaterFields: public ::EnumBase<ZoneHVAC_Baseboard_Convective_WaterFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, InletNodeName, OutletNodeName, HeatingDesignCapacityMethod, HeatingDesignCapacity, HeatingDesignCapacityPerFloorArea, FractionofAutosizedHeatingDesignCapacity, UFactorTimesAreaValue, MaximumWaterFlowRate, ConvergenceTolerance,   };
  ZoneHVAC_Baseboard_Convective_WaterFields()
   : EnumBase<ZoneHVAC_Baseboard_Convective_WaterFields>(Name) {} 
  ZoneHVAC_Baseboard_Convective_WaterFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_Baseboard_Convective_WaterFields>(t_name) {} 
  ZoneHVAC_Baseboard_Convective_WaterFields(int t_value) 
   : EnumBase<ZoneHVAC_Baseboard_Convective_WaterFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_Baseboard_Convective_WaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_Baseboard_Convective_WaterFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_Baseboard_Convective_WaterFields>;
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
{ ZoneHVAC_Baseboard_Convective_WaterFields::Name, "Name", "Name"},
{ ZoneHVAC_Baseboard_Convective_WaterFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_Baseboard_Convective_WaterFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ ZoneHVAC_Baseboard_Convective_WaterFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityMethod, "HeatingDesignCapacityMethod", "Heating Design Capacity Method"},
{ ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacity, "HeatingDesignCapacity", "Heating Design Capacity"},
{ ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityPerFloorArea, "HeatingDesignCapacityPerFloorArea", "Heating Design Capacity Per Floor Area"},
{ ZoneHVAC_Baseboard_Convective_WaterFields::FractionofAutosizedHeatingDesignCapacity, "FractionofAutosizedHeatingDesignCapacity", "Fraction of Autosized Heating Design Capacity"},
{ ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue, "UFactorTimesAreaValue", "U-Factor Times Area Value"},
{ ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate, "MaximumWaterFlowRate", "Maximum Water Flow Rate"},
{ ZoneHVAC_Baseboard_Convective_WaterFields::ConvergenceTolerance, "ConvergenceTolerance", "Convergence Tolerance"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_Baseboard_Convective_WaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_Baseboard_Convective_WaterFields> OptionalZoneHVAC_Baseboard_Convective_WaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_BASEBOARD_CONVECTIVE_WATER_FIELDENUMS_HXX
