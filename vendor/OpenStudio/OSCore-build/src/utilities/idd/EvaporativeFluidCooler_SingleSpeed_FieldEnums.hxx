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

#ifndef UTILITIES_IDD_EVAPORATIVEFLUIDCOOLER_SINGLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_EVAPORATIVEFLUIDCOOLER_SINGLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class EvaporativeFluidCooler_SingleSpeedFields
 *  \brief Enumeration of EvaporativeFluidCooler:SingleSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(EvaporativeFluidCooler_SingleSpeedFields, )
#else
class EvaporativeFluidCooler_SingleSpeedFields: public ::EnumBase<EvaporativeFluidCooler_SingleSpeedFields> {
 public: 
  enum domain 
  {
Name, WaterInletNodeName, WaterOutletNodeName, DesignAirFlowRate, DesignAirFlowRateFanPower, DesignSprayWaterFlowRate, PerformanceInputMethod, OutdoorAirInletNodeName, HeatRejectionCapacityandNominalCapacitySizingRatio, StandardDesignCapacity, DesignAirFlowRateUfactorTimesAreaValue, DesignWaterFlowRate, UserSpecifiedDesignCapacity, DesignEnteringWaterTemperature, DesignEnteringAirTemperature, DesignEnteringAirWetbulbTemperature, CapacityControl, SizingFactor, EvaporationLossMode, EvaporationLossFactor, DriftLossPercent, BlowdownCalculationMode, BlowdownConcentrationRatio, BlowdownMakeupWaterUsageScheduleName, SupplyWaterStorageTankName,   };
  EvaporativeFluidCooler_SingleSpeedFields()
   : EnumBase<EvaporativeFluidCooler_SingleSpeedFields>(Name) {} 
  EvaporativeFluidCooler_SingleSpeedFields(const std::string &t_name) 
   : EnumBase<EvaporativeFluidCooler_SingleSpeedFields>(t_name) {} 
  EvaporativeFluidCooler_SingleSpeedFields(int t_value) 
   : EnumBase<EvaporativeFluidCooler_SingleSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "EvaporativeFluidCooler_SingleSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<EvaporativeFluidCooler_SingleSpeedFields>::value()); }
   private:
    friend class EnumBase<EvaporativeFluidCooler_SingleSpeedFields>;
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
{ EvaporativeFluidCooler_SingleSpeedFields::Name, "Name", "Name"},
{ EvaporativeFluidCooler_SingleSpeedFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ EvaporativeFluidCooler_SingleSpeedFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRate, "DesignAirFlowRate", "Design Air Flow Rate"},
{ EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, "DesignAirFlowRateFanPower", "Design Air Flow Rate Fan Power"},
{ EvaporativeFluidCooler_SingleSpeedFields::DesignSprayWaterFlowRate, "DesignSprayWaterFlowRate", "Design Spray Water Flow Rate"},
{ EvaporativeFluidCooler_SingleSpeedFields::PerformanceInputMethod, "PerformanceInputMethod", "Performance Input Method"},
{ EvaporativeFluidCooler_SingleSpeedFields::OutdoorAirInletNodeName, "OutdoorAirInletNodeName", "Outdoor Air Inlet Node Name"},
{ EvaporativeFluidCooler_SingleSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio, "HeatRejectionCapacityandNominalCapacitySizingRatio", "Heat Rejection Capacity and Nominal Capacity Sizing Ratio"},
{ EvaporativeFluidCooler_SingleSpeedFields::StandardDesignCapacity, "StandardDesignCapacity", "Standard Design Capacity"},
{ EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, "DesignAirFlowRateUfactorTimesAreaValue", "Design Air Flow Rate U-factor Times Area Value"},
{ EvaporativeFluidCooler_SingleSpeedFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ EvaporativeFluidCooler_SingleSpeedFields::UserSpecifiedDesignCapacity, "UserSpecifiedDesignCapacity", "User Specified Design Capacity"},
{ EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringWaterTemperature, "DesignEnteringWaterTemperature", "Design Entering Water Temperature"},
{ EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringAirTemperature, "DesignEnteringAirTemperature", "Design Entering Air Temperature"},
{ EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringAirWetbulbTemperature, "DesignEnteringAirWetbulbTemperature", "Design Entering Air Wet-bulb Temperature"},
{ EvaporativeFluidCooler_SingleSpeedFields::CapacityControl, "CapacityControl", "Capacity Control"},
{ EvaporativeFluidCooler_SingleSpeedFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ EvaporativeFluidCooler_SingleSpeedFields::EvaporationLossMode, "EvaporationLossMode", "Evaporation Loss Mode"},
{ EvaporativeFluidCooler_SingleSpeedFields::EvaporationLossFactor, "EvaporationLossFactor", "Evaporation Loss Factor"},
{ EvaporativeFluidCooler_SingleSpeedFields::DriftLossPercent, "DriftLossPercent", "Drift Loss Percent"},
{ EvaporativeFluidCooler_SingleSpeedFields::BlowdownCalculationMode, "BlowdownCalculationMode", "Blowdown Calculation Mode"},
{ EvaporativeFluidCooler_SingleSpeedFields::BlowdownConcentrationRatio, "BlowdownConcentrationRatio", "Blowdown Concentration Ratio"},
{ EvaporativeFluidCooler_SingleSpeedFields::BlowdownMakeupWaterUsageScheduleName, "BlowdownMakeupWaterUsageScheduleName", "Blowdown Makeup Water Usage Schedule Name"},
{ EvaporativeFluidCooler_SingleSpeedFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const EvaporativeFluidCooler_SingleSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<EvaporativeFluidCooler_SingleSpeedFields> OptionalEvaporativeFluidCooler_SingleSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_EVAPORATIVEFLUIDCOOLER_SINGLESPEED_FIELDENUMS_HXX
