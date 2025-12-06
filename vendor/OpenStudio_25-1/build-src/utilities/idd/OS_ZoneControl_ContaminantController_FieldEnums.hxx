/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ZONECONTROL_CONTAMINANTCONTROLLER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONECONTROL_CONTAMINANTCONTROLLER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneControl_ContaminantControllerFields
 *  \brief Enumeration of OS:ZoneControl:ContaminantController's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneControl_ContaminantControllerFields, )
#else
class OS_ZoneControl_ContaminantControllerFields: public ::EnumBase<OS_ZoneControl_ContaminantControllerFields> {
 public: 
  enum domain 
  {
Handle, Name, ControlledZoneName, CarbonDioxideControlAvailabilityScheduleName, CarbonDioxideSetpointScheduleName, MinimumCarbonDioxideConcentrationScheduleName, GenericContaminantControlAvailabilityScheduleName, GenericContaminantSetpointScheduleName,   };
  OS_ZoneControl_ContaminantControllerFields()
   : EnumBase<OS_ZoneControl_ContaminantControllerFields>(Handle) {} 
  OS_ZoneControl_ContaminantControllerFields(const std::string &t_name) 
   : EnumBase<OS_ZoneControl_ContaminantControllerFields>(t_name) {} 
  OS_ZoneControl_ContaminantControllerFields(int t_value) 
   : EnumBase<OS_ZoneControl_ContaminantControllerFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneControl_ContaminantControllerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneControl_ContaminantControllerFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneControl_ContaminantControllerFields>;
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
{ OS_ZoneControl_ContaminantControllerFields::Handle, "Handle", "Handle"},
{ OS_ZoneControl_ContaminantControllerFields::Name, "Name", "Name"},
{ OS_ZoneControl_ContaminantControllerFields::ControlledZoneName, "ControlledZoneName", "Controlled Zone Name"},
{ OS_ZoneControl_ContaminantControllerFields::CarbonDioxideControlAvailabilityScheduleName, "CarbonDioxideControlAvailabilityScheduleName", "Carbon Dioxide Control Availability Schedule Name"},
{ OS_ZoneControl_ContaminantControllerFields::CarbonDioxideSetpointScheduleName, "CarbonDioxideSetpointScheduleName", "Carbon Dioxide Setpoint Schedule Name"},
{ OS_ZoneControl_ContaminantControllerFields::MinimumCarbonDioxideConcentrationScheduleName, "MinimumCarbonDioxideConcentrationScheduleName", "Minimum Carbon Dioxide Concentration Schedule Name"},
{ OS_ZoneControl_ContaminantControllerFields::GenericContaminantControlAvailabilityScheduleName, "GenericContaminantControlAvailabilityScheduleName", "Generic Contaminant Control Availability Schedule Name"},
{ OS_ZoneControl_ContaminantControllerFields::GenericContaminantSetpointScheduleName, "GenericContaminantSetpointScheduleName", "Generic Contaminant Setpoint Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneControl_ContaminantControllerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneControl_ContaminantControllerFields> OptionalOS_ZoneControl_ContaminantControllerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONECONTROL_CONTAMINANTCONTROLLER_FIELDENUMS_HXX
