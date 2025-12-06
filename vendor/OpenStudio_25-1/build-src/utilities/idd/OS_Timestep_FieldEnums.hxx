/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_TIMESTEP_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_TIMESTEP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_TimestepFields
 *  \brief Enumeration of OS:Timestep's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_TimestepFields, )
#else
class OS_TimestepFields: public ::EnumBase<OS_TimestepFields> {
 public: 
  enum domain 
  {
Handle, NumberofTimestepsperHour,   };
  OS_TimestepFields()
   : EnumBase<OS_TimestepFields>(Handle) {} 
  OS_TimestepFields(const std::string &t_name) 
   : EnumBase<OS_TimestepFields>(t_name) {} 
  OS_TimestepFields(int t_value) 
   : EnumBase<OS_TimestepFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_TimestepFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_TimestepFields>::integer_value()); }
   private:
    friend class EnumBase<OS_TimestepFields>;
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
{ OS_TimestepFields::Handle, "Handle", "Handle"},
{ OS_TimestepFields::NumberofTimestepsperHour, "NumberofTimestepsperHour", "Number of Timesteps per Hour"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_TimestepFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_TimestepFields> OptionalOS_TimestepFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_TIMESTEP_FIELDENUMS_HXX
