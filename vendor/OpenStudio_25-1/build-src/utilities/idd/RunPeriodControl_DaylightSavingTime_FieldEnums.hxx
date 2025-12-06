/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_RUNPERIODCONTROL_DAYLIGHTSAVINGTIME_FIELDENUMS_HXX
#define UTILITIES_IDD_RUNPERIODCONTROL_DAYLIGHTSAVINGTIME_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class RunPeriodControl_DaylightSavingTimeFields
 *  \brief Enumeration of RunPeriodControl:DaylightSavingTime's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(RunPeriodControl_DaylightSavingTimeFields, )
#else
class RunPeriodControl_DaylightSavingTimeFields: public ::EnumBase<RunPeriodControl_DaylightSavingTimeFields> {
 public: 
  enum domain 
  {
StartDate, EndDate,   };
  RunPeriodControl_DaylightSavingTimeFields()
   : EnumBase<RunPeriodControl_DaylightSavingTimeFields>(StartDate) {} 
  RunPeriodControl_DaylightSavingTimeFields(const std::string &t_name) 
   : EnumBase<RunPeriodControl_DaylightSavingTimeFields>(t_name) {} 
  RunPeriodControl_DaylightSavingTimeFields(int t_value) 
   : EnumBase<RunPeriodControl_DaylightSavingTimeFields>(t_value) {} 
  static std::string enumName() 
  { return "RunPeriodControl_DaylightSavingTimeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RunPeriodControl_DaylightSavingTimeFields>::integer_value()); }
   private:
    friend class EnumBase<RunPeriodControl_DaylightSavingTimeFields>;
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
{ RunPeriodControl_DaylightSavingTimeFields::StartDate, "StartDate", "Start Date"},
{ RunPeriodControl_DaylightSavingTimeFields::EndDate, "EndDate", "End Date"},
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
  inline std::ostream &operator<<(std::ostream &os, const RunPeriodControl_DaylightSavingTimeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RunPeriodControl_DaylightSavingTimeFields> OptionalRunPeriodControl_DaylightSavingTimeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_RUNPERIODCONTROL_DAYLIGHTSAVINGTIME_FIELDENUMS_HXX
