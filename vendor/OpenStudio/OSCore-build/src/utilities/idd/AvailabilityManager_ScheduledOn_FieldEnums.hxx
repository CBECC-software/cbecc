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

#ifndef UTILITIES_IDD_AVAILABILITYMANAGER_SCHEDULEDON_FIELDENUMS_HXX
#define UTILITIES_IDD_AVAILABILITYMANAGER_SCHEDULEDON_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AvailabilityManager_ScheduledOnFields
 *  \brief Enumeration of AvailabilityManager:ScheduledOn's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AvailabilityManager_ScheduledOnFields, )
#else
class AvailabilityManager_ScheduledOnFields: public ::EnumBase<AvailabilityManager_ScheduledOnFields> {
 public: 
  enum domain 
  {
Name, ScheduleName,   };
  AvailabilityManager_ScheduledOnFields()
   : EnumBase<AvailabilityManager_ScheduledOnFields>(Name) {} 
  AvailabilityManager_ScheduledOnFields(const std::string &t_name) 
   : EnumBase<AvailabilityManager_ScheduledOnFields>(t_name) {} 
  AvailabilityManager_ScheduledOnFields(int t_value) 
   : EnumBase<AvailabilityManager_ScheduledOnFields>(t_value) {} 
  static std::string enumName() 
  { return "AvailabilityManager_ScheduledOnFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AvailabilityManager_ScheduledOnFields>::value()); }
   private:
    friend class EnumBase<AvailabilityManager_ScheduledOnFields>;
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
{ AvailabilityManager_ScheduledOnFields::Name, "Name", "Name"},
{ AvailabilityManager_ScheduledOnFields::ScheduleName, "ScheduleName", "Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AvailabilityManager_ScheduledOnFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AvailabilityManager_ScheduledOnFields> OptionalAvailabilityManager_ScheduledOnFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AVAILABILITYMANAGER_SCHEDULEDON_FIELDENUMS_HXX
