/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_OUTPUT_SCHEDULES_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_OUTPUT_SCHEDULES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Output_SchedulesFields
 *  \brief Enumeration of OS:Output:Schedules's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Output_SchedulesFields, )
#else
class OS_Output_SchedulesFields: public ::EnumBase<OS_Output_SchedulesFields> {
 public: 
  enum domain 
  {
Handle, KeyField,   };
  OS_Output_SchedulesFields()
   : EnumBase<OS_Output_SchedulesFields>(Handle) {} 
  OS_Output_SchedulesFields(const std::string &t_name) 
   : EnumBase<OS_Output_SchedulesFields>(t_name) {} 
  OS_Output_SchedulesFields(int t_value) 
   : EnumBase<OS_Output_SchedulesFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Output_SchedulesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Output_SchedulesFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Output_SchedulesFields>;
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
{ OS_Output_SchedulesFields::Handle, "Handle", "Handle"},
{ OS_Output_SchedulesFields::KeyField, "KeyField", "Key Field"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Output_SchedulesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Output_SchedulesFields> OptionalOS_Output_SchedulesFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_OUTPUT_SCHEDULES_FIELDENUMS_HXX
