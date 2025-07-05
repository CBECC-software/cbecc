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

#ifndef UTILITIES_IDD_COILSYSTEM_INTEGRATEDHEATPUMP_AIRSOURCE_FIELDENUMS_HXX
#define UTILITIES_IDD_COILSYSTEM_INTEGRATEDHEATPUMP_AIRSOURCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CoilSystem_IntegratedHeatPump_AirSourceFields
 *  \brief Enumeration of CoilSystem:IntegratedHeatPump:AirSource's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CoilSystem_IntegratedHeatPump_AirSourceFields, )
#else
class CoilSystem_IntegratedHeatPump_AirSourceFields: public ::EnumBase<CoilSystem_IntegratedHeatPump_AirSourceFields> {
 public: 
  enum domain 
  {
Name, SupplyHotWaterFlowSensorNodeName, SpaceCoolingCoilName, SpaceHeatingCoilName, DedicatedWaterHeatingCoilName, SCWHCoilName, SCDWHCoolingCoilName, SCDWHWaterHeatingCoilName, SHDWHHeatingCoilName, SHDWHWaterHeatingCoilName, IndoorTemperatureLimitforSCWHMode, AmbientTemperatureLimitforSCWHMode, IndoorTemperatureaboveWhichWHhasHigherPriority, AmbientTemperatureaboveWhichWHhasHigherPriority, FlagtoIndicateLoadControlinSCWHMode, MinimumSpeedLevelforSCWHMode, MaximumWaterFlowVolumebeforeSwitchingfromSCDWHtoSCWHMode, MinimumSpeedLevelforSCDWHMode, MaximumRunningTimebeforeAllowingElectricResistanceHeatUseduringSHDWHMode, MinimumSpeedLevelforSHDWHMode,   };
  CoilSystem_IntegratedHeatPump_AirSourceFields()
   : EnumBase<CoilSystem_IntegratedHeatPump_AirSourceFields>(Name) {} 
  CoilSystem_IntegratedHeatPump_AirSourceFields(const std::string &t_name) 
   : EnumBase<CoilSystem_IntegratedHeatPump_AirSourceFields>(t_name) {} 
  CoilSystem_IntegratedHeatPump_AirSourceFields(int t_value) 
   : EnumBase<CoilSystem_IntegratedHeatPump_AirSourceFields>(t_value) {} 
  static std::string enumName() 
  { return "CoilSystem_IntegratedHeatPump_AirSourceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CoilSystem_IntegratedHeatPump_AirSourceFields>::value()); }
   private:
    friend class EnumBase<CoilSystem_IntegratedHeatPump_AirSourceFields>;
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
{ CoilSystem_IntegratedHeatPump_AirSourceFields::Name, "Name", "Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SupplyHotWaterFlowSensorNodeName, "SupplyHotWaterFlowSensorNodeName", "Supply Hot Water Flow Sensor Node Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SpaceCoolingCoilName, "SpaceCoolingCoilName", "Space Cooling Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SpaceHeatingCoilName, "SpaceHeatingCoilName", "Space Heating Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::DedicatedWaterHeatingCoilName, "DedicatedWaterHeatingCoilName", "Dedicated Water Heating Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SCWHCoilName, "SCWHCoilName", "SCWH Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SCDWHCoolingCoilName, "SCDWHCoolingCoilName", "SCDWH Cooling Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SCDWHWaterHeatingCoilName, "SCDWHWaterHeatingCoilName", "SCDWH Water Heating Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SHDWHHeatingCoilName, "SHDWHHeatingCoilName", "SHDWH Heating Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SHDWHWaterHeatingCoilName, "SHDWHWaterHeatingCoilName", "SHDWH Water Heating Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureLimitforSCWHMode, "IndoorTemperatureLimitforSCWHMode", "Indoor Temperature Limit for SCWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::AmbientTemperatureLimitforSCWHMode, "AmbientTemperatureLimitforSCWHMode", "Ambient Temperature Limit for SCWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureaboveWhichWHhasHigherPriority, "IndoorTemperatureaboveWhichWHhasHigherPriority", "Indoor Temperature above Which WH has Higher Priority"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::AmbientTemperatureaboveWhichWHhasHigherPriority, "AmbientTemperatureaboveWhichWHhasHigherPriority", "Ambient Temperature above Which WH has Higher Priority"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::FlagtoIndicateLoadControlinSCWHMode, "FlagtoIndicateLoadControlinSCWHMode", "Flag to Indicate Load Control in SCWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelforSCWHMode, "MinimumSpeedLevelforSCWHMode", "Minimum Speed Level for SCWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::MaximumWaterFlowVolumebeforeSwitchingfromSCDWHtoSCWHMode, "MaximumWaterFlowVolumebeforeSwitchingfromSCDWHtoSCWHMode", "Maximum Water Flow Volume before Switching from SCDWH to SCWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelforSCDWHMode, "MinimumSpeedLevelforSCDWHMode", "Minimum Speed Level for SCDWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::MaximumRunningTimebeforeAllowingElectricResistanceHeatUseduringSHDWHMode, "MaximumRunningTimebeforeAllowingElectricResistanceHeatUseduringSHDWHMode", "Maximum Running Time before Allowing Electric Resistance Heat Use during SHDWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelforSHDWHMode, "MinimumSpeedLevelforSHDWHMode", "Minimum Speed Level for SHDWH Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const CoilSystem_IntegratedHeatPump_AirSourceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CoilSystem_IntegratedHeatPump_AirSourceFields> OptionalCoilSystem_IntegratedHeatPump_AirSourceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COILSYSTEM_INTEGRATEDHEATPUMP_AIRSOURCE_FIELDENUMS_HXX
