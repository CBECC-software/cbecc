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

#ifndef UTILITIES_IDD_ZONEHVAC_EQUIPMENTCONNECTIONS_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_EQUIPMENTCONNECTIONS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_EquipmentConnectionsFields
 *  \brief Enumeration of ZoneHVAC:EquipmentConnections's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_EquipmentConnectionsFields, )
#else
class ZoneHVAC_EquipmentConnectionsFields: public ::EnumBase<ZoneHVAC_EquipmentConnectionsFields> {
 public: 
  enum domain 
  {
ZoneName, ZoneConditioningEquipmentListName, ZoneAirInletNodeorNodeListName, ZoneAirExhaustNodeorNodeListName, ZoneAirNodeName, ZoneReturnAirNodeName, ZoneReturnAirFlowRateFractionScheduleName, ZoneReturnAirFlowRateBasisNodeorNodeListName,   };
  ZoneHVAC_EquipmentConnectionsFields()
   : EnumBase<ZoneHVAC_EquipmentConnectionsFields>(ZoneName) {} 
  ZoneHVAC_EquipmentConnectionsFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_EquipmentConnectionsFields>(t_name) {} 
  ZoneHVAC_EquipmentConnectionsFields(int t_value) 
   : EnumBase<ZoneHVAC_EquipmentConnectionsFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_EquipmentConnectionsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_EquipmentConnectionsFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_EquipmentConnectionsFields>;
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
{ ZoneHVAC_EquipmentConnectionsFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName, "ZoneConditioningEquipmentListName", "Zone Conditioning Equipment List Name"},
{ ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName, "ZoneAirInletNodeorNodeListName", "Zone Air Inlet Node or NodeList Name"},
{ ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, "ZoneAirExhaustNodeorNodeListName", "Zone Air Exhaust Node or NodeList Name"},
{ ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName, "ZoneAirNodeName", "Zone Air Node Name"},
{ ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeName, "ZoneReturnAirNodeName", "Zone Return Air Node Name"},
{ ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirFlowRateFractionScheduleName, "ZoneReturnAirFlowRateFractionScheduleName", "Zone Return Air Flow Rate Fraction Schedule Name"},
{ ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirFlowRateBasisNodeorNodeListName, "ZoneReturnAirFlowRateBasisNodeorNodeListName", "Zone Return Air Flow Rate Basis Node or NodeList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_EquipmentConnectionsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_EquipmentConnectionsFields> OptionalZoneHVAC_EquipmentConnectionsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_EQUIPMENTCONNECTIONS_FIELDENUMS_HXX
