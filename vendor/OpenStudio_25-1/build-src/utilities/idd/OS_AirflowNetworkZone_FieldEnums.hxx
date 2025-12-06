/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKZONE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKZONE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkZoneFields
 *  \brief Enumeration of OS:AirflowNetworkZone's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkZoneFields, )
#else
class OS_AirflowNetworkZoneFields: public ::EnumBase<OS_AirflowNetworkZoneFields> {
 public: 
  enum domain 
  {
Handle, Name, ThermalZoneName, VentilationControlMode, VentilationControlZoneTemperatureSetpointScheduleName, MinimumVentingOpenFactor, IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor, IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor, IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor, IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor, VentingAvailabilityScheduleName, SingleSidedWindPressureCoefficientAlgorithm, FacadeWidth, OccupantVentilationControlName,   };
  OS_AirflowNetworkZoneFields()
   : EnumBase<OS_AirflowNetworkZoneFields>(Handle) {} 
  OS_AirflowNetworkZoneFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkZoneFields>(t_name) {} 
  OS_AirflowNetworkZoneFields(int t_value) 
   : EnumBase<OS_AirflowNetworkZoneFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkZoneFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkZoneFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkZoneFields>;
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
{ OS_AirflowNetworkZoneFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkZoneFields::Name, "Name", "Name"},
{ OS_AirflowNetworkZoneFields::ThermalZoneName, "ThermalZoneName", "Thermal Zone Name"},
{ OS_AirflowNetworkZoneFields::VentilationControlMode, "VentilationControlMode", "Ventilation Control Mode"},
{ OS_AirflowNetworkZoneFields::VentilationControlZoneTemperatureSetpointScheduleName, "VentilationControlZoneTemperatureSetpointScheduleName", "Ventilation Control Zone Temperature Setpoint Schedule Name"},
{ OS_AirflowNetworkZoneFields::MinimumVentingOpenFactor, "MinimumVentingOpenFactor", "Minimum Venting Open Factor"},
{ OS_AirflowNetworkZoneFields::IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor, "IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor", "Indoor and Outdoor Temperature Difference Lower Limit For Maximum Venting Open Factor"},
{ OS_AirflowNetworkZoneFields::IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor, "IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor", "Indoor and Outdoor Temperature Difference Upper Limit for Minimum Venting Open Factor"},
{ OS_AirflowNetworkZoneFields::IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor, "IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor", "Indoor and Outdoor Enthalpy Difference Lower Limit For Maximum Venting Open Factor"},
{ OS_AirflowNetworkZoneFields::IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor, "IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor", "Indoor and Outdoor Enthalpy Difference Upper Limit for Minimum Venting Open Factor"},
{ OS_AirflowNetworkZoneFields::VentingAvailabilityScheduleName, "VentingAvailabilityScheduleName", "Venting Availability Schedule Name"},
{ OS_AirflowNetworkZoneFields::SingleSidedWindPressureCoefficientAlgorithm, "SingleSidedWindPressureCoefficientAlgorithm", "Single Sided Wind Pressure Coefficient Algorithm"},
{ OS_AirflowNetworkZoneFields::FacadeWidth, "FacadeWidth", "Facade Width"},
{ OS_AirflowNetworkZoneFields::OccupantVentilationControlName, "OccupantVentilationControlName", "Occupant Ventilation Control Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkZoneFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkZoneFields> OptionalOS_AirflowNetworkZoneFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKZONE_FIELDENUMS_HXX
