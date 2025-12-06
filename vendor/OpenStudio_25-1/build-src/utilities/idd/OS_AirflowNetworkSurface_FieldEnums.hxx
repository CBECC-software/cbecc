/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKSURFACE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKSURFACE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkSurfaceFields
 *  \brief Enumeration of OS:AirflowNetworkSurface's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkSurfaceFields, )
#else
class OS_AirflowNetworkSurfaceFields: public ::EnumBase<OS_AirflowNetworkSurfaceFields> {
 public: 
  enum domain 
  {
Handle, SurfaceName, LeakageComponentName, ExternalNodeName, Window_DoorOpeningFactororCrackFactor, VentilationControlMode, VentilationControlZoneTemperatureSetpointScheduleName, MinimumVentingOpenFactor, IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor, IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor, IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor, IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor, VentingAvailabilityScheduleName, OccupantVentilationControlName, EquivalentRectangleMethod, EquivalentRectangleAspectRatio,   };
  OS_AirflowNetworkSurfaceFields()
   : EnumBase<OS_AirflowNetworkSurfaceFields>(Handle) {} 
  OS_AirflowNetworkSurfaceFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkSurfaceFields>(t_name) {} 
  OS_AirflowNetworkSurfaceFields(int t_value) 
   : EnumBase<OS_AirflowNetworkSurfaceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkSurfaceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkSurfaceFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkSurfaceFields>;
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
{ OS_AirflowNetworkSurfaceFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkSurfaceFields::SurfaceName, "SurfaceName", "Surface Name"},
{ OS_AirflowNetworkSurfaceFields::LeakageComponentName, "LeakageComponentName", "Leakage Component Name"},
{ OS_AirflowNetworkSurfaceFields::ExternalNodeName, "ExternalNodeName", "External Node Name"},
{ OS_AirflowNetworkSurfaceFields::Window_DoorOpeningFactororCrackFactor, "Window_DoorOpeningFactororCrackFactor", "Window/Door Opening Factor or Crack Factor"},
{ OS_AirflowNetworkSurfaceFields::VentilationControlMode, "VentilationControlMode", "Ventilation Control Mode"},
{ OS_AirflowNetworkSurfaceFields::VentilationControlZoneTemperatureSetpointScheduleName, "VentilationControlZoneTemperatureSetpointScheduleName", "Ventilation Control Zone Temperature Setpoint Schedule Name"},
{ OS_AirflowNetworkSurfaceFields::MinimumVentingOpenFactor, "MinimumVentingOpenFactor", "Minimum Venting Open Factor"},
{ OS_AirflowNetworkSurfaceFields::IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor, "IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor", "Indoor and Outdoor Temperature Difference Lower Limit For Maximum Venting Open Factor"},
{ OS_AirflowNetworkSurfaceFields::IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor, "IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor", "Indoor and Outdoor Temperature Difference Upper Limit for Minimum Venting Open Factor"},
{ OS_AirflowNetworkSurfaceFields::IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor, "IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor", "Indoor and Outdoor Enthalpy Difference Lower Limit For Maximum Venting Open Factor"},
{ OS_AirflowNetworkSurfaceFields::IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor, "IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor", "Indoor and Outdoor Enthalpy Difference Upper Limit for Minimum Venting Open Factor"},
{ OS_AirflowNetworkSurfaceFields::VentingAvailabilityScheduleName, "VentingAvailabilityScheduleName", "Venting Availability Schedule Name"},
{ OS_AirflowNetworkSurfaceFields::OccupantVentilationControlName, "OccupantVentilationControlName", "Occupant Ventilation Control Name"},
{ OS_AirflowNetworkSurfaceFields::EquivalentRectangleMethod, "EquivalentRectangleMethod", "Equivalent Rectangle Method"},
{ OS_AirflowNetworkSurfaceFields::EquivalentRectangleAspectRatio, "EquivalentRectangleAspectRatio", "Equivalent Rectangle Aspect Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkSurfaceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkSurfaceFields> OptionalOS_AirflowNetworkSurfaceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKSURFACE_FIELDENUMS_HXX
