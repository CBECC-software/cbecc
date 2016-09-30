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

#ifndef UTILITIES_IDD_COOLINGTOWER_VARIABLESPEED_MERKEL_FIELDENUMS_HXX
#define UTILITIES_IDD_COOLINGTOWER_VARIABLESPEED_MERKEL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CoolingTower_VariableSpeed_MerkelFields
 *  \brief Enumeration of CoolingTower:VariableSpeed:Merkel's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CoolingTower_VariableSpeed_MerkelFields, )
#else
class CoolingTower_VariableSpeed_MerkelFields: public ::EnumBase<CoolingTower_VariableSpeed_MerkelFields> {
 public: 
  enum domain 
  {
Name, WaterInletNodeName, WaterOutletNodeName, PerformanceInputMethod, HeatRejectionCapacityandNominalCapacitySizingRatio, NominalCapacity, FreeConvectionNominalCapacity, FreeConvectionNominalCapacitySizingFactor, DesignWaterFlowRate, DesignWaterFlowRateperUnitofNominalCapacity, DesignAirFlowRate, DesignAirFlowRatePerUnitofNominalCapacity, MinimumAirFlowRateRatio, DesignFanPower, DesignFanPowerPerUnitofNominalCapacity, FanPowerModifierFunctionofAirFlowRateRatioCurveName, FreeConvectionRegimeAirFlowRate, FreeConvectionRegimeAirFlowRateSizingFactor, DesignAirFlowRateUFactorTimesAreaValue, FreeConvectionRegimeUFactorTimesAreaValue, FreeConvectionUFactorTimesAreaValueSizingFactor, UFactorTimesAreaModifierFunctionofAirFlowRatioCurveName, UFactorTimesAreaModifierFunctionofWetbulbTemperatureDifferenceCurveName, UFactorTimesAreaModifierFunctionofWaterFlowRatioCurveName, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, EvaporationLossMode, EvaporationLossFactor, DriftLossPercent, BlowdownCalculationMode, BlowdownConcentrationRatio, BlowdownMakeupWaterUsageScheduleName, SupplyWaterStorageTankName, OutdoorAirInletNodeName, NumberofCells, CellControl, CellMinimumWaterFlowRateFraction, CellMaximumWaterFlowRateFraction, SizingFactor,   };
  CoolingTower_VariableSpeed_MerkelFields()
   : EnumBase<CoolingTower_VariableSpeed_MerkelFields>(Name) {} 
  CoolingTower_VariableSpeed_MerkelFields(const std::string &t_name) 
   : EnumBase<CoolingTower_VariableSpeed_MerkelFields>(t_name) {} 
  CoolingTower_VariableSpeed_MerkelFields(int t_value) 
   : EnumBase<CoolingTower_VariableSpeed_MerkelFields>(t_value) {} 
  static std::string enumName() 
  { return "CoolingTower_VariableSpeed_MerkelFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CoolingTower_VariableSpeed_MerkelFields>::value()); }
   private:
    friend class EnumBase<CoolingTower_VariableSpeed_MerkelFields>;
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
{ CoolingTower_VariableSpeed_MerkelFields::Name, "Name", "Name"},
{ CoolingTower_VariableSpeed_MerkelFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ CoolingTower_VariableSpeed_MerkelFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ CoolingTower_VariableSpeed_MerkelFields::PerformanceInputMethod, "PerformanceInputMethod", "Performance Input Method"},
{ CoolingTower_VariableSpeed_MerkelFields::HeatRejectionCapacityandNominalCapacitySizingRatio, "HeatRejectionCapacityandNominalCapacitySizingRatio", "Heat Rejection Capacity and Nominal Capacity Sizing Ratio"},
{ CoolingTower_VariableSpeed_MerkelFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ CoolingTower_VariableSpeed_MerkelFields::FreeConvectionNominalCapacity, "FreeConvectionNominalCapacity", "Free Convection Nominal Capacity"},
{ CoolingTower_VariableSpeed_MerkelFields::FreeConvectionNominalCapacitySizingFactor, "FreeConvectionNominalCapacitySizingFactor", "Free Convection Nominal Capacity Sizing Factor"},
{ CoolingTower_VariableSpeed_MerkelFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ CoolingTower_VariableSpeed_MerkelFields::DesignWaterFlowRateperUnitofNominalCapacity, "DesignWaterFlowRateperUnitofNominalCapacity", "Design Water Flow Rate per Unit of Nominal Capacity"},
{ CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRate, "DesignAirFlowRate", "Design Air Flow Rate"},
{ CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRatePerUnitofNominalCapacity, "DesignAirFlowRatePerUnitofNominalCapacity", "Design Air Flow Rate Per Unit of Nominal Capacity"},
{ CoolingTower_VariableSpeed_MerkelFields::MinimumAirFlowRateRatio, "MinimumAirFlowRateRatio", "Minimum Air Flow Rate Ratio"},
{ CoolingTower_VariableSpeed_MerkelFields::DesignFanPower, "DesignFanPower", "Design Fan Power"},
{ CoolingTower_VariableSpeed_MerkelFields::DesignFanPowerPerUnitofNominalCapacity, "DesignFanPowerPerUnitofNominalCapacity", "Design Fan Power Per Unit of Nominal Capacity"},
{ CoolingTower_VariableSpeed_MerkelFields::FanPowerModifierFunctionofAirFlowRateRatioCurveName, "FanPowerModifierFunctionofAirFlowRateRatioCurveName", "Fan Power Modifier Function of Air Flow Rate Ratio Curve Name"},
{ CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeAirFlowRate, "FreeConvectionRegimeAirFlowRate", "Free Convection Regime Air Flow Rate"},
{ CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeAirFlowRateSizingFactor, "FreeConvectionRegimeAirFlowRateSizingFactor", "Free Convection Regime Air Flow Rate Sizing Factor"},
{ CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRateUFactorTimesAreaValue, "DesignAirFlowRateUFactorTimesAreaValue", "Design Air Flow Rate U-Factor Times Area Value"},
{ CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeUFactorTimesAreaValue, "FreeConvectionRegimeUFactorTimesAreaValue", "Free Convection Regime U-Factor Times Area Value"},
{ CoolingTower_VariableSpeed_MerkelFields::FreeConvectionUFactorTimesAreaValueSizingFactor, "FreeConvectionUFactorTimesAreaValueSizingFactor", "Free Convection U-Factor Times Area Value Sizing Factor"},
{ CoolingTower_VariableSpeed_MerkelFields::UFactorTimesAreaModifierFunctionofAirFlowRatioCurveName, "UFactorTimesAreaModifierFunctionofAirFlowRatioCurveName", "U-Factor Times Area Modifier Function of Air Flow Ratio Curve Name"},
{ CoolingTower_VariableSpeed_MerkelFields::UFactorTimesAreaModifierFunctionofWetbulbTemperatureDifferenceCurveName, "UFactorTimesAreaModifierFunctionofWetbulbTemperatureDifferenceCurveName", "U-Factor Times Area Modifier Function of Wetbulb Temperature Difference Curve Name"},
{ CoolingTower_VariableSpeed_MerkelFields::UFactorTimesAreaModifierFunctionofWaterFlowRatioCurveName, "UFactorTimesAreaModifierFunctionofWaterFlowRatioCurveName", "U-Factor Times Area Modifier Function of Water Flow Ratio Curve Name"},
{ CoolingTower_VariableSpeed_MerkelFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ CoolingTower_VariableSpeed_MerkelFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ CoolingTower_VariableSpeed_MerkelFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ CoolingTower_VariableSpeed_MerkelFields::EvaporationLossMode, "EvaporationLossMode", "Evaporation Loss Mode"},
{ CoolingTower_VariableSpeed_MerkelFields::EvaporationLossFactor, "EvaporationLossFactor", "Evaporation Loss Factor"},
{ CoolingTower_VariableSpeed_MerkelFields::DriftLossPercent, "DriftLossPercent", "Drift Loss Percent"},
{ CoolingTower_VariableSpeed_MerkelFields::BlowdownCalculationMode, "BlowdownCalculationMode", "Blowdown Calculation Mode"},
{ CoolingTower_VariableSpeed_MerkelFields::BlowdownConcentrationRatio, "BlowdownConcentrationRatio", "Blowdown Concentration Ratio"},
{ CoolingTower_VariableSpeed_MerkelFields::BlowdownMakeupWaterUsageScheduleName, "BlowdownMakeupWaterUsageScheduleName", "Blowdown Makeup Water Usage Schedule Name"},
{ CoolingTower_VariableSpeed_MerkelFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ CoolingTower_VariableSpeed_MerkelFields::OutdoorAirInletNodeName, "OutdoorAirInletNodeName", "Outdoor Air Inlet Node Name"},
{ CoolingTower_VariableSpeed_MerkelFields::NumberofCells, "NumberofCells", "Number of Cells"},
{ CoolingTower_VariableSpeed_MerkelFields::CellControl, "CellControl", "Cell Control"},
{ CoolingTower_VariableSpeed_MerkelFields::CellMinimumWaterFlowRateFraction, "CellMinimumWaterFlowRateFraction", "Cell Minimum  Water Flow Rate Fraction"},
{ CoolingTower_VariableSpeed_MerkelFields::CellMaximumWaterFlowRateFraction, "CellMaximumWaterFlowRateFraction", "Cell Maximum Water Flow Rate Fraction"},
{ CoolingTower_VariableSpeed_MerkelFields::SizingFactor, "SizingFactor", "Sizing Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const CoolingTower_VariableSpeed_MerkelFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CoolingTower_VariableSpeed_MerkelFields> OptionalCoolingTower_VariableSpeed_MerkelFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COOLINGTOWER_VARIABLESPEED_MERKEL_FIELDENUMS_HXX
