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

#ifndef UTILITIES_IDD_OS_AVAILABILITYMANAGER_HYBRIDVENTILATION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AVAILABILITYMANAGER_HYBRIDVENTILATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AvailabilityManager_HybridVentilationFields
 *  \brief Enumeration of OS:AvailabilityManager:HybridVentilation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AvailabilityManager_HybridVentilationFields, )
#else
class OS_AvailabilityManager_HybridVentilationFields: public ::EnumBase<OS_AvailabilityManager_HybridVentilationFields> {
 public: 
  enum domain 
  {
Handle, Name, ControlledZone, VentilationControlModeSchedule, UseWeatherFileRainIndicators, MaximumWindSpeed, MinimumOutdoorTemperature, MaximumOutdoorTemperature, MinimumOutdoorEnthalpy, MaximumOutdoorEnthalpy, MinimumOutdoorDewpoint, MaximumOutdoorDewpoint, MinimumOutdoorVentilationAirSchedule, OpeningFactorFunctionofWindSpeedCurve, AirflowNetworkControlTypeSchedule, SimpleAirflowControlTypeSchedule, ZoneVentilationObject,   };
  OS_AvailabilityManager_HybridVentilationFields()
   : EnumBase<OS_AvailabilityManager_HybridVentilationFields>(Handle) {} 
  OS_AvailabilityManager_HybridVentilationFields(const std::string &t_name) 
   : EnumBase<OS_AvailabilityManager_HybridVentilationFields>(t_name) {} 
  OS_AvailabilityManager_HybridVentilationFields(int t_value) 
   : EnumBase<OS_AvailabilityManager_HybridVentilationFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AvailabilityManager_HybridVentilationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AvailabilityManager_HybridVentilationFields>::value()); }
   private:
    friend class EnumBase<OS_AvailabilityManager_HybridVentilationFields>;
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
{ OS_AvailabilityManager_HybridVentilationFields::Handle, "Handle", "Handle"},
{ OS_AvailabilityManager_HybridVentilationFields::Name, "Name", "Name"},
{ OS_AvailabilityManager_HybridVentilationFields::ControlledZone, "ControlledZone", "Controlled Zone"},
{ OS_AvailabilityManager_HybridVentilationFields::VentilationControlModeSchedule, "VentilationControlModeSchedule", "Ventilation Control Mode Schedule"},
{ OS_AvailabilityManager_HybridVentilationFields::UseWeatherFileRainIndicators, "UseWeatherFileRainIndicators", "Use Weather File Rain Indicators"},
{ OS_AvailabilityManager_HybridVentilationFields::MaximumWindSpeed, "MaximumWindSpeed", "Maximum Wind Speed"},
{ OS_AvailabilityManager_HybridVentilationFields::MinimumOutdoorTemperature, "MinimumOutdoorTemperature", "Minimum Outdoor Temperature"},
{ OS_AvailabilityManager_HybridVentilationFields::MaximumOutdoorTemperature, "MaximumOutdoorTemperature", "Maximum Outdoor Temperature"},
{ OS_AvailabilityManager_HybridVentilationFields::MinimumOutdoorEnthalpy, "MinimumOutdoorEnthalpy", "Minimum Outdoor Enthalpy"},
{ OS_AvailabilityManager_HybridVentilationFields::MaximumOutdoorEnthalpy, "MaximumOutdoorEnthalpy", "Maximum Outdoor Enthalpy"},
{ OS_AvailabilityManager_HybridVentilationFields::MinimumOutdoorDewpoint, "MinimumOutdoorDewpoint", "Minimum Outdoor Dewpoint"},
{ OS_AvailabilityManager_HybridVentilationFields::MaximumOutdoorDewpoint, "MaximumOutdoorDewpoint", "Maximum Outdoor Dewpoint"},
{ OS_AvailabilityManager_HybridVentilationFields::MinimumOutdoorVentilationAirSchedule, "MinimumOutdoorVentilationAirSchedule", "Minimum Outdoor Ventilation Air Schedule"},
{ OS_AvailabilityManager_HybridVentilationFields::OpeningFactorFunctionofWindSpeedCurve, "OpeningFactorFunctionofWindSpeedCurve", "Opening Factor Function of Wind Speed Curve"},
{ OS_AvailabilityManager_HybridVentilationFields::AirflowNetworkControlTypeSchedule, "AirflowNetworkControlTypeSchedule", "AirflowNetwork Control Type Schedule"},
{ OS_AvailabilityManager_HybridVentilationFields::SimpleAirflowControlTypeSchedule, "SimpleAirflowControlTypeSchedule", "Simple Airflow Control Type Schedule"},
{ OS_AvailabilityManager_HybridVentilationFields::ZoneVentilationObject, "ZoneVentilationObject", "ZoneVentilation Object"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AvailabilityManager_HybridVentilationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AvailabilityManager_HybridVentilationFields> OptionalOS_AvailabilityManager_HybridVentilationFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AVAILABILITYMANAGER_HYBRIDVENTILATION_FIELDENUMS_HXX
