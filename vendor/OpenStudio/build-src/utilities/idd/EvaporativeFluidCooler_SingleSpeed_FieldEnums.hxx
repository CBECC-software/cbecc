/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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