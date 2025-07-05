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

#ifndef UTILITIES_IDD_OS_COILSYSTEM_INTEGRATEDHEATPUMP_AIRSOURCE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COILSYSTEM_INTEGRATEDHEATPUMP_AIRSOURCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_CoilSystem_IntegratedHeatPump_AirSourceFields
 *  \brief Enumeration of OS:CoilSystem:IntegratedHeatPump:AirSource's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_CoilSystem_IntegratedHeatPump_AirSourceFields, )
#else
class OS_CoilSystem_IntegratedHeatPump_AirSourceFields: public ::EnumBase<OS_CoilSystem_IntegratedHeatPump_AirSourceFields> {
 public: 
  enum domain 
  {
Handle, Name, AirInletNodeName, AirOutletNodeName, SupplyHotWaterFlowSensorNodeName, SpaceCoolingCoil, SpaceHeatingCoil, DedicatedWaterHeatingCoil, SCWHCoil, SCDWHCoolingCoil, SCDWHWaterHeatingCoil, SHDWHHeatingCoil, SHDWHWaterHeatingCoil, IndoorTemperatureLimitForSCWHMode, AmbientTemperatureLimitForSCWHMode, IndoorTemperatureAboveWhichWHHasHigherPriority, AmbientTemperatureAboveWhichWHHasHigherPriority, FlagtoIndicateLoadControlInSCWHMode, MinimumSpeedLevelForSCWHMode, MaximumWaterFlowVolumeBeforeSwitchingFromSCDWHToSCWHMode, MinimumSpeedLevelForSCDWHMode, MaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode, MinimumSpeedLevelForSHDWHMode,   };
  OS_CoilSystem_IntegratedHeatPump_AirSourceFields()
   : EnumBase<OS_CoilSystem_IntegratedHeatPump_AirSourceFields>(Handle) {} 
  OS_CoilSystem_IntegratedHeatPump_AirSourceFields(const std::string &t_name) 
   : EnumBase<OS_CoilSystem_IntegratedHeatPump_AirSourceFields>(t_name) {} 
  OS_CoilSystem_IntegratedHeatPump_AirSourceFields(int t_value) 
   : EnumBase<OS_CoilSystem_IntegratedHeatPump_AirSourceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_CoilSystem_IntegratedHeatPump_AirSourceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_CoilSystem_IntegratedHeatPump_AirSourceFields>::value()); }
   private:
    friend class EnumBase<OS_CoilSystem_IntegratedHeatPump_AirSourceFields>;
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
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::Handle, "Handle", "Handle"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::Name, "Name", "Name"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SupplyHotWaterFlowSensorNodeName, "SupplyHotWaterFlowSensorNodeName", "Supply Hot Water Flow Sensor Node Name"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SpaceCoolingCoil, "SpaceCoolingCoil", "Space Cooling Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SpaceHeatingCoil, "SpaceHeatingCoil", "Space Heating Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::DedicatedWaterHeatingCoil, "DedicatedWaterHeatingCoil", "Dedicated Water Heating Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SCWHCoil, "SCWHCoil", "SCWH Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SCDWHCoolingCoil, "SCDWHCoolingCoil", "SCDWH Cooling Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SCDWHWaterHeatingCoil, "SCDWHWaterHeatingCoil", "SCDWH Water Heating Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SHDWHHeatingCoil, "SHDWHHeatingCoil", "SHDWH Heating Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SHDWHWaterHeatingCoil, "SHDWHWaterHeatingCoil", "SHDWH Water Heating Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureLimitForSCWHMode, "IndoorTemperatureLimitForSCWHMode", "Indoor Temperature Limit For SCWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::AmbientTemperatureLimitForSCWHMode, "AmbientTemperatureLimitForSCWHMode", "Ambient Temperature Limit For SCWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureAboveWhichWHHasHigherPriority, "IndoorTemperatureAboveWhichWHHasHigherPriority", "Indoor Temperature Above Which WH Has Higher Priority"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::AmbientTemperatureAboveWhichWHHasHigherPriority, "AmbientTemperatureAboveWhichWHHasHigherPriority", "Ambient Temperature Above Which WH Has Higher Priority"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::FlagtoIndicateLoadControlInSCWHMode, "FlagtoIndicateLoadControlInSCWHMode", "Flag to Indicate Load Control In SCWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelForSCWHMode, "MinimumSpeedLevelForSCWHMode", "Minimum Speed Level For SCWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::MaximumWaterFlowVolumeBeforeSwitchingFromSCDWHToSCWHMode, "MaximumWaterFlowVolumeBeforeSwitchingFromSCDWHToSCWHMode", "Maximum Water Flow Volume Before Switching From SCDWH To SCWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelForSCDWHMode, "MinimumSpeedLevelForSCDWHMode", "Minimum Speed Level For SCDWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::MaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode, "MaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode", "Maximum Running Time Before Allowing Electric Resistance Heat Use During SHDWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelForSHDWHMode, "MinimumSpeedLevelForSHDWHMode", "Minimum Speed Level For SHDWH Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_CoilSystem_IntegratedHeatPump_AirSourceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_CoilSystem_IntegratedHeatPump_AirSourceFields> OptionalOS_CoilSystem_IntegratedHeatPump_AirSourceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COILSYSTEM_INTEGRATEDHEATPUMP_AIRSOURCE_FIELDENUMS_HXX
