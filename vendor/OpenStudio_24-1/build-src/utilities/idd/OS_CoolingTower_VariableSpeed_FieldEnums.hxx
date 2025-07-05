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

#ifndef UTILITIES_IDD_OS_COOLINGTOWER_VARIABLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COOLINGTOWER_VARIABLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_CoolingTower_VariableSpeedFields
 *  \brief Enumeration of OS:CoolingTower:VariableSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_CoolingTower_VariableSpeedFields, )
#else
class OS_CoolingTower_VariableSpeedFields: public ::EnumBase<OS_CoolingTower_VariableSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, WaterInletNode, WaterOutletNode, ModelType, ModelCoefficient, DesignInletAirWetBulbTemperature, DesignApproachTemperature, DesignRangeTemperature, DesignWaterFlowRate, DesignAirFlowRate, DesignFanPower, FanPowerRatioFunctionofAirFlowRateRatioCurve, MinimumAirFlowRateRatio, FractionofTowerCapacityinFreeConvectionRegime, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingSchedule, EvaporationLossMode, EvaporationLossFactor, DriftLossPercent, BlowdownCalculationMode, BlowdownConcentrationRatio, BlowdownMakeupWaterUsageSchedule, SupplyWaterStorageTank, OutdoorAirInletNode, NumberofCells, CellControl, CellMinimumWaterFlowRateFraction, CellMaximumWaterFlowRateFraction, SizingFactor, EndUseSubcategory,   };
  OS_CoolingTower_VariableSpeedFields()
   : EnumBase<OS_CoolingTower_VariableSpeedFields>(Handle) {} 
  OS_CoolingTower_VariableSpeedFields(const std::string &t_name) 
   : EnumBase<OS_CoolingTower_VariableSpeedFields>(t_name) {} 
  OS_CoolingTower_VariableSpeedFields(int t_value) 
   : EnumBase<OS_CoolingTower_VariableSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_CoolingTower_VariableSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_CoolingTower_VariableSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_CoolingTower_VariableSpeedFields>;
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
{ OS_CoolingTower_VariableSpeedFields::Handle, "Handle", "Handle"},
{ OS_CoolingTower_VariableSpeedFields::Name, "Name", "Name"},
{ OS_CoolingTower_VariableSpeedFields::WaterInletNode, "WaterInletNode", "Water Inlet Node"},
{ OS_CoolingTower_VariableSpeedFields::WaterOutletNode, "WaterOutletNode", "Water Outlet Node"},
{ OS_CoolingTower_VariableSpeedFields::ModelType, "ModelType", "Model Type"},
{ OS_CoolingTower_VariableSpeedFields::ModelCoefficient, "ModelCoefficient", "Model Coefficient"},
{ OS_CoolingTower_VariableSpeedFields::DesignInletAirWetBulbTemperature, "DesignInletAirWetBulbTemperature", "Design Inlet Air Wet-Bulb Temperature"},
{ OS_CoolingTower_VariableSpeedFields::DesignApproachTemperature, "DesignApproachTemperature", "Design Approach Temperature"},
{ OS_CoolingTower_VariableSpeedFields::DesignRangeTemperature, "DesignRangeTemperature", "Design Range Temperature"},
{ OS_CoolingTower_VariableSpeedFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ OS_CoolingTower_VariableSpeedFields::DesignAirFlowRate, "DesignAirFlowRate", "Design Air Flow Rate"},
{ OS_CoolingTower_VariableSpeedFields::DesignFanPower, "DesignFanPower", "Design Fan Power"},
{ OS_CoolingTower_VariableSpeedFields::FanPowerRatioFunctionofAirFlowRateRatioCurve, "FanPowerRatioFunctionofAirFlowRateRatioCurve", "Fan Power Ratio Function of Air Flow Rate Ratio Curve"},
{ OS_CoolingTower_VariableSpeedFields::MinimumAirFlowRateRatio, "MinimumAirFlowRateRatio", "Minimum Air Flow Rate Ratio"},
{ OS_CoolingTower_VariableSpeedFields::FractionofTowerCapacityinFreeConvectionRegime, "FractionofTowerCapacityinFreeConvectionRegime", "Fraction of Tower Capacity in Free Convection Regime"},
{ OS_CoolingTower_VariableSpeedFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ OS_CoolingTower_VariableSpeedFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ OS_CoolingTower_VariableSpeedFields::BasinHeaterOperatingSchedule, "BasinHeaterOperatingSchedule", "Basin Heater Operating Schedule"},
{ OS_CoolingTower_VariableSpeedFields::EvaporationLossMode, "EvaporationLossMode", "Evaporation Loss Mode"},
{ OS_CoolingTower_VariableSpeedFields::EvaporationLossFactor, "EvaporationLossFactor", "Evaporation Loss Factor"},
{ OS_CoolingTower_VariableSpeedFields::DriftLossPercent, "DriftLossPercent", "Drift Loss Percent"},
{ OS_CoolingTower_VariableSpeedFields::BlowdownCalculationMode, "BlowdownCalculationMode", "Blowdown Calculation Mode"},
{ OS_CoolingTower_VariableSpeedFields::BlowdownConcentrationRatio, "BlowdownConcentrationRatio", "Blowdown Concentration Ratio"},
{ OS_CoolingTower_VariableSpeedFields::BlowdownMakeupWaterUsageSchedule, "BlowdownMakeupWaterUsageSchedule", "Blowdown Makeup Water Usage Schedule"},
{ OS_CoolingTower_VariableSpeedFields::SupplyWaterStorageTank, "SupplyWaterStorageTank", "Supply Water Storage Tank"},
{ OS_CoolingTower_VariableSpeedFields::OutdoorAirInletNode, "OutdoorAirInletNode", "Outdoor Air Inlet Node"},
{ OS_CoolingTower_VariableSpeedFields::NumberofCells, "NumberofCells", "Number of Cells"},
{ OS_CoolingTower_VariableSpeedFields::CellControl, "CellControl", "Cell Control"},
{ OS_CoolingTower_VariableSpeedFields::CellMinimumWaterFlowRateFraction, "CellMinimumWaterFlowRateFraction", "Cell Minimum  Water Flow Rate Fraction"},
{ OS_CoolingTower_VariableSpeedFields::CellMaximumWaterFlowRateFraction, "CellMaximumWaterFlowRateFraction", "Cell Maximum Water Flow Rate Fraction"},
{ OS_CoolingTower_VariableSpeedFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ OS_CoolingTower_VariableSpeedFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_CoolingTower_VariableSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_CoolingTower_VariableSpeedFields> OptionalOS_CoolingTower_VariableSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COOLINGTOWER_VARIABLESPEED_FIELDENUMS_HXX
