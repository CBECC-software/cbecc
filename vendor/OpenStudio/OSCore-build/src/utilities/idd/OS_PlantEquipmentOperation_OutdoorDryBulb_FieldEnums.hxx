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

#ifndef UTILITIES_IDD_OS_PLANTEQUIPMENTOPERATION_OUTDOORDRYBULB_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PLANTEQUIPMENTOPERATION_OUTDOORDRYBULB_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_PlantEquipmentOperation_OutdoorDryBulbFields
 *  \brief Enumeration of OS:PlantEquipmentOperation:OutdoorDryBulb's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_PlantEquipmentOperation_OutdoorDryBulbFields, )
#else
class OS_PlantEquipmentOperation_OutdoorDryBulbFields: public ::EnumBase<OS_PlantEquipmentOperation_OutdoorDryBulbFields> {
 public: 
  enum domain 
  {
Handle, Name,   };
  OS_PlantEquipmentOperation_OutdoorDryBulbFields()
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDryBulbFields>(Handle) {} 
  OS_PlantEquipmentOperation_OutdoorDryBulbFields(const std::string &t_name) 
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDryBulbFields>(t_name) {} 
  OS_PlantEquipmentOperation_OutdoorDryBulbFields(int t_value) 
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDryBulbFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PlantEquipmentOperation_OutdoorDryBulbFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PlantEquipmentOperation_OutdoorDryBulbFields>::value()); }
   private:
    friend class EnumBase<OS_PlantEquipmentOperation_OutdoorDryBulbFields>;
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
{ OS_PlantEquipmentOperation_OutdoorDryBulbFields::Handle, "Handle", "Handle"},
{ OS_PlantEquipmentOperation_OutdoorDryBulbFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PlantEquipmentOperation_OutdoorDryBulbFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PlantEquipmentOperation_OutdoorDryBulbFields> OptionalOS_PlantEquipmentOperation_OutdoorDryBulbFields ;
#endif

/** \class OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields
 *  \brief Enumeration of OS:PlantEquipmentOperation:OutdoorDryBulb's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields, )
#else
class OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields: public ::EnumBase<OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields> {
 public: 
  enum domain 
  {
DryBulbTemperatureRangeLowerLimit, DryBulbTemperatureRangeUpperLimit, RangeEquipmentListName,   };
  OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields()
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields>(DryBulbTemperatureRangeLowerLimit) {} 
  OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields>(t_name) {} 
  OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields(int t_value) 
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields>;
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
{ OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields::DryBulbTemperatureRangeLowerLimit, "DryBulbTemperatureRangeLowerLimit", "Dry-Bulb Temperature Range Lower Limit"},
{ OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields::DryBulbTemperatureRangeUpperLimit, "DryBulbTemperatureRangeUpperLimit", "Dry-Bulb Temperature Range Upper Limit"},
{ OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields::RangeEquipmentListName, "RangeEquipmentListName", "Range Equipment List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields> OptionalOS_PlantEquipmentOperation_OutdoorDryBulbExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PLANTEQUIPMENTOPERATION_OUTDOORDRYBULB_FIELDENUMS_HXX
