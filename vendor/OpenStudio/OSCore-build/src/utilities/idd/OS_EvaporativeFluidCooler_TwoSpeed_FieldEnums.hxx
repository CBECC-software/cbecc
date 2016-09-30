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

#ifndef UTILITIES_IDD_OS_EVAPORATIVEFLUIDCOOLER_TWOSPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_EVAPORATIVEFLUIDCOOLER_TWOSPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_EvaporativeFluidCooler_TwoSpeedFields
 *  \brief Enumeration of OS:EvaporativeFluidCooler:TwoSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_EvaporativeFluidCooler_TwoSpeedFields, )
#else
class OS_EvaporativeFluidCooler_TwoSpeedFields: public ::EnumBase<OS_EvaporativeFluidCooler_TwoSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, WaterInletNodeName, WaterOutletNodeName, HighFanSpeedAirFlowRate, HighFanSpeedFanPower, LowFanSpeedAirFlowRate, LowFanSpeedAirFlowRateSizingFactor, LowFanSpeedFanPower, LowFanSpeedFanPowerSizingFactor, DesignSprayWaterFlowRate, PerformanceInputMethod, OutdoorAirInletNodeName, HeatRejectionCapacityandNominalCapacitySizingRatio, HighSpeedStandardDesignCapacity, LowSpeedStandardDesignCapacity, LowSpeedStandardCapacitySizingFactor, HighFanSpeedUfactorTimesAreaValue, LowFanSpeedUfactorTimesAreaValue, LowFanSpeedUFactorTimesAreaSizingFactor, DesignWaterFlowRate, HighSpeedUserSpecifiedDesignCapacity, LowSpeedUserSpecifiedDesignCapacity, LowSpeedUserSpecifiedDesignCapacitySizingFactor, DesignEnteringWaterTemperature, DesignEnteringAirTemperature, DesignEnteringAirWetbulbTemperature, HighSpeedSizingFactor, EvaporationLossMode, EvaporationLossFactor, DriftLossPercent, BlowdownCalculationMode, BlowdownConcentrationRatio, BlowdownMakeupWaterUsageScheduleName, SupplyWaterStorageTankName,   };
  OS_EvaporativeFluidCooler_TwoSpeedFields()
   : EnumBase<OS_EvaporativeFluidCooler_TwoSpeedFields>(Handle) {} 
  OS_EvaporativeFluidCooler_TwoSpeedFields(const std::string &t_name) 
   : EnumBase<OS_EvaporativeFluidCooler_TwoSpeedFields>(t_name) {} 
  OS_EvaporativeFluidCooler_TwoSpeedFields(int t_value) 
   : EnumBase<OS_EvaporativeFluidCooler_TwoSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_EvaporativeFluidCooler_TwoSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_EvaporativeFluidCooler_TwoSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_EvaporativeFluidCooler_TwoSpeedFields>;
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
{ OS_EvaporativeFluidCooler_TwoSpeedFields::Handle, "Handle", "Handle"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::Name, "Name", "Name"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, "HighFanSpeedAirFlowRate", "High Fan Speed Air Flow Rate"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedFanPower, "HighFanSpeedFanPower", "High Fan Speed Fan Power"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, "LowFanSpeedAirFlowRate", "Low Fan Speed Air Flow Rate"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, "LowFanSpeedAirFlowRateSizingFactor", "Low Fan Speed Air Flow Rate Sizing Factor"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedFanPower, "LowFanSpeedFanPower", "Low Fan Speed Fan Power"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, "LowFanSpeedFanPowerSizingFactor", "Low Fan Speed Fan Power Sizing Factor"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::DesignSprayWaterFlowRate, "DesignSprayWaterFlowRate", "Design Spray Water Flow Rate"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::PerformanceInputMethod, "PerformanceInputMethod", "Performance Input Method"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::OutdoorAirInletNodeName, "OutdoorAirInletNodeName", "Outdoor Air Inlet Node Name"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio, "HeatRejectionCapacityandNominalCapacitySizingRatio", "Heat Rejection Capacity and Nominal Capacity Sizing Ratio"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::HighSpeedStandardDesignCapacity, "HighSpeedStandardDesignCapacity", "High Speed Standard Design Capacity"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::LowSpeedStandardDesignCapacity, "LowSpeedStandardDesignCapacity", "Low Speed Standard Design Capacity"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::LowSpeedStandardCapacitySizingFactor, "LowSpeedStandardCapacitySizingFactor", "Low Speed Standard Capacity Sizing Factor"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, "HighFanSpeedUfactorTimesAreaValue", "High Fan Speed U-factor Times Area Value"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, "LowFanSpeedUfactorTimesAreaValue", "Low Fan Speed U-factor Times Area Value"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor, "LowFanSpeedUFactorTimesAreaSizingFactor", "Low Fan Speed U-Factor Times Area Sizing Factor"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::HighSpeedUserSpecifiedDesignCapacity, "HighSpeedUserSpecifiedDesignCapacity", "High Speed User Specified Design Capacity"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::LowSpeedUserSpecifiedDesignCapacity, "LowSpeedUserSpecifiedDesignCapacity", "Low Speed User Specified Design Capacity"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::LowSpeedUserSpecifiedDesignCapacitySizingFactor, "LowSpeedUserSpecifiedDesignCapacitySizingFactor", "Low Speed User Specified Design Capacity Sizing Factor"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringWaterTemperature, "DesignEnteringWaterTemperature", "Design Entering Water Temperature"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringAirTemperature, "DesignEnteringAirTemperature", "Design Entering Air Temperature"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringAirWetbulbTemperature, "DesignEnteringAirWetbulbTemperature", "Design Entering Air Wet-bulb Temperature"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::HighSpeedSizingFactor, "HighSpeedSizingFactor", "High Speed Sizing Factor"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::EvaporationLossMode, "EvaporationLossMode", "Evaporation Loss Mode"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::EvaporationLossFactor, "EvaporationLossFactor", "Evaporation Loss Factor"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::DriftLossPercent, "DriftLossPercent", "Drift Loss Percent"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::BlowdownCalculationMode, "BlowdownCalculationMode", "Blowdown Calculation Mode"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::BlowdownConcentrationRatio, "BlowdownConcentrationRatio", "Blowdown Concentration Ratio"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::BlowdownMakeupWaterUsageScheduleName, "BlowdownMakeupWaterUsageScheduleName", "Blowdown Makeup Water Usage Schedule Name"},
{ OS_EvaporativeFluidCooler_TwoSpeedFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_EvaporativeFluidCooler_TwoSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_EvaporativeFluidCooler_TwoSpeedFields> OptionalOS_EvaporativeFluidCooler_TwoSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_EVAPORATIVEFLUIDCOOLER_TWOSPEED_FIELDENUMS_HXX
