/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_EXTERNAL_FILE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_EXTERNAL_FILE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_External_FileFields
 *  \brief Enumeration of OS:External:File's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_External_FileFields, )
#else
class OS_External_FileFields: public ::EnumBase<OS_External_FileFields> {
 public: 
  enum domain 
  {
Handle, Name, FileName, ColumnSeparator,   };
  OS_External_FileFields()
   : EnumBase<OS_External_FileFields>(Handle) {} 
  OS_External_FileFields(const std::string &t_name) 
   : EnumBase<OS_External_FileFields>(t_name) {} 
  OS_External_FileFields(int t_value) 
   : EnumBase<OS_External_FileFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_External_FileFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_External_FileFields>::integer_value()); }
   private:
    friend class EnumBase<OS_External_FileFields>;
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
{ OS_External_FileFields::Handle, "Handle", "Handle"},
{ OS_External_FileFields::Name, "Name", "Name"},
{ OS_External_FileFields::FileName, "FileName", "File Name"},
{ OS_External_FileFields::ColumnSeparator, "ColumnSeparator", "Column Separator"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_External_FileFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_External_FileFields> OptionalOS_External_FileFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_EXTERNAL_FILE_FIELDENUMS_HXX
