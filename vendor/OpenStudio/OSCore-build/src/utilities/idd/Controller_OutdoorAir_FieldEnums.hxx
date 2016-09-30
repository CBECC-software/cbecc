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

#ifndef UTILITIES_IDD_CONTROLLER_OUTDOORAIR_FIELDENUMS_HXX
#define UTILITIES_IDD_CONTROLLER_OUTDOORAIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Controller_OutdoorAirFields
 *  \brief Enumeration of Controller:OutdoorAir's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Controller_OutdoorAirFields, )
#else
class Controller_OutdoorAirFields: public ::EnumBase<Controller_OutdoorAirFields> {
 public: 
  enum domain 
  {
Name, ReliefAirOutletNodeName, ReturnAirNodeName, MixedAirNodeName, ActuatorNodeName, MinimumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate, EconomizerControlType, EconomizerControlActionType, EconomizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitEnthalpy, EconomizerMaximumLimitDewpointTemperature, ElectronicEnthalpyLimitCurveName, EconomizerMinimumLimitDryBulbTemperature, LockoutType, MinimumLimitType, MinimumOutdoorAirScheduleName, MinimumFractionofOutdoorAirScheduleName, MaximumFractionofOutdoorAirScheduleName, MechanicalVentilationControllerName, TimeofDayEconomizerControlScheduleName, HighHumidityControl, HumidistatControlZoneName, HighHumidityOutdoorAirFlowRatio, ControlHighIndoorHumidityBasedonOutdoorHumidityRatio, HeatRecoveryBypassControlType,   };
  Controller_OutdoorAirFields()
   : EnumBase<Controller_OutdoorAirFields>(Name) {} 
  Controller_OutdoorAirFields(const std::string &t_name) 
   : EnumBase<Controller_OutdoorAirFields>(t_name) {} 
  Controller_OutdoorAirFields(int t_value) 
   : EnumBase<Controller_OutdoorAirFields>(t_value) {} 
  static std::string enumName() 
  { return "Controller_OutdoorAirFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Controller_OutdoorAirFields>::value()); }
   private:
    friend class EnumBase<Controller_OutdoorAirFields>;
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
{ Controller_OutdoorAirFields::Name, "Name", "Name"},
{ Controller_OutdoorAirFields::ReliefAirOutletNodeName, "ReliefAirOutletNodeName", "Relief Air Outlet Node Name"},
{ Controller_OutdoorAirFields::ReturnAirNodeName, "ReturnAirNodeName", "Return Air Node Name"},
{ Controller_OutdoorAirFields::MixedAirNodeName, "MixedAirNodeName", "Mixed Air Node Name"},
{ Controller_OutdoorAirFields::ActuatorNodeName, "ActuatorNodeName", "Actuator Node Name"},
{ Controller_OutdoorAirFields::MinimumOutdoorAirFlowRate, "MinimumOutdoorAirFlowRate", "Minimum Outdoor Air Flow Rate"},
{ Controller_OutdoorAirFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ Controller_OutdoorAirFields::EconomizerControlType, "EconomizerControlType", "Economizer Control Type"},
{ Controller_OutdoorAirFields::EconomizerControlActionType, "EconomizerControlActionType", "Economizer Control Action Type"},
{ Controller_OutdoorAirFields::EconomizerMaximumLimitDryBulbTemperature, "EconomizerMaximumLimitDryBulbTemperature", "Economizer Maximum Limit Dry-Bulb Temperature"},
{ Controller_OutdoorAirFields::EconomizerMaximumLimitEnthalpy, "EconomizerMaximumLimitEnthalpy", "Economizer Maximum Limit Enthalpy"},
{ Controller_OutdoorAirFields::EconomizerMaximumLimitDewpointTemperature, "EconomizerMaximumLimitDewpointTemperature", "Economizer Maximum Limit Dewpoint Temperature"},
{ Controller_OutdoorAirFields::ElectronicEnthalpyLimitCurveName, "ElectronicEnthalpyLimitCurveName", "Electronic Enthalpy Limit Curve Name"},
{ Controller_OutdoorAirFields::EconomizerMinimumLimitDryBulbTemperature, "EconomizerMinimumLimitDryBulbTemperature", "Economizer Minimum Limit Dry-Bulb Temperature"},
{ Controller_OutdoorAirFields::LockoutType, "LockoutType", "Lockout Type"},
{ Controller_OutdoorAirFields::MinimumLimitType, "MinimumLimitType", "Minimum Limit Type"},
{ Controller_OutdoorAirFields::MinimumOutdoorAirScheduleName, "MinimumOutdoorAirScheduleName", "Minimum Outdoor Air Schedule Name"},
{ Controller_OutdoorAirFields::MinimumFractionofOutdoorAirScheduleName, "MinimumFractionofOutdoorAirScheduleName", "Minimum Fraction of Outdoor Air Schedule Name"},
{ Controller_OutdoorAirFields::MaximumFractionofOutdoorAirScheduleName, "MaximumFractionofOutdoorAirScheduleName", "Maximum Fraction of Outdoor Air Schedule Name"},
{ Controller_OutdoorAirFields::MechanicalVentilationControllerName, "MechanicalVentilationControllerName", "Mechanical Ventilation Controller Name"},
{ Controller_OutdoorAirFields::TimeofDayEconomizerControlScheduleName, "TimeofDayEconomizerControlScheduleName", "Time of Day Economizer Control Schedule Name"},
{ Controller_OutdoorAirFields::HighHumidityControl, "HighHumidityControl", "High Humidity Control"},
{ Controller_OutdoorAirFields::HumidistatControlZoneName, "HumidistatControlZoneName", "Humidistat Control Zone Name"},
{ Controller_OutdoorAirFields::HighHumidityOutdoorAirFlowRatio, "HighHumidityOutdoorAirFlowRatio", "High Humidity Outdoor Air Flow Ratio"},
{ Controller_OutdoorAirFields::ControlHighIndoorHumidityBasedonOutdoorHumidityRatio, "ControlHighIndoorHumidityBasedonOutdoorHumidityRatio", "Control High Indoor Humidity Based on Outdoor Humidity Ratio"},
{ Controller_OutdoorAirFields::HeatRecoveryBypassControlType, "HeatRecoveryBypassControlType", "Heat Recovery Bypass Control Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const Controller_OutdoorAirFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Controller_OutdoorAirFields> OptionalController_OutdoorAirFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CONTROLLER_OUTDOORAIR_FIELDENUMS_HXX
