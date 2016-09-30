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

#ifndef UTILITIES_IDD_ZONEHVAC_EQUIPMENTLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_EQUIPMENTLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_EquipmentListFields
 *  \brief Enumeration of ZoneHVAC:EquipmentList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_EquipmentListFields, )
#else
class ZoneHVAC_EquipmentListFields: public ::EnumBase<ZoneHVAC_EquipmentListFields> {
 public: 
  enum domain 
  {
Name,   };
  ZoneHVAC_EquipmentListFields()
   : EnumBase<ZoneHVAC_EquipmentListFields>(Name) {} 
  ZoneHVAC_EquipmentListFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_EquipmentListFields>(t_name) {} 
  ZoneHVAC_EquipmentListFields(int t_value) 
   : EnumBase<ZoneHVAC_EquipmentListFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_EquipmentListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_EquipmentListFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_EquipmentListFields>;
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
{ ZoneHVAC_EquipmentListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_EquipmentListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_EquipmentListFields> OptionalZoneHVAC_EquipmentListFields ;
#endif

/** \class ZoneHVAC_EquipmentListExtensibleFields
 *  \brief Enumeration of ZoneHVAC:EquipmentList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ZoneHVAC_EquipmentListExtensibleFields, )
#else
class ZoneHVAC_EquipmentListExtensibleFields: public ::EnumBase<ZoneHVAC_EquipmentListExtensibleFields> {
 public: 
  enum domain 
  {
ZoneEquipmentObjectType, ZoneEquipmentName, ZoneEquipmentCoolingSequence, ZoneEquipmentHeatingorNoLoadSequence,   };
  ZoneHVAC_EquipmentListExtensibleFields()
   : EnumBase<ZoneHVAC_EquipmentListExtensibleFields>(ZoneEquipmentObjectType) {} 
  ZoneHVAC_EquipmentListExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_EquipmentListExtensibleFields>(t_name) {} 
  ZoneHVAC_EquipmentListExtensibleFields(int t_value) 
   : EnumBase<ZoneHVAC_EquipmentListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_EquipmentListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_EquipmentListExtensibleFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_EquipmentListExtensibleFields>;
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
{ ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentObjectType, "ZoneEquipmentObjectType", "Zone Equipment Object Type"},
{ ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentName, "ZoneEquipmentName", "Zone Equipment Name"},
{ ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence, "ZoneEquipmentCoolingSequence", "Zone Equipment Cooling Sequence"},
{ ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence, "ZoneEquipmentHeatingorNoLoadSequence", "Zone Equipment Heating or No-Load Sequence"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_EquipmentListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_EquipmentListExtensibleFields> OptionalZoneHVAC_EquipmentListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_EQUIPMENTLIST_FIELDENUMS_HXX
