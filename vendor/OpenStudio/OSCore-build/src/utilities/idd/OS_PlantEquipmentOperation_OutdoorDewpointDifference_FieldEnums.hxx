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

#ifndef UTILITIES_IDD_OS_PLANTEQUIPMENTOPERATION_OUTDOORDEWPOINTDIFFERENCE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PLANTEQUIPMENTOPERATION_OUTDOORDEWPOINTDIFFERENCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields
 *  \brief Enumeration of OS:PlantEquipmentOperation:OutdoorDewpointDifference's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields, )
#else
class OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields: public ::EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields> {
 public: 
  enum domain 
  {
Handle, Name, ReferenceTemperatureNodeName,   };
  OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields()
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields>(Handle) {} 
  OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields(const std::string &t_name) 
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields>(t_name) {} 
  OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields(int t_value) 
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields>::value()); }
   private:
    friend class EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields>;
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
{ OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields::Handle, "Handle", "Handle"},
{ OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields::Name, "Name", "Name"},
{ OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields::ReferenceTemperatureNodeName, "ReferenceTemperatureNodeName", "Reference Temperature Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields> OptionalOS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields ;
#endif

/** \class OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields
 *  \brief Enumeration of OS:PlantEquipmentOperation:OutdoorDewpointDifference's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields, )
#else
class OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields: public ::EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields> {
 public: 
  enum domain 
  {
DryBulbTemperatureDifferenceRangeLowerLimit, DryBulbTemperatureDifferenceRangeUpperLimit, RangeEquipmentListName,   };
  OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields()
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields>(DryBulbTemperatureDifferenceRangeLowerLimit) {} 
  OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields>(t_name) {} 
  OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields(int t_value) 
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields>;
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
{ OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields::DryBulbTemperatureDifferenceRangeLowerLimit, "DryBulbTemperatureDifferenceRangeLowerLimit", "Dry-Bulb Temperature Difference Range Lower Limit"},
{ OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields::DryBulbTemperatureDifferenceRangeUpperLimit, "DryBulbTemperatureDifferenceRangeUpperLimit", "Dry-Bulb Temperature Difference Range Upper Limit"},
{ OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields::RangeEquipmentListName, "RangeEquipmentListName", "Range Equipment List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields> OptionalOS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PLANTEQUIPMENTOPERATION_OUTDOORDEWPOINTDIFFERENCE_FIELDENUMS_HXX
