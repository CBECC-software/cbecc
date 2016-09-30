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

#ifndef UTILITIES_IDD_OS_THERMALSTORAGE_CHILLEDWATER_STRATIFIED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_THERMALSTORAGE_CHILLEDWATER_STRATIFIED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ThermalStorage_ChilledWater_StratifiedFields
 *  \brief Enumeration of OS:ThermalStorage:ChilledWater:Stratified's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ThermalStorage_ChilledWater_StratifiedFields, )
#else
class OS_ThermalStorage_ChilledWater_StratifiedFields: public ::EnumBase<OS_ThermalStorage_ChilledWater_StratifiedFields> {
 public: 
  enum domain 
  {
Handle, Name, TankVolume, TankHeight, TankShape, TankPerimeter, SetpointTemperatureScheduleName, DeadbandTemperatureDifference, TemperatureSensorHeight, MinimumTemperatureLimit, NominalCoolingCapacity, AmbientTemperatureIndicator, AmbientTemperatureScheduleName, AmbientTemperatureThermalZoneName, AmbientTemperatureOutdoorAirNodeName, UniformSkinLossCoefficientperUnitAreatoAmbientTemperature, UseSideInletNodeName, UseSideOutletNodeName, UseSideHeatTransferEffectiveness, UseSideAvailabilityScheduleName, UseSideInletHeight, UseSideOutletHeight, UseSideDesignFlowRate, SourceSideInletNodeName, SourceSideOutletNodeName, SourceSideHeatTransferEffectiveness, SourceSideAvailabilityScheduleName, SourceSideInletHeight, SourceSideOutletHeight, SourceSideDesignFlowRate, TankRecoveryTime, InletMode, NumberofNodes, AdditionalDestratificationConductivity, Node1AdditionalLossCoefficient, Node2AdditionalLossCoefficient, Node3AdditionalLossCoefficient, Node4AdditionalLossCoefficient, Node5AdditionalLossCoefficient, Node6AdditionalLossCoefficient, Node7AdditionalLossCoefficient, Node8AdditionalLossCoefficient, Node9AdditionalLossCoefficient, Node10AdditionalLossCoefficient,   };
  OS_ThermalStorage_ChilledWater_StratifiedFields()
   : EnumBase<OS_ThermalStorage_ChilledWater_StratifiedFields>(Handle) {} 
  OS_ThermalStorage_ChilledWater_StratifiedFields(const std::string &t_name) 
   : EnumBase<OS_ThermalStorage_ChilledWater_StratifiedFields>(t_name) {} 
  OS_ThermalStorage_ChilledWater_StratifiedFields(int t_value) 
   : EnumBase<OS_ThermalStorage_ChilledWater_StratifiedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ThermalStorage_ChilledWater_StratifiedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ThermalStorage_ChilledWater_StratifiedFields>::value()); }
   private:
    friend class EnumBase<OS_ThermalStorage_ChilledWater_StratifiedFields>;
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
{ OS_ThermalStorage_ChilledWater_StratifiedFields::Handle, "Handle", "Handle"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::Name, "Name", "Name"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::TankVolume, "TankVolume", "Tank Volume"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::TankHeight, "TankHeight", "Tank Height"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::TankShape, "TankShape", "Tank Shape"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::TankPerimeter, "TankPerimeter", "Tank Perimeter"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::SetpointTemperatureScheduleName, "SetpointTemperatureScheduleName", "Setpoint Temperature Schedule Name"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::DeadbandTemperatureDifference, "DeadbandTemperatureDifference", "Deadband Temperature Difference"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::TemperatureSensorHeight, "TemperatureSensorHeight", "Temperature Sensor Height"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::MinimumTemperatureLimit, "MinimumTemperatureLimit", "Minimum Temperature Limit"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::NominalCoolingCapacity, "NominalCoolingCapacity", "Nominal Cooling Capacity"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureIndicator, "AmbientTemperatureIndicator", "Ambient Temperature Indicator"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureScheduleName, "AmbientTemperatureScheduleName", "Ambient Temperature Schedule Name"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureThermalZoneName, "AmbientTemperatureThermalZoneName", "Ambient Temperature Thermal Zone Name"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureOutdoorAirNodeName, "AmbientTemperatureOutdoorAirNodeName", "Ambient Temperature Outdoor Air Node Name"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::UniformSkinLossCoefficientperUnitAreatoAmbientTemperature, "UniformSkinLossCoefficientperUnitAreatoAmbientTemperature", "Uniform Skin Loss Coefficient per Unit Area to Ambient Temperature"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::UseSideInletNodeName, "UseSideInletNodeName", "Use Side Inlet Node Name"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::UseSideOutletNodeName, "UseSideOutletNodeName", "Use Side Outlet Node Name"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::UseSideHeatTransferEffectiveness, "UseSideHeatTransferEffectiveness", "Use Side Heat Transfer Effectiveness"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::UseSideAvailabilityScheduleName, "UseSideAvailabilityScheduleName", "Use Side Availability Schedule Name"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::UseSideInletHeight, "UseSideInletHeight", "Use Side Inlet Height"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::UseSideOutletHeight, "UseSideOutletHeight", "Use Side Outlet Height"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::UseSideDesignFlowRate, "UseSideDesignFlowRate", "Use Side Design Flow Rate"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::SourceSideHeatTransferEffectiveness, "SourceSideHeatTransferEffectiveness", "Source Side Heat Transfer Effectiveness"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::SourceSideAvailabilityScheduleName, "SourceSideAvailabilityScheduleName", "Source Side Availability Schedule Name"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::SourceSideInletHeight, "SourceSideInletHeight", "Source Side Inlet Height"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletHeight, "SourceSideOutletHeight", "Source Side Outlet Height"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::SourceSideDesignFlowRate, "SourceSideDesignFlowRate", "Source Side Design Flow Rate"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::TankRecoveryTime, "TankRecoveryTime", "Tank Recovery Time"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::InletMode, "InletMode", "Inlet Mode"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::NumberofNodes, "NumberofNodes", "Number of Nodes"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::AdditionalDestratificationConductivity, "AdditionalDestratificationConductivity", "Additional Destratification Conductivity"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::Node1AdditionalLossCoefficient, "Node1AdditionalLossCoefficient", "Node 1 Additional Loss Coefficient"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::Node2AdditionalLossCoefficient, "Node2AdditionalLossCoefficient", "Node 2 Additional Loss Coefficient"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::Node3AdditionalLossCoefficient, "Node3AdditionalLossCoefficient", "Node 3 Additional Loss Coefficient"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::Node4AdditionalLossCoefficient, "Node4AdditionalLossCoefficient", "Node 4 Additional Loss Coefficient"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::Node5AdditionalLossCoefficient, "Node5AdditionalLossCoefficient", "Node 5 Additional Loss Coefficient"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::Node6AdditionalLossCoefficient, "Node6AdditionalLossCoefficient", "Node 6 Additional Loss Coefficient"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::Node7AdditionalLossCoefficient, "Node7AdditionalLossCoefficient", "Node 7 Additional Loss Coefficient"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::Node8AdditionalLossCoefficient, "Node8AdditionalLossCoefficient", "Node 8 Additional Loss Coefficient"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::Node9AdditionalLossCoefficient, "Node9AdditionalLossCoefficient", "Node 9 Additional Loss Coefficient"},
{ OS_ThermalStorage_ChilledWater_StratifiedFields::Node10AdditionalLossCoefficient, "Node10AdditionalLossCoefficient", "Node 10 Additional Loss Coefficient"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ThermalStorage_ChilledWater_StratifiedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ThermalStorage_ChilledWater_StratifiedFields> OptionalOS_ThermalStorage_ChilledWater_StratifiedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_THERMALSTORAGE_CHILLEDWATER_STRATIFIED_FIELDENUMS_HXX
