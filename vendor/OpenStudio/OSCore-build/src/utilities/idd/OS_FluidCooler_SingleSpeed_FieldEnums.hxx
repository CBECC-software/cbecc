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

#ifndef UTILITIES_IDD_OS_FLUIDCOOLER_SINGLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_FLUIDCOOLER_SINGLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_FluidCooler_SingleSpeedFields
 *  \brief Enumeration of OS:FluidCooler:SingleSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_FluidCooler_SingleSpeedFields, )
#else
class OS_FluidCooler_SingleSpeedFields: public ::EnumBase<OS_FluidCooler_SingleSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, WaterInletNode, WaterOutletNode, PerformanceInputMethod, DesignAirFlowRateUfactorTimesAreaValue, NominalCapacity, DesignEnteringWaterTemperature, DesignEnteringAirTemperature, DesignEnteringAirWetbulbTemperature, DesignWaterFlowRate, DesignAirFlowRate, DesignAirFlowRateFanPower, OutdoorAirInletNode,   };
  OS_FluidCooler_SingleSpeedFields()
   : EnumBase<OS_FluidCooler_SingleSpeedFields>(Handle) {} 
  OS_FluidCooler_SingleSpeedFields(const std::string &t_name) 
   : EnumBase<OS_FluidCooler_SingleSpeedFields>(t_name) {} 
  OS_FluidCooler_SingleSpeedFields(int t_value) 
   : EnumBase<OS_FluidCooler_SingleSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_FluidCooler_SingleSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_FluidCooler_SingleSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_FluidCooler_SingleSpeedFields>;
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
{ OS_FluidCooler_SingleSpeedFields::Handle, "Handle", "Handle"},
{ OS_FluidCooler_SingleSpeedFields::Name, "Name", "Name"},
{ OS_FluidCooler_SingleSpeedFields::WaterInletNode, "WaterInletNode", "Water Inlet Node"},
{ OS_FluidCooler_SingleSpeedFields::WaterOutletNode, "WaterOutletNode", "Water Outlet Node"},
{ OS_FluidCooler_SingleSpeedFields::PerformanceInputMethod, "PerformanceInputMethod", "Performance Input Method"},
{ OS_FluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, "DesignAirFlowRateUfactorTimesAreaValue", "Design Air Flow Rate U-factor Times Area Value"},
{ OS_FluidCooler_SingleSpeedFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ OS_FluidCooler_SingleSpeedFields::DesignEnteringWaterTemperature, "DesignEnteringWaterTemperature", "Design Entering Water Temperature"},
{ OS_FluidCooler_SingleSpeedFields::DesignEnteringAirTemperature, "DesignEnteringAirTemperature", "Design Entering Air Temperature"},
{ OS_FluidCooler_SingleSpeedFields::DesignEnteringAirWetbulbTemperature, "DesignEnteringAirWetbulbTemperature", "Design Entering Air Wetbulb Temperature"},
{ OS_FluidCooler_SingleSpeedFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ OS_FluidCooler_SingleSpeedFields::DesignAirFlowRate, "DesignAirFlowRate", "Design Air Flow Rate"},
{ OS_FluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, "DesignAirFlowRateFanPower", "Design Air Flow Rate Fan Power"},
{ OS_FluidCooler_SingleSpeedFields::OutdoorAirInletNode, "OutdoorAirInletNode", "Outdoor Air Inlet Node"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_FluidCooler_SingleSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_FluidCooler_SingleSpeedFields> OptionalOS_FluidCooler_SingleSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_FLUIDCOOLER_SINGLESPEED_FIELDENUMS_HXX
