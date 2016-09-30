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

#ifndef UTILITIES_IDD_ZONEHVAC_ENERGYRECOVERYVENTILATOR_CONTROLLER_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_ENERGYRECOVERYVENTILATOR_CONTROLLER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_EnergyRecoveryVentilator_ControllerFields
 *  \brief Enumeration of ZoneHVAC:EnergyRecoveryVentilator:Controller's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_EnergyRecoveryVentilator_ControllerFields, )
#else
class ZoneHVAC_EnergyRecoveryVentilator_ControllerFields: public ::EnumBase<ZoneHVAC_EnergyRecoveryVentilator_ControllerFields> {
 public: 
  enum domain 
  {
Name, TemperatureHighLimit, TemperatureLowLimit, EnthalpyHighLimit, DewpointTemperatureLimit, ElectronicEnthalpyLimitCurveName, ExhaustAirTemperatureLimit, ExhaustAirEnthalpyLimit, TimeofDayEconomizerFlowControlScheduleName, HighHumidityControlFlag, HumidistatControlZoneName, HighHumidityOutdoorAirFlowRatio, ControlHighIndoorHumidityBasedonOutdoorHumidityRatio,   };
  ZoneHVAC_EnergyRecoveryVentilator_ControllerFields()
   : EnumBase<ZoneHVAC_EnergyRecoveryVentilator_ControllerFields>(Name) {} 
  ZoneHVAC_EnergyRecoveryVentilator_ControllerFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_EnergyRecoveryVentilator_ControllerFields>(t_name) {} 
  ZoneHVAC_EnergyRecoveryVentilator_ControllerFields(int t_value) 
   : EnumBase<ZoneHVAC_EnergyRecoveryVentilator_ControllerFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_EnergyRecoveryVentilator_ControllerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_EnergyRecoveryVentilator_ControllerFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_EnergyRecoveryVentilator_ControllerFields>;
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
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::Name, "Name", "Name"},
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TemperatureHighLimit, "TemperatureHighLimit", "Temperature High Limit"},
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TemperatureLowLimit, "TemperatureLowLimit", "Temperature Low Limit"},
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::EnthalpyHighLimit, "EnthalpyHighLimit", "Enthalpy High Limit"},
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::DewpointTemperatureLimit, "DewpointTemperatureLimit", "Dewpoint Temperature Limit"},
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ElectronicEnthalpyLimitCurveName, "ElectronicEnthalpyLimitCurveName", "Electronic Enthalpy Limit Curve Name"},
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ExhaustAirTemperatureLimit, "ExhaustAirTemperatureLimit", "Exhaust Air Temperature Limit"},
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ExhaustAirEnthalpyLimit, "ExhaustAirEnthalpyLimit", "Exhaust Air Enthalpy Limit"},
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TimeofDayEconomizerFlowControlScheduleName, "TimeofDayEconomizerFlowControlScheduleName", "Time of Day Economizer Flow Control Schedule Name"},
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::HighHumidityControlFlag, "HighHumidityControlFlag", "High Humidity Control Flag"},
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::HumidistatControlZoneName, "HumidistatControlZoneName", "Humidistat Control Zone Name"},
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::HighHumidityOutdoorAirFlowRatio, "HighHumidityOutdoorAirFlowRatio", "High Humidity Outdoor Air Flow Ratio"},
{ ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ControlHighIndoorHumidityBasedonOutdoorHumidityRatio, "ControlHighIndoorHumidityBasedonOutdoorHumidityRatio", "Control High Indoor Humidity Based on Outdoor Humidity Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_EnergyRecoveryVentilator_ControllerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_EnergyRecoveryVentilator_ControllerFields> OptionalZoneHVAC_EnergyRecoveryVentilator_ControllerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_ENERGYRECOVERYVENTILATOR_CONTROLLER_FIELDENUMS_HXX
