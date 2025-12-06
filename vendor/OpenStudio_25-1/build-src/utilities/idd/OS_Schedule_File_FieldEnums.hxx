/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SCHEDULE_FILE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SCHEDULE_FILE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Schedule_FileFields
 *  \brief Enumeration of OS:Schedule:File's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Schedule_FileFields, )
#else
class OS_Schedule_FileFields: public ::EnumBase<OS_Schedule_FileFields> {
 public: 
  enum domain 
  {
Handle, Name, ScheduleTypeLimitsName, ExternalFileName, ColumnNumber, RowstoSkipatTop, NumberofHoursofData, ColumnSeparator, InterpolatetoTimestep, MinutesperItem, AdjustScheduleforDaylightSavings, TranslateFileWithRelativePath,   };
  OS_Schedule_FileFields()
   : EnumBase<OS_Schedule_FileFields>(Handle) {} 
  OS_Schedule_FileFields(const std::string &t_name) 
   : EnumBase<OS_Schedule_FileFields>(t_name) {} 
  OS_Schedule_FileFields(int t_value) 
   : EnumBase<OS_Schedule_FileFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Schedule_FileFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Schedule_FileFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Schedule_FileFields>;
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
{ OS_Schedule_FileFields::Handle, "Handle", "Handle"},
{ OS_Schedule_FileFields::Name, "Name", "Name"},
{ OS_Schedule_FileFields::ScheduleTypeLimitsName, "ScheduleTypeLimitsName", "Schedule Type Limits Name"},
{ OS_Schedule_FileFields::ExternalFileName, "ExternalFileName", "External File Name"},
{ OS_Schedule_FileFields::ColumnNumber, "ColumnNumber", "Column Number"},
{ OS_Schedule_FileFields::RowstoSkipatTop, "RowstoSkipatTop", "Rows to Skip at Top"},
{ OS_Schedule_FileFields::NumberofHoursofData, "NumberofHoursofData", "Number of Hours of Data"},
{ OS_Schedule_FileFields::ColumnSeparator, "ColumnSeparator", "Column Separator"},
{ OS_Schedule_FileFields::InterpolatetoTimestep, "InterpolatetoTimestep", "Interpolate to Timestep"},
{ OS_Schedule_FileFields::MinutesperItem, "MinutesperItem", "Minutes per Item"},
{ OS_Schedule_FileFields::AdjustScheduleforDaylightSavings, "AdjustScheduleforDaylightSavings", "Adjust Schedule for Daylight Savings"},
{ OS_Schedule_FileFields::TranslateFileWithRelativePath, "TranslateFileWithRelativePath", "Translate File With Relative Path"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Schedule_FileFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Schedule_FileFields> OptionalOS_Schedule_FileFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SCHEDULE_FILE_FIELDENUMS_HXX
