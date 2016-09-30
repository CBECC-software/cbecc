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

#ifndef UTILITIES_IDD_OS_AIRTERMINAL_SINGLEDUCT_VAV_HEATANDCOOL_NOREHEAT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRTERMINAL_SINGLEDUCT_VAV_HEATANDCOOL_NOREHEAT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields
 *  \brief Enumeration of OS:AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields, )
#else
class OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields: public ::EnumBase<OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilitySchedule, AirOutlet, AirInlet, MaximumAirFlowRate, ZoneMinimumAirFlowFraction,   };
  OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields()
   : EnumBase<OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields>(Handle) {} 
  OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields(const std::string &t_name) 
   : EnumBase<OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields>(t_name) {} 
  OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields(int t_value) 
   : EnumBase<OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields>::value()); }
   private:
    friend class EnumBase<OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields>;
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
{ OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::Handle, "Handle", "Handle"},
{ OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::Name, "Name", "Name"},
{ OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::AirOutlet, "AirOutlet", "Air Outlet"},
{ OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::AirInlet, "AirInlet", "Air Inlet"},
{ OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::MaximumAirFlowRate, "MaximumAirFlowRate", "Maximum Air Flow Rate"},
{ OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::ZoneMinimumAirFlowFraction, "ZoneMinimumAirFlowFraction", "Zone Minimum Air Flow Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields> OptionalOS_AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRTERMINAL_SINGLEDUCT_VAV_HEATANDCOOL_NOREHEAT_FIELDENUMS_HXX
