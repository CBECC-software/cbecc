/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SCHEDULE_FILE_SHADING_FIELDENUMS_HXX
#define UTILITIES_IDD_SCHEDULE_FILE_SHADING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Schedule_File_ShadingFields
 *  \brief Enumeration of Schedule:File:Shading's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Schedule_File_ShadingFields, )
#else
class Schedule_File_ShadingFields: public ::EnumBase<Schedule_File_ShadingFields> {
 public: 
  enum domain 
  {
FileName,   };
  Schedule_File_ShadingFields()
   : EnumBase<Schedule_File_ShadingFields>(FileName) {} 
  Schedule_File_ShadingFields(const std::string &t_name) 
   : EnumBase<Schedule_File_ShadingFields>(t_name) {} 
  Schedule_File_ShadingFields(int t_value) 
   : EnumBase<Schedule_File_ShadingFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_File_ShadingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_File_ShadingFields>::integer_value()); }
   private:
    friend class EnumBase<Schedule_File_ShadingFields>;
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
{ Schedule_File_ShadingFields::FileName, "FileName", "File Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_File_ShadingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_File_ShadingFields> OptionalSchedule_File_ShadingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SCHEDULE_FILE_SHADING_FIELDENUMS_HXX
