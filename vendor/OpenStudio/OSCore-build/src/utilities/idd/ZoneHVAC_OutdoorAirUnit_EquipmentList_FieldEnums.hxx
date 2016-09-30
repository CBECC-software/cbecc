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

#ifndef UTILITIES_IDD_ZONEHVAC_OUTDOORAIRUNIT_EQUIPMENTLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_OUTDOORAIRUNIT_EQUIPMENTLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_OutdoorAirUnit_EquipmentListFields
 *  \brief Enumeration of ZoneHVAC:OutdoorAirUnit:EquipmentList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_OutdoorAirUnit_EquipmentListFields, )
#else
class ZoneHVAC_OutdoorAirUnit_EquipmentListFields: public ::EnumBase<ZoneHVAC_OutdoorAirUnit_EquipmentListFields> {
 public: 
  enum domain 
  {
Name,   };
  ZoneHVAC_OutdoorAirUnit_EquipmentListFields()
   : EnumBase<ZoneHVAC_OutdoorAirUnit_EquipmentListFields>(Name) {} 
  ZoneHVAC_OutdoorAirUnit_EquipmentListFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_OutdoorAirUnit_EquipmentListFields>(t_name) {} 
  ZoneHVAC_OutdoorAirUnit_EquipmentListFields(int t_value) 
   : EnumBase<ZoneHVAC_OutdoorAirUnit_EquipmentListFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_OutdoorAirUnit_EquipmentListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_OutdoorAirUnit_EquipmentListFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_OutdoorAirUnit_EquipmentListFields>;
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
{ ZoneHVAC_OutdoorAirUnit_EquipmentListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_OutdoorAirUnit_EquipmentListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_OutdoorAirUnit_EquipmentListFields> OptionalZoneHVAC_OutdoorAirUnit_EquipmentListFields ;
#endif

/** \class ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields
 *  \brief Enumeration of ZoneHVAC:OutdoorAirUnit:EquipmentList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields, )
#else
class ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields: public ::EnumBase<ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields> {
 public: 
  enum domain 
  {
ComponentObjectType, ComponentName,   };
  ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields()
   : EnumBase<ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields>(ComponentObjectType) {} 
  ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields>(t_name) {} 
  ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields(int t_value) 
   : EnumBase<ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields>;
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
{ ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields::ComponentObjectType, "ComponentObjectType", "Component Object Type"},
{ ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields::ComponentName, "ComponentName", "Component Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields> OptionalZoneHVAC_OutdoorAirUnit_EquipmentListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_OUTDOORAIRUNIT_EQUIPMENTLIST_FIELDENUMS_HXX
