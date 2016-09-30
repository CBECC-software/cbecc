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

#ifndef UTILITIES_IDD_OS_COOLINGTOWER_TWOSPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COOLINGTOWER_TWOSPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_CoolingTower_TwoSpeedFields
 *  \brief Enumeration of OS:CoolingTower:TwoSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_CoolingTower_TwoSpeedFields, )
#else
class OS_CoolingTower_TwoSpeedFields: public ::EnumBase<OS_CoolingTower_TwoSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, WaterInletNodeName, WaterOutletNodeName, DesignWaterFlowRate, HighFanSpeedAirFlowRate, HighFanSpeedFanPower, HighFanSpeedUFactorTimesAreaValue, LowFanSpeedAirFlowRate, LowFanSpeedAirFlowRateSizingFactor, LowFanSpeedFanPower, LowFanSpeedFanPowerSizingFactor, LowFanSpeedUFactorTimesAreaValue, LowFanSpeedUFactorTimesAreaSizingFactor, FreeConvectionRegimeAirFlowRate, FreeConvectionRegimeAirFlowRateSizingFactor, FreeConvectionRegimeUFactorTimesAreaValue, FreeConvectionUFactorTimesAreaValueSizingFactor, PerformanceInputMethod, HeatRejectionCapacityandNominalCapacitySizingRatio, HighSpeedNominalCapacity, LowSpeedNominalCapacity, LowSpeedNominalCapacitySizingFactor, FreeConvectionNominalCapacity, FreeConvectionNominalCapacitySizingFactor, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, EvaporationLossMode, EvaporationLossFactor, DriftLossPercent, BlowdownCalculationMode, BlowdownConcentrationRatio, BlowdownMakeupWaterUsageScheduleName, SupplyWaterStorageTankName, OutdoorAirInletNodeName, NumberofCells, CellControl, CellMinimumWaterFlowRateFraction, CellMaximumWaterFlowRateFraction, SizingFactor,   };
  OS_CoolingTower_TwoSpeedFields()
   : EnumBase<OS_CoolingTower_TwoSpeedFields>(Handle) {} 
  OS_CoolingTower_TwoSpeedFields(const std::string &t_name) 
   : EnumBase<OS_CoolingTower_TwoSpeedFields>(t_name) {} 
  OS_CoolingTower_TwoSpeedFields(int t_value) 
   : EnumBase<OS_CoolingTower_TwoSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_CoolingTower_TwoSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_CoolingTower_TwoSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_CoolingTower_TwoSpeedFields>;
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
{ OS_CoolingTower_TwoSpeedFields::Handle, "Handle", "Handle"},
{ OS_CoolingTower_TwoSpeedFields::Name, "Name", "Name"},
{ OS_CoolingTower_TwoSpeedFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ OS_CoolingTower_TwoSpeedFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ OS_CoolingTower_TwoSpeedFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ OS_CoolingTower_TwoSpeedFields::HighFanSpeedAirFlowRate, "HighFanSpeedAirFlowRate", "High Fan Speed Air Flow Rate"},
{ OS_CoolingTower_TwoSpeedFields::HighFanSpeedFanPower, "HighFanSpeedFanPower", "High Fan Speed Fan Power"},
{ OS_CoolingTower_TwoSpeedFields::HighFanSpeedUFactorTimesAreaValue, "HighFanSpeedUFactorTimesAreaValue", "High Fan Speed U-Factor Times Area Value"},
{ OS_CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRate, "LowFanSpeedAirFlowRate", "Low Fan Speed Air Flow Rate"},
{ OS_CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, "LowFanSpeedAirFlowRateSizingFactor", "Low Fan Speed Air Flow Rate Sizing Factor"},
{ OS_CoolingTower_TwoSpeedFields::LowFanSpeedFanPower, "LowFanSpeedFanPower", "Low Fan Speed Fan Power"},
{ OS_CoolingTower_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, "LowFanSpeedFanPowerSizingFactor", "Low Fan Speed Fan Power Sizing Factor"},
{ OS_CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaValue, "LowFanSpeedUFactorTimesAreaValue", "Low Fan Speed U-Factor Times Area Value"},
{ OS_CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor, "LowFanSpeedUFactorTimesAreaSizingFactor", "Low Fan Speed U-Factor Times Area Sizing Factor"},
{ OS_CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRate, "FreeConvectionRegimeAirFlowRate", "Free Convection Regime Air Flow Rate"},
{ OS_CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRateSizingFactor, "FreeConvectionRegimeAirFlowRateSizingFactor", "Free Convection Regime Air Flow Rate Sizing Factor"},
{ OS_CoolingTower_TwoSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue, "FreeConvectionRegimeUFactorTimesAreaValue", "Free Convection Regime U-Factor Times Area Value"},
{ OS_CoolingTower_TwoSpeedFields::FreeConvectionUFactorTimesAreaValueSizingFactor, "FreeConvectionUFactorTimesAreaValueSizingFactor", "Free Convection U-Factor Times Area Value Sizing Factor"},
{ OS_CoolingTower_TwoSpeedFields::PerformanceInputMethod, "PerformanceInputMethod", "Performance Input Method"},
{ OS_CoolingTower_TwoSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio, "HeatRejectionCapacityandNominalCapacitySizingRatio", "Heat Rejection Capacity and Nominal Capacity Sizing Ratio"},
{ OS_CoolingTower_TwoSpeedFields::HighSpeedNominalCapacity, "HighSpeedNominalCapacity", "High Speed Nominal Capacity"},
{ OS_CoolingTower_TwoSpeedFields::LowSpeedNominalCapacity, "LowSpeedNominalCapacity", "Low Speed Nominal Capacity"},
{ OS_CoolingTower_TwoSpeedFields::LowSpeedNominalCapacitySizingFactor, "LowSpeedNominalCapacitySizingFactor", "Low Speed Nominal Capacity Sizing Factor"},
{ OS_CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacity, "FreeConvectionNominalCapacity", "Free Convection Nominal Capacity"},
{ OS_CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacitySizingFactor, "FreeConvectionNominalCapacitySizingFactor", "Free Convection Nominal Capacity Sizing Factor"},
{ OS_CoolingTower_TwoSpeedFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ OS_CoolingTower_TwoSpeedFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ OS_CoolingTower_TwoSpeedFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ OS_CoolingTower_TwoSpeedFields::EvaporationLossMode, "EvaporationLossMode", "Evaporation Loss Mode"},
{ OS_CoolingTower_TwoSpeedFields::EvaporationLossFactor, "EvaporationLossFactor", "Evaporation Loss Factor"},
{ OS_CoolingTower_TwoSpeedFields::DriftLossPercent, "DriftLossPercent", "Drift Loss Percent"},
{ OS_CoolingTower_TwoSpeedFields::BlowdownCalculationMode, "BlowdownCalculationMode", "Blowdown Calculation Mode"},
{ OS_CoolingTower_TwoSpeedFields::BlowdownConcentrationRatio, "BlowdownConcentrationRatio", "Blowdown Concentration Ratio"},
{ OS_CoolingTower_TwoSpeedFields::BlowdownMakeupWaterUsageScheduleName, "BlowdownMakeupWaterUsageScheduleName", "Blowdown Makeup Water Usage Schedule Name"},
{ OS_CoolingTower_TwoSpeedFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ OS_CoolingTower_TwoSpeedFields::OutdoorAirInletNodeName, "OutdoorAirInletNodeName", "Outdoor Air Inlet Node Name"},
{ OS_CoolingTower_TwoSpeedFields::NumberofCells, "NumberofCells", "Number of Cells"},
{ OS_CoolingTower_TwoSpeedFields::CellControl, "CellControl", "Cell Control"},
{ OS_CoolingTower_TwoSpeedFields::CellMinimumWaterFlowRateFraction, "CellMinimumWaterFlowRateFraction", "Cell Minimum  Water Flow Rate Fraction"},
{ OS_CoolingTower_TwoSpeedFields::CellMaximumWaterFlowRateFraction, "CellMaximumWaterFlowRateFraction", "Cell Maximum Water Flow Rate Fraction"},
{ OS_CoolingTower_TwoSpeedFields::SizingFactor, "SizingFactor", "Sizing Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_CoolingTower_TwoSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_CoolingTower_TwoSpeedFields> OptionalOS_CoolingTower_TwoSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COOLINGTOWER_TWOSPEED_FIELDENUMS_HXX
