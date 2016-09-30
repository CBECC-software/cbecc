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

#ifndef UTILITIES_IDD_SCHEDULE_YEAR_FIELDENUMS_HXX
#define UTILITIES_IDD_SCHEDULE_YEAR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Schedule_YearFields
 *  \brief Enumeration of Schedule:Year's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Schedule_YearFields, )
#else
class Schedule_YearFields: public ::EnumBase<Schedule_YearFields> {
 public: 
  enum domain 
  {
Name, ScheduleTypeLimitsName,   };
  Schedule_YearFields()
   : EnumBase<Schedule_YearFields>(Name) {} 
  Schedule_YearFields(const std::string &t_name) 
   : EnumBase<Schedule_YearFields>(t_name) {} 
  Schedule_YearFields(int t_value) 
   : EnumBase<Schedule_YearFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_YearFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_YearFields>::value()); }
   private:
    friend class EnumBase<Schedule_YearFields>;
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
{ Schedule_YearFields::Name, "Name", "Name"},
{ Schedule_YearFields::ScheduleTypeLimitsName, "ScheduleTypeLimitsName", "Schedule Type Limits Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_YearFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_YearFields> OptionalSchedule_YearFields ;
#endif

/** \class Schedule_YearExtensibleFields
 *  \brief Enumeration of Schedule:Year's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Schedule_YearExtensibleFields, )
#else
class Schedule_YearExtensibleFields: public ::EnumBase<Schedule_YearExtensibleFields> {
 public: 
  enum domain 
  {
Schedule_WeekName, StartMonth, StartDay, EndMonth, EndDay,   };
  Schedule_YearExtensibleFields()
   : EnumBase<Schedule_YearExtensibleFields>(Schedule_WeekName) {} 
  Schedule_YearExtensibleFields(const std::string &t_name) 
   : EnumBase<Schedule_YearExtensibleFields>(t_name) {} 
  Schedule_YearExtensibleFields(int t_value) 
   : EnumBase<Schedule_YearExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_YearExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_YearExtensibleFields>::value()); }
   private:
    friend class EnumBase<Schedule_YearExtensibleFields>;
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
{ Schedule_YearExtensibleFields::Schedule_WeekName, "Schedule_WeekName", "Schedule:Week Name"},
{ Schedule_YearExtensibleFields::StartMonth, "StartMonth", "Start Month"},
{ Schedule_YearExtensibleFields::StartDay, "StartDay", "Start Day"},
{ Schedule_YearExtensibleFields::EndMonth, "EndMonth", "End Month"},
{ Schedule_YearExtensibleFields::EndDay, "EndDay", "End Day"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_YearExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_YearExtensibleFields> OptionalSchedule_YearExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SCHEDULE_YEAR_FIELDENUMS_HXX
