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

#ifndef UTILITIES_IDD_AIRTERMINAL_DUALDUCT_VAV_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRTERMINAL_DUALDUCT_VAV_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirTerminal_DualDuct_VAVFields
 *  \brief Enumeration of AirTerminal:DualDuct:VAV's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirTerminal_DualDuct_VAVFields, )
#else
class AirTerminal_DualDuct_VAVFields: public ::EnumBase<AirTerminal_DualDuct_VAVFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirOutletNodeName, HotAirInletNodeName, ColdAirInletNodeName, MaximumDamperAirFlowRate, ZoneMinimumAirFlowFraction, DesignSpecificationOutdoorAirObjectName,   };
  AirTerminal_DualDuct_VAVFields()
   : EnumBase<AirTerminal_DualDuct_VAVFields>(Name) {} 
  AirTerminal_DualDuct_VAVFields(const std::string &t_name) 
   : EnumBase<AirTerminal_DualDuct_VAVFields>(t_name) {} 
  AirTerminal_DualDuct_VAVFields(int t_value) 
   : EnumBase<AirTerminal_DualDuct_VAVFields>(t_value) {} 
  static std::string enumName() 
  { return "AirTerminal_DualDuct_VAVFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirTerminal_DualDuct_VAVFields>::value()); }
   private:
    friend class EnumBase<AirTerminal_DualDuct_VAVFields>;
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
{ AirTerminal_DualDuct_VAVFields::Name, "Name", "Name"},
{ AirTerminal_DualDuct_VAVFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirTerminal_DualDuct_VAVFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ AirTerminal_DualDuct_VAVFields::HotAirInletNodeName, "HotAirInletNodeName", "Hot Air Inlet Node Name"},
{ AirTerminal_DualDuct_VAVFields::ColdAirInletNodeName, "ColdAirInletNodeName", "Cold Air Inlet Node Name"},
{ AirTerminal_DualDuct_VAVFields::MaximumDamperAirFlowRate, "MaximumDamperAirFlowRate", "Maximum Damper Air Flow Rate"},
{ AirTerminal_DualDuct_VAVFields::ZoneMinimumAirFlowFraction, "ZoneMinimumAirFlowFraction", "Zone Minimum Air Flow Fraction"},
{ AirTerminal_DualDuct_VAVFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirTerminal_DualDuct_VAVFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirTerminal_DualDuct_VAVFields> OptionalAirTerminal_DualDuct_VAVFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRTERMINAL_DUALDUCT_VAV_FIELDENUMS_HXX
