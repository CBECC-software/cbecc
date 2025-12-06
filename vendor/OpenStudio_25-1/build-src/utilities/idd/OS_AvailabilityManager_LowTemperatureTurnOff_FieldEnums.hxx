/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AVAILABILITYMANAGER_LOWTEMPERATURETURNOFF_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AVAILABILITYMANAGER_LOWTEMPERATURETURNOFF_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AvailabilityManager_LowTemperatureTurnOffFields
 *  \brief Enumeration of OS:AvailabilityManager:LowTemperatureTurnOff's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AvailabilityManager_LowTemperatureTurnOffFields, )
#else
class OS_AvailabilityManager_LowTemperatureTurnOffFields: public ::EnumBase<OS_AvailabilityManager_LowTemperatureTurnOffFields> {
 public: 
  enum domain 
  {
Handle, Name, SensorNodeName, Temperature, ApplicabilityScheduleName,   };
  OS_AvailabilityManager_LowTemperatureTurnOffFields()
   : EnumBase<OS_AvailabilityManager_LowTemperatureTurnOffFields>(Handle) {} 
  OS_AvailabilityManager_LowTemperatureTurnOffFields(const std::string &t_name) 
   : EnumBase<OS_AvailabilityManager_LowTemperatureTurnOffFields>(t_name) {} 
  OS_AvailabilityManager_LowTemperatureTurnOffFields(int t_value) 
   : EnumBase<OS_AvailabilityManager_LowTemperatureTurnOffFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AvailabilityManager_LowTemperatureTurnOffFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AvailabilityManager_LowTemperatureTurnOffFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AvailabilityManager_LowTemperatureTurnOffFields>;
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
{ OS_AvailabilityManager_LowTemperatureTurnOffFields::Handle, "Handle", "Handle"},
{ OS_AvailabilityManager_LowTemperatureTurnOffFields::Name, "Name", "Name"},
{ OS_AvailabilityManager_LowTemperatureTurnOffFields::SensorNodeName, "SensorNodeName", "Sensor Node Name"},
{ OS_AvailabilityManager_LowTemperatureTurnOffFields::Temperature, "Temperature", "Temperature"},
{ OS_AvailabilityManager_LowTemperatureTurnOffFields::ApplicabilityScheduleName, "ApplicabilityScheduleName", "Applicability Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AvailabilityManager_LowTemperatureTurnOffFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AvailabilityManager_LowTemperatureTurnOffFields> OptionalOS_AvailabilityManager_LowTemperatureTurnOffFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AVAILABILITYMANAGER_LOWTEMPERATURETURNOFF_FIELDENUMS_HXX
