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

#ifndef UTILITIES_IDD_COOLINGTOWER_SINGLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_COOLINGTOWER_SINGLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CoolingTower_SingleSpeedFields
 *  \brief Enumeration of CoolingTower:SingleSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CoolingTower_SingleSpeedFields, )
#else
class CoolingTower_SingleSpeedFields: public ::EnumBase<CoolingTower_SingleSpeedFields> {
 public: 
  enum domain 
  {
Name, WaterInletNodeName, WaterOutletNodeName, DesignWaterFlowRate, DesignAirFlowRate, DesignFanPower, DesignUFactorTimesAreaValue, FreeConvectionAirFlowRate, FreeConvectionAirFlowRateSizingFactor, FreeConvectionUFactorTimesAreaValue, FreeConvectionUFactorTimesAreaValueSizingFactor, PerformanceInputMethod, HeatRejectionCapacityandNominalCapacitySizingRatio, NominalCapacity, FreeConvectionCapacity, FreeConvectionNominalCapacitySizingFactor, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, EvaporationLossMode, EvaporationLossFactor, DriftLossPercent, BlowdownCalculationMode, BlowdownConcentrationRatio, BlowdownMakeupWaterUsageScheduleName, SupplyWaterStorageTankName, OutdoorAirInletNodeName, CapacityControl, NumberofCells, CellControl, CellMinimumWaterFlowRateFraction, CellMaximumWaterFlowRateFraction, SizingFactor,   };
  CoolingTower_SingleSpeedFields()
   : EnumBase<CoolingTower_SingleSpeedFields>(Name) {} 
  CoolingTower_SingleSpeedFields(const std::string &t_name) 
   : EnumBase<CoolingTower_SingleSpeedFields>(t_name) {} 
  CoolingTower_SingleSpeedFields(int t_value) 
   : EnumBase<CoolingTower_SingleSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "CoolingTower_SingleSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CoolingTower_SingleSpeedFields>::value()); }
   private:
    friend class EnumBase<CoolingTower_SingleSpeedFields>;
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
{ CoolingTower_SingleSpeedFields::Name, "Name", "Name"},
{ CoolingTower_SingleSpeedFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ CoolingTower_SingleSpeedFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ CoolingTower_SingleSpeedFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ CoolingTower_SingleSpeedFields::DesignAirFlowRate, "DesignAirFlowRate", "Design Air Flow Rate"},
{ CoolingTower_SingleSpeedFields::DesignFanPower, "DesignFanPower", "Design Fan Power"},
{ CoolingTower_SingleSpeedFields::DesignUFactorTimesAreaValue, "DesignUFactorTimesAreaValue", "Design U-Factor Times Area Value"},
{ CoolingTower_SingleSpeedFields::FreeConvectionAirFlowRate, "FreeConvectionAirFlowRate", "Free Convection Air Flow Rate"},
{ CoolingTower_SingleSpeedFields::FreeConvectionAirFlowRateSizingFactor, "FreeConvectionAirFlowRateSizingFactor", "Free Convection Air Flow Rate Sizing Factor"},
{ CoolingTower_SingleSpeedFields::FreeConvectionUFactorTimesAreaValue, "FreeConvectionUFactorTimesAreaValue", "Free Convection U-Factor Times Area Value"},
{ CoolingTower_SingleSpeedFields::FreeConvectionUFactorTimesAreaValueSizingFactor, "FreeConvectionUFactorTimesAreaValueSizingFactor", "Free Convection U-Factor Times Area Value Sizing Factor"},
{ CoolingTower_SingleSpeedFields::PerformanceInputMethod, "PerformanceInputMethod", "Performance Input Method"},
{ CoolingTower_SingleSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio, "HeatRejectionCapacityandNominalCapacitySizingRatio", "Heat Rejection Capacity and Nominal Capacity Sizing Ratio"},
{ CoolingTower_SingleSpeedFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ CoolingTower_SingleSpeedFields::FreeConvectionCapacity, "FreeConvectionCapacity", "Free Convection Capacity"},
{ CoolingTower_SingleSpeedFields::FreeConvectionNominalCapacitySizingFactor, "FreeConvectionNominalCapacitySizingFactor", "Free Convection Nominal Capacity Sizing Factor"},
{ CoolingTower_SingleSpeedFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ CoolingTower_SingleSpeedFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ CoolingTower_SingleSpeedFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ CoolingTower_SingleSpeedFields::EvaporationLossMode, "EvaporationLossMode", "Evaporation Loss Mode"},
{ CoolingTower_SingleSpeedFields::EvaporationLossFactor, "EvaporationLossFactor", "Evaporation Loss Factor"},
{ CoolingTower_SingleSpeedFields::DriftLossPercent, "DriftLossPercent", "Drift Loss Percent"},
{ CoolingTower_SingleSpeedFields::BlowdownCalculationMode, "BlowdownCalculationMode", "Blowdown Calculation Mode"},
{ CoolingTower_SingleSpeedFields::BlowdownConcentrationRatio, "BlowdownConcentrationRatio", "Blowdown Concentration Ratio"},
{ CoolingTower_SingleSpeedFields::BlowdownMakeupWaterUsageScheduleName, "BlowdownMakeupWaterUsageScheduleName", "Blowdown Makeup Water Usage Schedule Name"},
{ CoolingTower_SingleSpeedFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ CoolingTower_SingleSpeedFields::OutdoorAirInletNodeName, "OutdoorAirInletNodeName", "Outdoor Air Inlet Node Name"},
{ CoolingTower_SingleSpeedFields::CapacityControl, "CapacityControl", "Capacity Control"},
{ CoolingTower_SingleSpeedFields::NumberofCells, "NumberofCells", "Number of Cells"},
{ CoolingTower_SingleSpeedFields::CellControl, "CellControl", "Cell Control"},
{ CoolingTower_SingleSpeedFields::CellMinimumWaterFlowRateFraction, "CellMinimumWaterFlowRateFraction", "Cell Minimum  Water Flow Rate Fraction"},
{ CoolingTower_SingleSpeedFields::CellMaximumWaterFlowRateFraction, "CellMaximumWaterFlowRateFraction", "Cell Maximum Water Flow Rate Fraction"},
{ CoolingTower_SingleSpeedFields::SizingFactor, "SizingFactor", "Sizing Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const CoolingTower_SingleSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CoolingTower_SingleSpeedFields> OptionalCoolingTower_SingleSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COOLINGTOWER_SINGLESPEED_FIELDENUMS_HXX
