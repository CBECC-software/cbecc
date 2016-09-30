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

#ifndef UTILITIES_IDD_OS_SCHEDULE_FIXEDINTERVAL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SCHEDULE_FIXEDINTERVAL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Schedule_FixedIntervalFields
 *  \brief Enumeration of OS:Schedule:FixedInterval's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Schedule_FixedIntervalFields, )
#else
class OS_Schedule_FixedIntervalFields: public ::EnumBase<OS_Schedule_FixedIntervalFields> {
 public: 
  enum domain 
  {
Handle, Name, ScheduleTypeLimitsName, InterpolatetoTimestep, IntervalLength, OutOfRangeValue, StartMonth, StartDay,   };
  OS_Schedule_FixedIntervalFields()
   : EnumBase<OS_Schedule_FixedIntervalFields>(Handle) {} 
  OS_Schedule_FixedIntervalFields(const std::string &t_name) 
   : EnumBase<OS_Schedule_FixedIntervalFields>(t_name) {} 
  OS_Schedule_FixedIntervalFields(int t_value) 
   : EnumBase<OS_Schedule_FixedIntervalFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Schedule_FixedIntervalFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Schedule_FixedIntervalFields>::value()); }
   private:
    friend class EnumBase<OS_Schedule_FixedIntervalFields>;
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
{ OS_Schedule_FixedIntervalFields::Handle, "Handle", "Handle"},
{ OS_Schedule_FixedIntervalFields::Name, "Name", "Name"},
{ OS_Schedule_FixedIntervalFields::ScheduleTypeLimitsName, "ScheduleTypeLimitsName", "Schedule Type Limits Name"},
{ OS_Schedule_FixedIntervalFields::InterpolatetoTimestep, "InterpolatetoTimestep", "Interpolate to Timestep"},
{ OS_Schedule_FixedIntervalFields::IntervalLength, "IntervalLength", "Interval Length"},
{ OS_Schedule_FixedIntervalFields::OutOfRangeValue, "OutOfRangeValue", "Out Of Range Value"},
{ OS_Schedule_FixedIntervalFields::StartMonth, "StartMonth", "Start Month"},
{ OS_Schedule_FixedIntervalFields::StartDay, "StartDay", "Start Day"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Schedule_FixedIntervalFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Schedule_FixedIntervalFields> OptionalOS_Schedule_FixedIntervalFields ;
#endif

/** \class OS_Schedule_FixedIntervalExtensibleFields
 *  \brief Enumeration of OS:Schedule:FixedInterval's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Schedule_FixedIntervalExtensibleFields, )
#else
class OS_Schedule_FixedIntervalExtensibleFields: public ::EnumBase<OS_Schedule_FixedIntervalExtensibleFields> {
 public: 
  enum domain 
  {
Value,   };
  OS_Schedule_FixedIntervalExtensibleFields()
   : EnumBase<OS_Schedule_FixedIntervalExtensibleFields>(Value) {} 
  OS_Schedule_FixedIntervalExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Schedule_FixedIntervalExtensibleFields>(t_name) {} 
  OS_Schedule_FixedIntervalExtensibleFields(int t_value) 
   : EnumBase<OS_Schedule_FixedIntervalExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Schedule_FixedIntervalExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Schedule_FixedIntervalExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_Schedule_FixedIntervalExtensibleFields>;
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
{ OS_Schedule_FixedIntervalExtensibleFields::Value, "Value", "Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Schedule_FixedIntervalExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Schedule_FixedIntervalExtensibleFields> OptionalOS_Schedule_FixedIntervalExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SCHEDULE_FIXEDINTERVAL_FIELDENUMS_HXX
