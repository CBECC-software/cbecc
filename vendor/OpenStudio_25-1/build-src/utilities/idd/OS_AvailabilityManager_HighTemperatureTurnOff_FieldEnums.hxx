/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AVAILABILITYMANAGER_HIGHTEMPERATURETURNOFF_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AVAILABILITYMANAGER_HIGHTEMPERATURETURNOFF_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AvailabilityManager_HighTemperatureTurnOffFields
 *  \brief Enumeration of OS:AvailabilityManager:HighTemperatureTurnOff's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AvailabilityManager_HighTemperatureTurnOffFields, )
#else
class OS_AvailabilityManager_HighTemperatureTurnOffFields: public ::EnumBase<OS_AvailabilityManager_HighTemperatureTurnOffFields> {
 public: 
  enum domain 
  {
Handle, Name, SensorNodeName, Temperature,   };
  OS_AvailabilityManager_HighTemperatureTurnOffFields()
   : EnumBase<OS_AvailabilityManager_HighTemperatureTurnOffFields>(Handle) {} 
  OS_AvailabilityManager_HighTemperatureTurnOffFields(const std::string &t_name) 
   : EnumBase<OS_AvailabilityManager_HighTemperatureTurnOffFields>(t_name) {} 
  OS_AvailabilityManager_HighTemperatureTurnOffFields(int t_value) 
   : EnumBase<OS_AvailabilityManager_HighTemperatureTurnOffFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AvailabilityManager_HighTemperatureTurnOffFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AvailabilityManager_HighTemperatureTurnOffFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AvailabilityManager_HighTemperatureTurnOffFields>;
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
{ OS_AvailabilityManager_HighTemperatureTurnOffFields::Handle, "Handle", "Handle"},
{ OS_AvailabilityManager_HighTemperatureTurnOffFields::Name, "Name", "Name"},
{ OS_AvailabilityManager_HighTemperatureTurnOffFields::SensorNodeName, "SensorNodeName", "Sensor Node Name"},
{ OS_AvailabilityManager_HighTemperatureTurnOffFields::Temperature, "Temperature", "Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AvailabilityManager_HighTemperatureTurnOffFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AvailabilityManager_HighTemperatureTurnOffFields> OptionalOS_AvailabilityManager_HighTemperatureTurnOffFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AVAILABILITYMANAGER_HIGHTEMPERATURETURNOFF_FIELDENUMS_HXX
