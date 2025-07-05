/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_COOLINGTOWER_TWOSPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_COOLINGTOWER_TWOSPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CoolingTower_TwoSpeedFields
 *  \brief Enumeration of CoolingTower:TwoSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CoolingTower_TwoSpeedFields, )
#else
class CoolingTower_TwoSpeedFields: public ::EnumBase<CoolingTower_TwoSpeedFields> {
 public: 
  enum domain 
  {
Name, WaterInletNodeName, WaterOutletNodeName, DesignWaterFlowRate, HighFanSpeedAirFlowRate, HighFanSpeedFanPower, HighFanSpeedUFactorTimesAreaValue, LowFanSpeedAirFlowRate, LowFanSpeedAirFlowRateSizingFactor, LowFanSpeedFanPower, LowFanSpeedFanPowerSizingFactor, LowFanSpeedUFactorTimesAreaValue, LowFanSpeedUFactorTimesAreaSizingFactor, FreeConvectionRegimeAirFlowRate, FreeConvectionRegimeAirFlowRateSizingFactor, FreeConvectionRegimeUFactorTimesAreaValue, FreeConvectionUFactorTimesAreaValueSizingFactor, PerformanceInputMethod, HeatRejectionCapacityandNominalCapacitySizingRatio, HighSpeedNominalCapacity, LowSpeedNominalCapacity, LowSpeedNominalCapacitySizingFactor, FreeConvectionNominalCapacity, FreeConvectionNominalCapacitySizingFactor, DesignInletAirDryBulbTemperature, DesignInletAirWetBulbTemperature, DesignApproachTemperature, DesignRangeTemperature, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, EvaporationLossMode, EvaporationLossFactor, DriftLossPercent, BlowdownCalculationMode, BlowdownConcentrationRatio, BlowdownMakeupWaterUsageScheduleName, SupplyWaterStorageTankName, OutdoorAirInletNodeName, NumberofCells, CellControl, CellMinimumWaterFlowRateFraction, CellMaximumWaterFlowRateFraction, SizingFactor, EndUseSubcategory,   };
  CoolingTower_TwoSpeedFields()
   : EnumBase<CoolingTower_TwoSpeedFields>(Name) {} 
  CoolingTower_TwoSpeedFields(const std::string &t_name) 
   : EnumBase<CoolingTower_TwoSpeedFields>(t_name) {} 
  CoolingTower_TwoSpeedFields(int t_value) 
   : EnumBase<CoolingTower_TwoSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "CoolingTower_TwoSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CoolingTower_TwoSpeedFields>::value()); }
   private:
    friend class EnumBase<CoolingTower_TwoSpeedFields>;
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
{ CoolingTower_TwoSpeedFields::Name, "Name", "Name"},
{ CoolingTower_TwoSpeedFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ CoolingTower_TwoSpeedFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ CoolingTower_TwoSpeedFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ CoolingTower_TwoSpeedFields::HighFanSpeedAirFlowRate, "HighFanSpeedAirFlowRate", "High Fan Speed Air Flow Rate"},
{ CoolingTower_TwoSpeedFields::HighFanSpeedFanPower, "HighFanSpeedFanPower", "High Fan Speed Fan Power"},
{ CoolingTower_TwoSpeedFields::HighFanSpeedUFactorTimesAreaValue, "HighFanSpeedUFactorTimesAreaValue", "High Fan Speed U-Factor Times Area Value"},
{ CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRate, "LowFanSpeedAirFlowRate", "Low Fan Speed Air Flow Rate"},
{ CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, "LowFanSpeedAirFlowRateSizingFactor", "Low Fan Speed Air Flow Rate Sizing Factor"},
{ CoolingTower_TwoSpeedFields::LowFanSpeedFanPower, "LowFanSpeedFanPower", "Low Fan Speed Fan Power"},
{ CoolingTower_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, "LowFanSpeedFanPowerSizingFactor", "Low Fan Speed Fan Power Sizing Factor"},
{ CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaValue, "LowFanSpeedUFactorTimesAreaValue", "Low Fan Speed U-Factor Times Area Value"},
{ CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor, "LowFanSpeedUFactorTimesAreaSizingFactor", "Low Fan Speed U-Factor Times Area Sizing Factor"},
{ CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRate, "FreeConvectionRegimeAirFlowRate", "Free Convection Regime Air Flow Rate"},
{ CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRateSizingFactor, "FreeConvectionRegimeAirFlowRateSizingFactor", "Free Convection Regime Air Flow Rate Sizing Factor"},
{ CoolingTower_TwoSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue, "FreeConvectionRegimeUFactorTimesAreaValue", "Free Convection Regime U-Factor Times Area Value"},
{ CoolingTower_TwoSpeedFields::FreeConvectionUFactorTimesAreaValueSizingFactor, "FreeConvectionUFactorTimesAreaValueSizingFactor", "Free Convection U-Factor Times Area Value Sizing Factor"},
{ CoolingTower_TwoSpeedFields::PerformanceInputMethod, "PerformanceInputMethod", "Performance Input Method"},
{ CoolingTower_TwoSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio, "HeatRejectionCapacityandNominalCapacitySizingRatio", "Heat Rejection Capacity and Nominal Capacity Sizing Ratio"},
{ CoolingTower_TwoSpeedFields::HighSpeedNominalCapacity, "HighSpeedNominalCapacity", "High Speed Nominal Capacity"},
{ CoolingTower_TwoSpeedFields::LowSpeedNominalCapacity, "LowSpeedNominalCapacity", "Low Speed Nominal Capacity"},
{ CoolingTower_TwoSpeedFields::LowSpeedNominalCapacitySizingFactor, "LowSpeedNominalCapacitySizingFactor", "Low Speed Nominal Capacity Sizing Factor"},
{ CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacity, "FreeConvectionNominalCapacity", "Free Convection Nominal Capacity"},
{ CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacitySizingFactor, "FreeConvectionNominalCapacitySizingFactor", "Free Convection Nominal Capacity Sizing Factor"},
{ CoolingTower_TwoSpeedFields::DesignInletAirDryBulbTemperature, "DesignInletAirDryBulbTemperature", "Design Inlet Air Dry-Bulb Temperature"},
{ CoolingTower_TwoSpeedFields::DesignInletAirWetBulbTemperature, "DesignInletAirWetBulbTemperature", "Design Inlet Air Wet-Bulb Temperature"},
{ CoolingTower_TwoSpeedFields::DesignApproachTemperature, "DesignApproachTemperature", "Design Approach Temperature"},
{ CoolingTower_TwoSpeedFields::DesignRangeTemperature, "DesignRangeTemperature", "Design Range Temperature"},
{ CoolingTower_TwoSpeedFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ CoolingTower_TwoSpeedFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ CoolingTower_TwoSpeedFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ CoolingTower_TwoSpeedFields::EvaporationLossMode, "EvaporationLossMode", "Evaporation Loss Mode"},
{ CoolingTower_TwoSpeedFields::EvaporationLossFactor, "EvaporationLossFactor", "Evaporation Loss Factor"},
{ CoolingTower_TwoSpeedFields::DriftLossPercent, "DriftLossPercent", "Drift Loss Percent"},
{ CoolingTower_TwoSpeedFields::BlowdownCalculationMode, "BlowdownCalculationMode", "Blowdown Calculation Mode"},
{ CoolingTower_TwoSpeedFields::BlowdownConcentrationRatio, "BlowdownConcentrationRatio", "Blowdown Concentration Ratio"},
{ CoolingTower_TwoSpeedFields::BlowdownMakeupWaterUsageScheduleName, "BlowdownMakeupWaterUsageScheduleName", "Blowdown Makeup Water Usage Schedule Name"},
{ CoolingTower_TwoSpeedFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ CoolingTower_TwoSpeedFields::OutdoorAirInletNodeName, "OutdoorAirInletNodeName", "Outdoor Air Inlet Node Name"},
{ CoolingTower_TwoSpeedFields::NumberofCells, "NumberofCells", "Number of Cells"},
{ CoolingTower_TwoSpeedFields::CellControl, "CellControl", "Cell Control"},
{ CoolingTower_TwoSpeedFields::CellMinimumWaterFlowRateFraction, "CellMinimumWaterFlowRateFraction", "Cell Minimum  Water Flow Rate Fraction"},
{ CoolingTower_TwoSpeedFields::CellMaximumWaterFlowRateFraction, "CellMaximumWaterFlowRateFraction", "Cell Maximum Water Flow Rate Fraction"},
{ CoolingTower_TwoSpeedFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ CoolingTower_TwoSpeedFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const CoolingTower_TwoSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CoolingTower_TwoSpeedFields> OptionalCoolingTower_TwoSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COOLINGTOWER_TWOSPEED_FIELDENUMS_HXX
