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

#ifndef UTILITIES_IDD_OS_DEFAULTSCHEDULESET_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_DEFAULTSCHEDULESET_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_DefaultScheduleSetFields
 *  \brief Enumeration of OS:DefaultScheduleSet's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_DefaultScheduleSetFields, )
#else
class OS_DefaultScheduleSetFields: public ::EnumBase<OS_DefaultScheduleSetFields> {
 public: 
  enum domain 
  {
Handle, Name, HoursofOperationScheduleName, NumberofPeopleScheduleName, PeopleActivityLevelScheduleName, LightingScheduleName, ElectricEquipmentScheduleName, GasEquipmentScheduleName, HotWaterEquipmentScheduleName, InfiltrationScheduleName, SteamEquipmentScheduleName, OtherEquipmentScheduleName,   };
  OS_DefaultScheduleSetFields()
   : EnumBase<OS_DefaultScheduleSetFields>(Handle) {} 
  OS_DefaultScheduleSetFields(const std::string &t_name) 
   : EnumBase<OS_DefaultScheduleSetFields>(t_name) {} 
  OS_DefaultScheduleSetFields(int t_value) 
   : EnumBase<OS_DefaultScheduleSetFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_DefaultScheduleSetFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_DefaultScheduleSetFields>::value()); }
   private:
    friend class EnumBase<OS_DefaultScheduleSetFields>;
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
{ OS_DefaultScheduleSetFields::Handle, "Handle", "Handle"},
{ OS_DefaultScheduleSetFields::Name, "Name", "Name"},
{ OS_DefaultScheduleSetFields::HoursofOperationScheduleName, "HoursofOperationScheduleName", "Hours of Operation Schedule Name"},
{ OS_DefaultScheduleSetFields::NumberofPeopleScheduleName, "NumberofPeopleScheduleName", "Number of People Schedule Name"},
{ OS_DefaultScheduleSetFields::PeopleActivityLevelScheduleName, "PeopleActivityLevelScheduleName", "People Activity Level Schedule Name"},
{ OS_DefaultScheduleSetFields::LightingScheduleName, "LightingScheduleName", "Lighting Schedule Name"},
{ OS_DefaultScheduleSetFields::ElectricEquipmentScheduleName, "ElectricEquipmentScheduleName", "Electric Equipment Schedule Name"},
{ OS_DefaultScheduleSetFields::GasEquipmentScheduleName, "GasEquipmentScheduleName", "Gas Equipment Schedule Name"},
{ OS_DefaultScheduleSetFields::HotWaterEquipmentScheduleName, "HotWaterEquipmentScheduleName", "Hot Water Equipment Schedule Name"},
{ OS_DefaultScheduleSetFields::InfiltrationScheduleName, "InfiltrationScheduleName", "Infiltration Schedule Name"},
{ OS_DefaultScheduleSetFields::SteamEquipmentScheduleName, "SteamEquipmentScheduleName", "Steam Equipment Schedule Name"},
{ OS_DefaultScheduleSetFields::OtherEquipmentScheduleName, "OtherEquipmentScheduleName", "Other Equipment Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_DefaultScheduleSetFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_DefaultScheduleSetFields> OptionalOS_DefaultScheduleSetFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_DEFAULTSCHEDULESET_FIELDENUMS_HXX
