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

#ifndef UTILITIES_IDD_FAN_ZONEEXHAUST_FIELDENUMS_HXX
#define UTILITIES_IDD_FAN_ZONEEXHAUST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Fan_ZoneExhaustFields
 *  \brief Enumeration of Fan:ZoneExhaust's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Fan_ZoneExhaustFields, )
#else
class Fan_ZoneExhaustFields: public ::EnumBase<Fan_ZoneExhaustFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, FanTotalEfficiency, PressureRise, MaximumFlowRate, AirInletNodeName, AirOutletNodeName, EndUseSubcategory, FlowFractionScheduleName, SystemAvailabilityManagerCouplingMode, MinimumZoneTemperatureLimitScheduleName, BalancedExhaustFractionScheduleName,   };
  Fan_ZoneExhaustFields()
   : EnumBase<Fan_ZoneExhaustFields>(Name) {} 
  Fan_ZoneExhaustFields(const std::string &t_name) 
   : EnumBase<Fan_ZoneExhaustFields>(t_name) {} 
  Fan_ZoneExhaustFields(int t_value) 
   : EnumBase<Fan_ZoneExhaustFields>(t_value) {} 
  static std::string enumName() 
  { return "Fan_ZoneExhaustFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Fan_ZoneExhaustFields>::value()); }
   private:
    friend class EnumBase<Fan_ZoneExhaustFields>;
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
{ Fan_ZoneExhaustFields::Name, "Name", "Name"},
{ Fan_ZoneExhaustFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Fan_ZoneExhaustFields::FanTotalEfficiency, "FanTotalEfficiency", "Fan Total Efficiency"},
{ Fan_ZoneExhaustFields::PressureRise, "PressureRise", "Pressure Rise"},
{ Fan_ZoneExhaustFields::MaximumFlowRate, "MaximumFlowRate", "Maximum Flow Rate"},
{ Fan_ZoneExhaustFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Fan_ZoneExhaustFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Fan_ZoneExhaustFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ Fan_ZoneExhaustFields::FlowFractionScheduleName, "FlowFractionScheduleName", "Flow Fraction Schedule Name"},
{ Fan_ZoneExhaustFields::SystemAvailabilityManagerCouplingMode, "SystemAvailabilityManagerCouplingMode", "System Availability Manager Coupling Mode"},
{ Fan_ZoneExhaustFields::MinimumZoneTemperatureLimitScheduleName, "MinimumZoneTemperatureLimitScheduleName", "Minimum Zone Temperature Limit Schedule Name"},
{ Fan_ZoneExhaustFields::BalancedExhaustFractionScheduleName, "BalancedExhaustFractionScheduleName", "Balanced Exhaust Fraction Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Fan_ZoneExhaustFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Fan_ZoneExhaustFields> OptionalFan_ZoneExhaustFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FAN_ZONEEXHAUST_FIELDENUMS_HXX
