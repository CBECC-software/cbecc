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
