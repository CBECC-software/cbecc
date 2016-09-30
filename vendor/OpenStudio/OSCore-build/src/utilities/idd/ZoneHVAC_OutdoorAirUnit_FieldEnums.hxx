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

#ifndef UTILITIES_IDD_ZONEHVAC_OUTDOORAIRUNIT_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_OUTDOORAIRUNIT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_OutdoorAirUnitFields
 *  \brief Enumeration of ZoneHVAC:OutdoorAirUnit's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_OutdoorAirUnitFields, )
#else
class ZoneHVAC_OutdoorAirUnitFields: public ::EnumBase<ZoneHVAC_OutdoorAirUnitFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, OutdoorAirFlowRate, OutdoorAirScheduleName, SupplyFanName, SupplyFanPlacement, ExhaustFanName, ExhaustAirFlowRate, ExhaustAirScheduleName, UnitControlType, HighAirControlTemperatureScheduleName, LowAirControlTemperatureScheduleName, OutdoorAirNodeName, AirOutletNodeName, AirInletNodeName, SupplyFanOutletNodeName, OutdoorAirUnitListName, AvailabilityManagerListName,   };
  ZoneHVAC_OutdoorAirUnitFields()
   : EnumBase<ZoneHVAC_OutdoorAirUnitFields>(Name) {} 
  ZoneHVAC_OutdoorAirUnitFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_OutdoorAirUnitFields>(t_name) {} 
  ZoneHVAC_OutdoorAirUnitFields(int t_value) 
   : EnumBase<ZoneHVAC_OutdoorAirUnitFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_OutdoorAirUnitFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_OutdoorAirUnitFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_OutdoorAirUnitFields>;
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
{ ZoneHVAC_OutdoorAirUnitFields::Name, "Name", "Name"},
{ ZoneHVAC_OutdoorAirUnitFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_OutdoorAirUnitFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneHVAC_OutdoorAirUnitFields::OutdoorAirFlowRate, "OutdoorAirFlowRate", "Outdoor Air Flow Rate"},
{ ZoneHVAC_OutdoorAirUnitFields::OutdoorAirScheduleName, "OutdoorAirScheduleName", "Outdoor Air Schedule Name"},
{ ZoneHVAC_OutdoorAirUnitFields::SupplyFanName, "SupplyFanName", "Supply Fan Name"},
{ ZoneHVAC_OutdoorAirUnitFields::SupplyFanPlacement, "SupplyFanPlacement", "Supply Fan Placement"},
{ ZoneHVAC_OutdoorAirUnitFields::ExhaustFanName, "ExhaustFanName", "Exhaust Fan Name"},
{ ZoneHVAC_OutdoorAirUnitFields::ExhaustAirFlowRate, "ExhaustAirFlowRate", "Exhaust Air Flow Rate"},
{ ZoneHVAC_OutdoorAirUnitFields::ExhaustAirScheduleName, "ExhaustAirScheduleName", "Exhaust Air Schedule Name"},
{ ZoneHVAC_OutdoorAirUnitFields::UnitControlType, "UnitControlType", "Unit Control Type"},
{ ZoneHVAC_OutdoorAirUnitFields::HighAirControlTemperatureScheduleName, "HighAirControlTemperatureScheduleName", "High Air Control Temperature Schedule Name"},
{ ZoneHVAC_OutdoorAirUnitFields::LowAirControlTemperatureScheduleName, "LowAirControlTemperatureScheduleName", "Low Air Control Temperature Schedule Name"},
{ ZoneHVAC_OutdoorAirUnitFields::OutdoorAirNodeName, "OutdoorAirNodeName", "Outdoor Air Node Name"},
{ ZoneHVAC_OutdoorAirUnitFields::AirOutletNodeName, "AirOutletNodeName", "AirOutlet Node Name"},
{ ZoneHVAC_OutdoorAirUnitFields::AirInletNodeName, "AirInletNodeName", "AirInlet Node Name"},
{ ZoneHVAC_OutdoorAirUnitFields::SupplyFanOutletNodeName, "SupplyFanOutletNodeName", "Supply FanOutlet Node Name"},
{ ZoneHVAC_OutdoorAirUnitFields::OutdoorAirUnitListName, "OutdoorAirUnitListName", "Outdoor Air Unit List Name"},
{ ZoneHVAC_OutdoorAirUnitFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_OutdoorAirUnitFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_OutdoorAirUnitFields> OptionalZoneHVAC_OutdoorAirUnitFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_OUTDOORAIRUNIT_FIELDENUMS_HXX
