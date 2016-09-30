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

#ifndef UTILITIES_IDD_AIRLOOPHVAC_OUTDOORAIRSYSTEM_EQUIPMENTLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_OUTDOORAIRSYSTEM_EQUIPMENTLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_OutdoorAirSystem_EquipmentListFields
 *  \brief Enumeration of AirLoopHVAC:OutdoorAirSystem:EquipmentList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_OutdoorAirSystem_EquipmentListFields, )
#else
class AirLoopHVAC_OutdoorAirSystem_EquipmentListFields: public ::EnumBase<AirLoopHVAC_OutdoorAirSystem_EquipmentListFields> {
 public: 
  enum domain 
  {
Name,   };
  AirLoopHVAC_OutdoorAirSystem_EquipmentListFields()
   : EnumBase<AirLoopHVAC_OutdoorAirSystem_EquipmentListFields>(Name) {} 
  AirLoopHVAC_OutdoorAirSystem_EquipmentListFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_OutdoorAirSystem_EquipmentListFields>(t_name) {} 
  AirLoopHVAC_OutdoorAirSystem_EquipmentListFields(int t_value) 
   : EnumBase<AirLoopHVAC_OutdoorAirSystem_EquipmentListFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_OutdoorAirSystem_EquipmentListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_OutdoorAirSystem_EquipmentListFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_OutdoorAirSystem_EquipmentListFields>;
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
{ AirLoopHVAC_OutdoorAirSystem_EquipmentListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_OutdoorAirSystem_EquipmentListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_OutdoorAirSystem_EquipmentListFields> OptionalAirLoopHVAC_OutdoorAirSystem_EquipmentListFields ;
#endif

/** \class AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields
 *  \brief Enumeration of AirLoopHVAC:OutdoorAirSystem:EquipmentList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields, )
#else
class AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields: public ::EnumBase<AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields> {
 public: 
  enum domain 
  {
ComponentObjectType, ComponentName,   };
  AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields()
   : EnumBase<AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields>(ComponentObjectType) {} 
  AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields>(t_name) {} 
  AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields(int t_value) 
   : EnumBase<AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields>;
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
{ AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentObjectType, "ComponentObjectType", "Component Object Type"},
{ AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentName, "ComponentName", "Component Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields> OptionalAirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_OUTDOORAIRSYSTEM_EQUIPMENTLIST_FIELDENUMS_HXX
