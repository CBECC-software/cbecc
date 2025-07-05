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

#ifndef UTILITIES_IDD_THERMALSTORAGE_CHILLEDWATER_MIXED_FIELDENUMS_HXX
#define UTILITIES_IDD_THERMALSTORAGE_CHILLEDWATER_MIXED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ThermalStorage_ChilledWater_MixedFields
 *  \brief Enumeration of ThermalStorage:ChilledWater:Mixed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ThermalStorage_ChilledWater_MixedFields, )
#else
class ThermalStorage_ChilledWater_MixedFields: public ::EnumBase<ThermalStorage_ChilledWater_MixedFields> {
 public: 
  enum domain 
  {
Name, TankVolume, SetpointTemperatureScheduleName, DeadbandTemperatureDifference, MinimumTemperatureLimit, NominalCoolingCapacity, AmbientTemperatureIndicator, AmbientTemperatureScheduleName, AmbientTemperatureZoneName, AmbientTemperatureOutdoorAirNodeName, HeatGainCoefficientfromAmbientTemperature, UseSideInletNodeName, UseSideOutletNodeName, UseSideHeatTransferEffectiveness, UseSideAvailabilityScheduleName, UseSideDesignFlowRate, SourceSideInletNodeName, SourceSideOutletNodeName, SourceSideHeatTransferEffectiveness, SourceSideAvailabilityScheduleName, SourceSideDesignFlowRate, TankRecoveryTime,   };
  ThermalStorage_ChilledWater_MixedFields()
   : EnumBase<ThermalStorage_ChilledWater_MixedFields>(Name) {} 
  ThermalStorage_ChilledWater_MixedFields(const std::string &t_name) 
   : EnumBase<ThermalStorage_ChilledWater_MixedFields>(t_name) {} 
  ThermalStorage_ChilledWater_MixedFields(int t_value) 
   : EnumBase<ThermalStorage_ChilledWater_MixedFields>(t_value) {} 
  static std::string enumName() 
  { return "ThermalStorage_ChilledWater_MixedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ThermalStorage_ChilledWater_MixedFields>::value()); }
   private:
    friend class EnumBase<ThermalStorage_ChilledWater_MixedFields>;
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
{ ThermalStorage_ChilledWater_MixedFields::Name, "Name", "Name"},
{ ThermalStorage_ChilledWater_MixedFields::TankVolume, "TankVolume", "Tank Volume"},
{ ThermalStorage_ChilledWater_MixedFields::SetpointTemperatureScheduleName, "SetpointTemperatureScheduleName", "Setpoint Temperature Schedule Name"},
{ ThermalStorage_ChilledWater_MixedFields::DeadbandTemperatureDifference, "DeadbandTemperatureDifference", "Deadband Temperature Difference"},
{ ThermalStorage_ChilledWater_MixedFields::MinimumTemperatureLimit, "MinimumTemperatureLimit", "Minimum Temperature Limit"},
{ ThermalStorage_ChilledWater_MixedFields::NominalCoolingCapacity, "NominalCoolingCapacity", "Nominal Cooling Capacity"},
{ ThermalStorage_ChilledWater_MixedFields::AmbientTemperatureIndicator, "AmbientTemperatureIndicator", "Ambient Temperature Indicator"},
{ ThermalStorage_ChilledWater_MixedFields::AmbientTemperatureScheduleName, "AmbientTemperatureScheduleName", "Ambient Temperature Schedule Name"},
{ ThermalStorage_ChilledWater_MixedFields::AmbientTemperatureZoneName, "AmbientTemperatureZoneName", "Ambient Temperature Zone Name"},
{ ThermalStorage_ChilledWater_MixedFields::AmbientTemperatureOutdoorAirNodeName, "AmbientTemperatureOutdoorAirNodeName", "Ambient Temperature Outdoor Air Node Name"},
{ ThermalStorage_ChilledWater_MixedFields::HeatGainCoefficientfromAmbientTemperature, "HeatGainCoefficientfromAmbientTemperature", "Heat Gain Coefficient from Ambient Temperature"},
{ ThermalStorage_ChilledWater_MixedFields::UseSideInletNodeName, "UseSideInletNodeName", "Use Side Inlet Node Name"},
{ ThermalStorage_ChilledWater_MixedFields::UseSideOutletNodeName, "UseSideOutletNodeName", "Use Side Outlet Node Name"},
{ ThermalStorage_ChilledWater_MixedFields::UseSideHeatTransferEffectiveness, "UseSideHeatTransferEffectiveness", "Use Side Heat Transfer Effectiveness"},
{ ThermalStorage_ChilledWater_MixedFields::UseSideAvailabilityScheduleName, "UseSideAvailabilityScheduleName", "Use Side Availability Schedule Name"},
{ ThermalStorage_ChilledWater_MixedFields::UseSideDesignFlowRate, "UseSideDesignFlowRate", "Use Side Design Flow Rate"},
{ ThermalStorage_ChilledWater_MixedFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ ThermalStorage_ChilledWater_MixedFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ ThermalStorage_ChilledWater_MixedFields::SourceSideHeatTransferEffectiveness, "SourceSideHeatTransferEffectiveness", "Source Side Heat Transfer Effectiveness"},
{ ThermalStorage_ChilledWater_MixedFields::SourceSideAvailabilityScheduleName, "SourceSideAvailabilityScheduleName", "Source Side Availability Schedule Name"},
{ ThermalStorage_ChilledWater_MixedFields::SourceSideDesignFlowRate, "SourceSideDesignFlowRate", "Source Side Design Flow Rate"},
{ ThermalStorage_ChilledWater_MixedFields::TankRecoveryTime, "TankRecoveryTime", "Tank Recovery Time"},
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
  inline std::ostream &operator<<(std::ostream &os, const ThermalStorage_ChilledWater_MixedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ThermalStorage_ChilledWater_MixedFields> OptionalThermalStorage_ChilledWater_MixedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_THERMALSTORAGE_CHILLEDWATER_MIXED_FIELDENUMS_HXX
