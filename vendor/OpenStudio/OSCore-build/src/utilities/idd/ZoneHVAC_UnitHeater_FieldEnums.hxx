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

#ifndef UTILITIES_IDD_ZONEHVAC_UNITHEATER_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_UNITHEATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_UnitHeaterFields
 *  \brief Enumeration of ZoneHVAC:UnitHeater's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_UnitHeaterFields, )
#else
class ZoneHVAC_UnitHeaterFields: public ::EnumBase<ZoneHVAC_UnitHeaterFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, SupplyAirFanObjectType, SupplyAirFanName, MaximumSupplyAirFlowRate, HeatingCoilObjectType, HeatingCoilName, SupplyAirFanOperatingModeScheduleName, SupplyAirFanOperationDuringNoHeating, MaximumHotWaterorSteamFlowRate, MinimumHotWaterorSteamFlowRate, HeatingConvergenceTolerance, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName,   };
  ZoneHVAC_UnitHeaterFields()
   : EnumBase<ZoneHVAC_UnitHeaterFields>(Name) {} 
  ZoneHVAC_UnitHeaterFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_UnitHeaterFields>(t_name) {} 
  ZoneHVAC_UnitHeaterFields(int t_value) 
   : EnumBase<ZoneHVAC_UnitHeaterFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_UnitHeaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_UnitHeaterFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_UnitHeaterFields>;
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
{ ZoneHVAC_UnitHeaterFields::Name, "Name", "Name"},
{ ZoneHVAC_UnitHeaterFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_UnitHeaterFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ ZoneHVAC_UnitHeaterFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ ZoneHVAC_UnitHeaterFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ ZoneHVAC_UnitHeaterFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ ZoneHVAC_UnitHeaterFields::MaximumSupplyAirFlowRate, "MaximumSupplyAirFlowRate", "Maximum Supply Air Flow Rate"},
{ ZoneHVAC_UnitHeaterFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ ZoneHVAC_UnitHeaterFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ ZoneHVAC_UnitHeaterFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ ZoneHVAC_UnitHeaterFields::SupplyAirFanOperationDuringNoHeating, "SupplyAirFanOperationDuringNoHeating", "Supply Air Fan Operation During No Heating"},
{ ZoneHVAC_UnitHeaterFields::MaximumHotWaterorSteamFlowRate, "MaximumHotWaterorSteamFlowRate", "Maximum Hot Water or Steam Flow Rate"},
{ ZoneHVAC_UnitHeaterFields::MinimumHotWaterorSteamFlowRate, "MinimumHotWaterorSteamFlowRate", "Minimum Hot Water or Steam Flow Rate"},
{ ZoneHVAC_UnitHeaterFields::HeatingConvergenceTolerance, "HeatingConvergenceTolerance", "Heating Convergence Tolerance"},
{ ZoneHVAC_UnitHeaterFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_UnitHeaterFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_UnitHeaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_UnitHeaterFields> OptionalZoneHVAC_UnitHeaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_UNITHEATER_FIELDENUMS_HXX
