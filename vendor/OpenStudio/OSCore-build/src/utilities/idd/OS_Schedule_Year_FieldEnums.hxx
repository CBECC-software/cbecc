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

#ifndef UTILITIES_IDD_OS_SCHEDULE_YEAR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SCHEDULE_YEAR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Schedule_YearFields
 *  \brief Enumeration of OS:Schedule:Year's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Schedule_YearFields, )
#else
class OS_Schedule_YearFields: public ::EnumBase<OS_Schedule_YearFields> {
 public: 
  enum domain 
  {
Handle, Name, ScheduleTypeLimitsName,   };
  OS_Schedule_YearFields()
   : EnumBase<OS_Schedule_YearFields>(Handle) {} 
  OS_Schedule_YearFields(const std::string &t_name) 
   : EnumBase<OS_Schedule_YearFields>(t_name) {} 
  OS_Schedule_YearFields(int t_value) 
   : EnumBase<OS_Schedule_YearFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Schedule_YearFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Schedule_YearFields>::value()); }
   private:
    friend class EnumBase<OS_Schedule_YearFields>;
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
{ OS_Schedule_YearFields::Handle, "Handle", "Handle"},
{ OS_Schedule_YearFields::Name, "Name", "Name"},
{ OS_Schedule_YearFields::ScheduleTypeLimitsName, "ScheduleTypeLimitsName", "Schedule Type Limits Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Schedule_YearFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Schedule_YearFields> OptionalOS_Schedule_YearFields ;
#endif

/** \class OS_Schedule_YearExtensibleFields
 *  \brief Enumeration of OS:Schedule:Year's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Schedule_YearExtensibleFields, )
#else
class OS_Schedule_YearExtensibleFields: public ::EnumBase<OS_Schedule_YearExtensibleFields> {
 public: 
  enum domain 
  {
Month, Day, WeekScheduleUntilDate,   };
  OS_Schedule_YearExtensibleFields()
   : EnumBase<OS_Schedule_YearExtensibleFields>(Month) {} 
  OS_Schedule_YearExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Schedule_YearExtensibleFields>(t_name) {} 
  OS_Schedule_YearExtensibleFields(int t_value) 
   : EnumBase<OS_Schedule_YearExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Schedule_YearExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Schedule_YearExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_Schedule_YearExtensibleFields>;
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
{ OS_Schedule_YearExtensibleFields::Month, "Month", "Month"},
{ OS_Schedule_YearExtensibleFields::Day, "Day", "Day"},
{ OS_Schedule_YearExtensibleFields::WeekScheduleUntilDate, "WeekScheduleUntilDate", "Week Schedule Until Date"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Schedule_YearExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Schedule_YearExtensibleFields> OptionalOS_Schedule_YearExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SCHEDULE_YEAR_FIELDENUMS_HXX
