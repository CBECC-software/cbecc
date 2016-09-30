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

#ifndef UTILITIES_IDD_AVAILABILITYMANAGER_HYBRIDVENTILATION_FIELDENUMS_HXX
#define UTILITIES_IDD_AVAILABILITYMANAGER_HYBRIDVENTILATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AvailabilityManager_HybridVentilationFields
 *  \brief Enumeration of AvailabilityManager:HybridVentilation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AvailabilityManager_HybridVentilationFields, )
#else
class AvailabilityManager_HybridVentilationFields: public ::EnumBase<AvailabilityManager_HybridVentilationFields> {
 public: 
  enum domain 
  {
Name, HVACAirLoopName, ControlledZoneName, VentilationControlModeScheduleName, UseWeatherFileRainIndicators, MaximumWindSpeed, MinimumOutdoorTemperature, MaximumOutdoorTemperature, MinimumOutdoorEnthalpy, MaximumOutdoorEnthalpy, MinimumOutdoorDewpoint, MaximumOutdoorDewpoint, MinimumOutdoorVentilationAirScheduleName, OpeningFactorFunctionofWindSpeedCurveName, AirflowNetworkControlTypeScheduleName, SimpleAirflowControlTypeScheduleName, ZoneVentilationObjectName,   };
  AvailabilityManager_HybridVentilationFields()
   : EnumBase<AvailabilityManager_HybridVentilationFields>(Name) {} 
  AvailabilityManager_HybridVentilationFields(const std::string &t_name) 
   : EnumBase<AvailabilityManager_HybridVentilationFields>(t_name) {} 
  AvailabilityManager_HybridVentilationFields(int t_value) 
   : EnumBase<AvailabilityManager_HybridVentilationFields>(t_value) {} 
  static std::string enumName() 
  { return "AvailabilityManager_HybridVentilationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AvailabilityManager_HybridVentilationFields>::value()); }
   private:
    friend class EnumBase<AvailabilityManager_HybridVentilationFields>;
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
{ AvailabilityManager_HybridVentilationFields::Name, "Name", "Name"},
{ AvailabilityManager_HybridVentilationFields::HVACAirLoopName, "HVACAirLoopName", "HVAC Air Loop Name"},
{ AvailabilityManager_HybridVentilationFields::ControlledZoneName, "ControlledZoneName", "Controlled Zone Name"},
{ AvailabilityManager_HybridVentilationFields::VentilationControlModeScheduleName, "VentilationControlModeScheduleName", "Ventilation Control Mode Schedule Name"},
{ AvailabilityManager_HybridVentilationFields::UseWeatherFileRainIndicators, "UseWeatherFileRainIndicators", "Use Weather File Rain Indicators"},
{ AvailabilityManager_HybridVentilationFields::MaximumWindSpeed, "MaximumWindSpeed", "Maximum Wind Speed"},
{ AvailabilityManager_HybridVentilationFields::MinimumOutdoorTemperature, "MinimumOutdoorTemperature", "Minimum Outdoor Temperature"},
{ AvailabilityManager_HybridVentilationFields::MaximumOutdoorTemperature, "MaximumOutdoorTemperature", "Maximum Outdoor Temperature"},
{ AvailabilityManager_HybridVentilationFields::MinimumOutdoorEnthalpy, "MinimumOutdoorEnthalpy", "Minimum Outdoor Enthalpy"},
{ AvailabilityManager_HybridVentilationFields::MaximumOutdoorEnthalpy, "MaximumOutdoorEnthalpy", "Maximum Outdoor Enthalpy"},
{ AvailabilityManager_HybridVentilationFields::MinimumOutdoorDewpoint, "MinimumOutdoorDewpoint", "Minimum Outdoor Dewpoint"},
{ AvailabilityManager_HybridVentilationFields::MaximumOutdoorDewpoint, "MaximumOutdoorDewpoint", "Maximum Outdoor Dewpoint"},
{ AvailabilityManager_HybridVentilationFields::MinimumOutdoorVentilationAirScheduleName, "MinimumOutdoorVentilationAirScheduleName", "Minimum Outdoor Ventilation Air Schedule Name"},
{ AvailabilityManager_HybridVentilationFields::OpeningFactorFunctionofWindSpeedCurveName, "OpeningFactorFunctionofWindSpeedCurveName", "Opening Factor Function of Wind Speed Curve Name"},
{ AvailabilityManager_HybridVentilationFields::AirflowNetworkControlTypeScheduleName, "AirflowNetworkControlTypeScheduleName", "AirflowNetwork Control Type Schedule Name"},
{ AvailabilityManager_HybridVentilationFields::SimpleAirflowControlTypeScheduleName, "SimpleAirflowControlTypeScheduleName", "Simple Airflow Control Type Schedule Name"},
{ AvailabilityManager_HybridVentilationFields::ZoneVentilationObjectName, "ZoneVentilationObjectName", "ZoneVentilation Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AvailabilityManager_HybridVentilationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AvailabilityManager_HybridVentilationFields> OptionalAvailabilityManager_HybridVentilationFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AVAILABILITYMANAGER_HYBRIDVENTILATION_FIELDENUMS_HXX
