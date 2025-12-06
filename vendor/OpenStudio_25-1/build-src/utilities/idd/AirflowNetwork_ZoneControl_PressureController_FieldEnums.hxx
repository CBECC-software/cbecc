/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_ZONECONTROL_PRESSURECONTROLLER_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_ZONECONTROL_PRESSURECONTROLLER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_ZoneControl_PressureControllerFields
 *  \brief Enumeration of AirflowNetwork:ZoneControl:PressureController's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_ZoneControl_PressureControllerFields, )
#else
class AirflowNetwork_ZoneControl_PressureControllerFields: public ::EnumBase<AirflowNetwork_ZoneControl_PressureControllerFields> {
 public: 
  enum domain 
  {
Name, ControlZoneName, ControlObjectType, ControlObjectName, PressureControlAvailabilityScheduleName, PressureSetpointScheduleName,   };
  AirflowNetwork_ZoneControl_PressureControllerFields()
   : EnumBase<AirflowNetwork_ZoneControl_PressureControllerFields>(Name) {} 
  AirflowNetwork_ZoneControl_PressureControllerFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_ZoneControl_PressureControllerFields>(t_name) {} 
  AirflowNetwork_ZoneControl_PressureControllerFields(int t_value) 
   : EnumBase<AirflowNetwork_ZoneControl_PressureControllerFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_ZoneControl_PressureControllerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_ZoneControl_PressureControllerFields>::integer_value()); }
   private:
    friend class EnumBase<AirflowNetwork_ZoneControl_PressureControllerFields>;
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
{ AirflowNetwork_ZoneControl_PressureControllerFields::Name, "Name", "Name"},
{ AirflowNetwork_ZoneControl_PressureControllerFields::ControlZoneName, "ControlZoneName", "Control Zone Name"},
{ AirflowNetwork_ZoneControl_PressureControllerFields::ControlObjectType, "ControlObjectType", "Control Object Type"},
{ AirflowNetwork_ZoneControl_PressureControllerFields::ControlObjectName, "ControlObjectName", "Control Object Name"},
{ AirflowNetwork_ZoneControl_PressureControllerFields::PressureControlAvailabilityScheduleName, "PressureControlAvailabilityScheduleName", "Pressure Control Availability Schedule Name"},
{ AirflowNetwork_ZoneControl_PressureControllerFields::PressureSetpointScheduleName, "PressureSetpointScheduleName", "Pressure Setpoint Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_ZoneControl_PressureControllerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_ZoneControl_PressureControllerFields> OptionalAirflowNetwork_ZoneControl_PressureControllerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_ZONECONTROL_PRESSURECONTROLLER_FIELDENUMS_HXX
