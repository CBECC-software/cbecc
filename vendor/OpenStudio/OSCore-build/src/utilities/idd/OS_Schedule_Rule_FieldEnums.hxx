/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_OS_SCHEDULE_RULE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SCHEDULE_RULE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Schedule_RuleFields
 *  \brief Enumeration of OS:Schedule:Rule's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Schedule_RuleFields, )
#else
class OS_Schedule_RuleFields: public ::EnumBase<OS_Schedule_RuleFields> {
 public: 
  enum domain 
  {
Handle, Name, ScheduleRulesetName, RuleOrder, DayScheduleName, ApplySunday, ApplyMonday, ApplyTuesday, ApplyWednesday, ApplyThursday, ApplyFriday, ApplySaturday, ApplyHoliday, DateSpecificationType, StartMonth, StartDay, EndMonth, EndDay,   };
  OS_Schedule_RuleFields()
   : EnumBase<OS_Schedule_RuleFields>(Handle) {} 
  OS_Schedule_RuleFields(const std::string &t_name) 
   : EnumBase<OS_Schedule_RuleFields>(t_name) {} 
  OS_Schedule_RuleFields(int t_value) 
   : EnumBase<OS_Schedule_RuleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Schedule_RuleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Schedule_RuleFields>::value()); }
   private:
    friend class EnumBase<OS_Schedule_RuleFields>;
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
{ OS_Schedule_RuleFields::Handle, "Handle", "Handle"},
{ OS_Schedule_RuleFields::Name, "Name", "Name"},
{ OS_Schedule_RuleFields::ScheduleRulesetName, "ScheduleRulesetName", "Schedule Ruleset Name"},
{ OS_Schedule_RuleFields::RuleOrder, "RuleOrder", "Rule Order"},
{ OS_Schedule_RuleFields::DayScheduleName, "DayScheduleName", "Day Schedule Name"},
{ OS_Schedule_RuleFields::ApplySunday, "ApplySunday", "Apply Sunday"},
{ OS_Schedule_RuleFields::ApplyMonday, "ApplyMonday", "Apply Monday"},
{ OS_Schedule_RuleFields::ApplyTuesday, "ApplyTuesday", "Apply Tuesday"},
{ OS_Schedule_RuleFields::ApplyWednesday, "ApplyWednesday", "Apply Wednesday"},
{ OS_Schedule_RuleFields::ApplyThursday, "ApplyThursday", "Apply Thursday"},
{ OS_Schedule_RuleFields::ApplyFriday, "ApplyFriday", "Apply Friday"},
{ OS_Schedule_RuleFields::ApplySaturday, "ApplySaturday", "Apply Saturday"},
{ OS_Schedule_RuleFields::ApplyHoliday, "ApplyHoliday", "Apply Holiday"},
{ OS_Schedule_RuleFields::DateSpecificationType, "DateSpecificationType", "Date Specification Type"},
{ OS_Schedule_RuleFields::StartMonth, "StartMonth", "Start Month"},
{ OS_Schedule_RuleFields::StartDay, "StartDay", "Start Day"},
{ OS_Schedule_RuleFields::EndMonth, "EndMonth", "End Month"},
{ OS_Schedule_RuleFields::EndDay, "EndDay", "End Day"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Schedule_RuleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Schedule_RuleFields> OptionalOS_Schedule_RuleFields ;
#endif

/** \class OS_Schedule_RuleExtensibleFields
 *  \brief Enumeration of OS:Schedule:Rule's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Schedule_RuleExtensibleFields, )
#else
class OS_Schedule_RuleExtensibleFields: public ::EnumBase<OS_Schedule_RuleExtensibleFields> {
 public: 
  enum domain 
  {
SpecificMonth, SpecificDay,   };
  OS_Schedule_RuleExtensibleFields()
   : EnumBase<OS_Schedule_RuleExtensibleFields>(SpecificMonth) {} 
  OS_Schedule_RuleExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Schedule_RuleExtensibleFields>(t_name) {} 
  OS_Schedule_RuleExtensibleFields(int t_value) 
   : EnumBase<OS_Schedule_RuleExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Schedule_RuleExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Schedule_RuleExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_Schedule_RuleExtensibleFields>;
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
{ OS_Schedule_RuleExtensibleFields::SpecificMonth, "SpecificMonth", "Specific Month"},
{ OS_Schedule_RuleExtensibleFields::SpecificDay, "SpecificDay", "Specific Day"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Schedule_RuleExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Schedule_RuleExtensibleFields> OptionalOS_Schedule_RuleExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SCHEDULE_RULE_FIELDENUMS_HXX
