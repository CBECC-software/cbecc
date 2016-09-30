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

#ifndef UTILITIES_IDD_OS_COOLINGTOWER_SINGLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COOLINGTOWER_SINGLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_CoolingTower_SingleSpeedFields
 *  \brief Enumeration of OS:CoolingTower:SingleSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_CoolingTower_SingleSpeedFields, )
#else
class OS_CoolingTower_SingleSpeedFields: public ::EnumBase<OS_CoolingTower_SingleSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, WaterInletNodeName, WaterOutletNodeName, DesignWaterFlowRate, DesignAirFlowRate, FanPoweratDesignAirFlowRate, UFactorTimesAreaValueatDesignAirFlowRate, AirFlowRateinFreeConvectionRegime, UFactorTimesAreaValueatFreeConvectionAirFlowRate, PerformanceInputMethod, NominalCapacity, FreeConvectionCapacity, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, EvaporationLossMode, EvaporationLossFactor, DriftLossPercent, BlowdownCalculationMode, BlowdownConcentrationRatio, BlowdownMakeupWaterUsageScheduleName, OutdoorAirInletNodeName, CapacityControl, NumberofCells, CellControl, CellMinimumWaterFlowRateFraction, CellMaximumWaterFlowRateFraction, SizingFactor,   };
  OS_CoolingTower_SingleSpeedFields()
   : EnumBase<OS_CoolingTower_SingleSpeedFields>(Handle) {} 
  OS_CoolingTower_SingleSpeedFields(const std::string &t_name) 
   : EnumBase<OS_CoolingTower_SingleSpeedFields>(t_name) {} 
  OS_CoolingTower_SingleSpeedFields(int t_value) 
   : EnumBase<OS_CoolingTower_SingleSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_CoolingTower_SingleSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_CoolingTower_SingleSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_CoolingTower_SingleSpeedFields>;
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
{ OS_CoolingTower_SingleSpeedFields::Handle, "Handle", "Handle"},
{ OS_CoolingTower_SingleSpeedFields::Name, "Name", "Name"},
{ OS_CoolingTower_SingleSpeedFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ OS_CoolingTower_SingleSpeedFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ OS_CoolingTower_SingleSpeedFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ OS_CoolingTower_SingleSpeedFields::DesignAirFlowRate, "DesignAirFlowRate", "Design Air Flow Rate"},
{ OS_CoolingTower_SingleSpeedFields::FanPoweratDesignAirFlowRate, "FanPoweratDesignAirFlowRate", "Fan Power at Design Air Flow Rate"},
{ OS_CoolingTower_SingleSpeedFields::UFactorTimesAreaValueatDesignAirFlowRate, "UFactorTimesAreaValueatDesignAirFlowRate", "U-Factor Times Area Value at Design Air Flow Rate"},
{ OS_CoolingTower_SingleSpeedFields::AirFlowRateinFreeConvectionRegime, "AirFlowRateinFreeConvectionRegime", "Air Flow Rate in Free Convection Regime"},
{ OS_CoolingTower_SingleSpeedFields::UFactorTimesAreaValueatFreeConvectionAirFlowRate, "UFactorTimesAreaValueatFreeConvectionAirFlowRate", "U-Factor Times Area Value at Free Convection Air Flow Rate"},
{ OS_CoolingTower_SingleSpeedFields::PerformanceInputMethod, "PerformanceInputMethod", "Performance Input Method"},
{ OS_CoolingTower_SingleSpeedFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ OS_CoolingTower_SingleSpeedFields::FreeConvectionCapacity, "FreeConvectionCapacity", "Free Convection Capacity"},
{ OS_CoolingTower_SingleSpeedFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ OS_CoolingTower_SingleSpeedFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ OS_CoolingTower_SingleSpeedFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ OS_CoolingTower_SingleSpeedFields::EvaporationLossMode, "EvaporationLossMode", "Evaporation Loss Mode"},
{ OS_CoolingTower_SingleSpeedFields::EvaporationLossFactor, "EvaporationLossFactor", "Evaporation Loss Factor"},
{ OS_CoolingTower_SingleSpeedFields::DriftLossPercent, "DriftLossPercent", "Drift Loss Percent"},
{ OS_CoolingTower_SingleSpeedFields::BlowdownCalculationMode, "BlowdownCalculationMode", "Blowdown Calculation Mode"},
{ OS_CoolingTower_SingleSpeedFields::BlowdownConcentrationRatio, "BlowdownConcentrationRatio", "Blowdown Concentration Ratio"},
{ OS_CoolingTower_SingleSpeedFields::BlowdownMakeupWaterUsageScheduleName, "BlowdownMakeupWaterUsageScheduleName", "Blowdown Makeup Water Usage Schedule Name"},
{ OS_CoolingTower_SingleSpeedFields::OutdoorAirInletNodeName, "OutdoorAirInletNodeName", "Outdoor Air Inlet Node Name"},
{ OS_CoolingTower_SingleSpeedFields::CapacityControl, "CapacityControl", "Capacity Control"},
{ OS_CoolingTower_SingleSpeedFields::NumberofCells, "NumberofCells", "Number of Cells"},
{ OS_CoolingTower_SingleSpeedFields::CellControl, "CellControl", "Cell Control"},
{ OS_CoolingTower_SingleSpeedFields::CellMinimumWaterFlowRateFraction, "CellMinimumWaterFlowRateFraction", "Cell Minimum  Water Flow Rate Fraction"},
{ OS_CoolingTower_SingleSpeedFields::CellMaximumWaterFlowRateFraction, "CellMaximumWaterFlowRateFraction", "Cell Maximum Water Flow Rate Fraction"},
{ OS_CoolingTower_SingleSpeedFields::SizingFactor, "SizingFactor", "Sizing Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_CoolingTower_SingleSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_CoolingTower_SingleSpeedFields> OptionalOS_CoolingTower_SingleSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COOLINGTOWER_SINGLESPEED_FIELDENUMS_HXX
