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

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_SURFACE_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_SURFACE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_MultiZone_SurfaceFields
 *  \brief Enumeration of AirflowNetwork:MultiZone:Surface's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_MultiZone_SurfaceFields, )
#else
class AirflowNetwork_MultiZone_SurfaceFields: public ::EnumBase<AirflowNetwork_MultiZone_SurfaceFields> {
 public: 
  enum domain 
  {
SurfaceName, LeakageComponentName, ExternalNodeName, Window_DoorOpeningFactororCrackFactor, VentilationControlMode, VentilationControlZoneTemperatureSetpointScheduleName, MinimumVentingOpenFactor, IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor, IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor, IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor, IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor, VentingAvailabilityScheduleName, OccupantVentilationControlName,   };
  AirflowNetwork_MultiZone_SurfaceFields()
   : EnumBase<AirflowNetwork_MultiZone_SurfaceFields>(SurfaceName) {} 
  AirflowNetwork_MultiZone_SurfaceFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_MultiZone_SurfaceFields>(t_name) {} 
  AirflowNetwork_MultiZone_SurfaceFields(int t_value) 
   : EnumBase<AirflowNetwork_MultiZone_SurfaceFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_MultiZone_SurfaceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_MultiZone_SurfaceFields>::value()); }
   private:
    friend class EnumBase<AirflowNetwork_MultiZone_SurfaceFields>;
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
{ AirflowNetwork_MultiZone_SurfaceFields::SurfaceName, "SurfaceName", "Surface Name"},
{ AirflowNetwork_MultiZone_SurfaceFields::LeakageComponentName, "LeakageComponentName", "Leakage Component Name"},
{ AirflowNetwork_MultiZone_SurfaceFields::ExternalNodeName, "ExternalNodeName", "External Node Name"},
{ AirflowNetwork_MultiZone_SurfaceFields::Window_DoorOpeningFactororCrackFactor, "Window_DoorOpeningFactororCrackFactor", "Window/Door Opening Factor or Crack Factor"},
{ AirflowNetwork_MultiZone_SurfaceFields::VentilationControlMode, "VentilationControlMode", "Ventilation Control Mode"},
{ AirflowNetwork_MultiZone_SurfaceFields::VentilationControlZoneTemperatureSetpointScheduleName, "VentilationControlZoneTemperatureSetpointScheduleName", "Ventilation Control Zone Temperature Setpoint Schedule Name"},
{ AirflowNetwork_MultiZone_SurfaceFields::MinimumVentingOpenFactor, "MinimumVentingOpenFactor", "Minimum Venting Open Factor"},
{ AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor, "IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor", "Indoor and Outdoor Temperature Difference Lower Limit For Maximum Venting Open Factor"},
{ AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor, "IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor", "Indoor and Outdoor Temperature Difference Upper Limit for Minimum Venting Open Factor"},
{ AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor, "IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor", "Indoor and Outdoor Enthalpy Difference Lower Limit For Maximum Venting Open Factor"},
{ AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor, "IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor", "Indoor and Outdoor Enthalpy Difference Upper Limit for Minimum Venting Open Factor"},
{ AirflowNetwork_MultiZone_SurfaceFields::VentingAvailabilityScheduleName, "VentingAvailabilityScheduleName", "Venting Availability Schedule Name"},
{ AirflowNetwork_MultiZone_SurfaceFields::OccupantVentilationControlName, "OccupantVentilationControlName", "Occupant Ventilation Control Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_MultiZone_SurfaceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_MultiZone_SurfaceFields> OptionalAirflowNetwork_MultiZone_SurfaceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_SURFACE_FIELDENUMS_HXX
