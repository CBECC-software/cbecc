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

#ifndef UTILITIES_IDD_OS_FLUIDCOOLER_TWOSPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_FLUIDCOOLER_TWOSPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_FluidCooler_TwoSpeedFields
 *  \brief Enumeration of OS:FluidCooler:TwoSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_FluidCooler_TwoSpeedFields, )
#else
class OS_FluidCooler_TwoSpeedFields: public ::EnumBase<OS_FluidCooler_TwoSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, WaterInletNode, WaterOutletNode, PerformanceInputMethod, HighFanSpeedUfactorTimesAreaValue, LowFanSpeedUfactorTimesAreaValue, LowFanSpeedUFactorTimesAreaSizingFactor, HighSpeedNominalCapacity, LowSpeedNominalCapacity, LowSpeedNominalCapacitySizingFactor, DesignEnteringWaterTemperature, DesignEnteringAirTemperature, DesignEnteringAirWetbulbTemperature, DesignWaterFlowRate, HighFanSpeedAirFlowRate, HighFanSpeedFanPower, LowFanSpeedAirFlowRate, LowFanSpeedAirFlowRateSizingFactor, LowFanSpeedFanPower, LowFanSpeedFanPowerSizingFactor, OutdoorAirInletNode,   };
  OS_FluidCooler_TwoSpeedFields()
   : EnumBase<OS_FluidCooler_TwoSpeedFields>(Handle) {} 
  OS_FluidCooler_TwoSpeedFields(const std::string &t_name) 
   : EnumBase<OS_FluidCooler_TwoSpeedFields>(t_name) {} 
  OS_FluidCooler_TwoSpeedFields(int t_value) 
   : EnumBase<OS_FluidCooler_TwoSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_FluidCooler_TwoSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_FluidCooler_TwoSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_FluidCooler_TwoSpeedFields>;
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
{ OS_FluidCooler_TwoSpeedFields::Handle, "Handle", "Handle"},
{ OS_FluidCooler_TwoSpeedFields::Name, "Name", "Name"},
{ OS_FluidCooler_TwoSpeedFields::WaterInletNode, "WaterInletNode", "Water Inlet Node"},
{ OS_FluidCooler_TwoSpeedFields::WaterOutletNode, "WaterOutletNode", "Water Outlet Node"},
{ OS_FluidCooler_TwoSpeedFields::PerformanceInputMethod, "PerformanceInputMethod", "Performance Input Method"},
{ OS_FluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, "HighFanSpeedUfactorTimesAreaValue", "High Fan Speed U-factor Times Area Value"},
{ OS_FluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, "LowFanSpeedUfactorTimesAreaValue", "Low Fan Speed U-factor Times Area Value"},
{ OS_FluidCooler_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor, "LowFanSpeedUFactorTimesAreaSizingFactor", "Low Fan Speed U-Factor Times Area Sizing Factor"},
{ OS_FluidCooler_TwoSpeedFields::HighSpeedNominalCapacity, "HighSpeedNominalCapacity", "High Speed Nominal Capacity"},
{ OS_FluidCooler_TwoSpeedFields::LowSpeedNominalCapacity, "LowSpeedNominalCapacity", "Low Speed Nominal Capacity"},
{ OS_FluidCooler_TwoSpeedFields::LowSpeedNominalCapacitySizingFactor, "LowSpeedNominalCapacitySizingFactor", "Low Speed Nominal Capacity Sizing Factor"},
{ OS_FluidCooler_TwoSpeedFields::DesignEnteringWaterTemperature, "DesignEnteringWaterTemperature", "Design Entering Water Temperature"},
{ OS_FluidCooler_TwoSpeedFields::DesignEnteringAirTemperature, "DesignEnteringAirTemperature", "Design Entering Air Temperature"},
{ OS_FluidCooler_TwoSpeedFields::DesignEnteringAirWetbulbTemperature, "DesignEnteringAirWetbulbTemperature", "Design Entering Air Wet-bulb Temperature"},
{ OS_FluidCooler_TwoSpeedFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ OS_FluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, "HighFanSpeedAirFlowRate", "High Fan Speed Air Flow Rate"},
{ OS_FluidCooler_TwoSpeedFields::HighFanSpeedFanPower, "HighFanSpeedFanPower", "High Fan Speed Fan Power"},
{ OS_FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, "LowFanSpeedAirFlowRate", "Low Fan Speed Air Flow Rate"},
{ OS_FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, "LowFanSpeedAirFlowRateSizingFactor", "Low Fan Speed Air Flow Rate Sizing Factor"},
{ OS_FluidCooler_TwoSpeedFields::LowFanSpeedFanPower, "LowFanSpeedFanPower", "Low Fan Speed Fan Power"},
{ OS_FluidCooler_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, "LowFanSpeedFanPowerSizingFactor", "Low Fan Speed Fan Power Sizing Factor"},
{ OS_FluidCooler_TwoSpeedFields::OutdoorAirInletNode, "OutdoorAirInletNode", "Outdoor Air Inlet Node"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_FluidCooler_TwoSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_FluidCooler_TwoSpeedFields> OptionalOS_FluidCooler_TwoSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_FLUIDCOOLER_TWOSPEED_FIELDENUMS_HXX
