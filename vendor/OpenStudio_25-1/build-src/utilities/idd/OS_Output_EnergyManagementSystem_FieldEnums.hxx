/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_OUTPUT_ENERGYMANAGEMENTSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_OUTPUT_ENERGYMANAGEMENTSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Output_EnergyManagementSystemFields
 *  \brief Enumeration of OS:Output:EnergyManagementSystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Output_EnergyManagementSystemFields, )
#else
class OS_Output_EnergyManagementSystemFields: public ::EnumBase<OS_Output_EnergyManagementSystemFields> {
 public: 
  enum domain 
  {
Handle, Name, ActuatorAvailabilityDictionaryReporting, InternalVariableAvailabilityDictionaryReporting, EMSRuntimeLanguageDebugOutputLevel,   };
  OS_Output_EnergyManagementSystemFields()
   : EnumBase<OS_Output_EnergyManagementSystemFields>(Handle) {} 
  OS_Output_EnergyManagementSystemFields(const std::string &t_name) 
   : EnumBase<OS_Output_EnergyManagementSystemFields>(t_name) {} 
  OS_Output_EnergyManagementSystemFields(int t_value) 
   : EnumBase<OS_Output_EnergyManagementSystemFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Output_EnergyManagementSystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Output_EnergyManagementSystemFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Output_EnergyManagementSystemFields>;
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
{ OS_Output_EnergyManagementSystemFields::Handle, "Handle", "Handle"},
{ OS_Output_EnergyManagementSystemFields::Name, "Name", "Name"},
{ OS_Output_EnergyManagementSystemFields::ActuatorAvailabilityDictionaryReporting, "ActuatorAvailabilityDictionaryReporting", "Actuator Availability Dictionary Reporting"},
{ OS_Output_EnergyManagementSystemFields::InternalVariableAvailabilityDictionaryReporting, "InternalVariableAvailabilityDictionaryReporting", "Internal Variable Availability Dictionary Reporting"},
{ OS_Output_EnergyManagementSystemFields::EMSRuntimeLanguageDebugOutputLevel, "EMSRuntimeLanguageDebugOutputLevel", "EMS Runtime Language Debug Output Level"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Output_EnergyManagementSystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Output_EnergyManagementSystemFields> OptionalOS_Output_EnergyManagementSystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_OUTPUT_ENERGYMANAGEMENTSYSTEM_FIELDENUMS_HXX
