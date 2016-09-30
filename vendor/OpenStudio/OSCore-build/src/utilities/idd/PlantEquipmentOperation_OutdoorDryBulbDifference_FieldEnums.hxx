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

#ifndef UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORDRYBULBDIFFERENCE_FIELDENUMS_HXX
#define UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORDRYBULBDIFFERENCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PlantEquipmentOperation_OutdoorDryBulbDifferenceFields
 *  \brief Enumeration of PlantEquipmentOperation:OutdoorDryBulbDifference's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PlantEquipmentOperation_OutdoorDryBulbDifferenceFields, )
#else
class PlantEquipmentOperation_OutdoorDryBulbDifferenceFields: public ::EnumBase<PlantEquipmentOperation_OutdoorDryBulbDifferenceFields> {
 public: 
  enum domain 
  {
Name, ReferenceTemperatureNodeName,   };
  PlantEquipmentOperation_OutdoorDryBulbDifferenceFields()
   : EnumBase<PlantEquipmentOperation_OutdoorDryBulbDifferenceFields>(Name) {} 
  PlantEquipmentOperation_OutdoorDryBulbDifferenceFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_OutdoorDryBulbDifferenceFields>(t_name) {} 
  PlantEquipmentOperation_OutdoorDryBulbDifferenceFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_OutdoorDryBulbDifferenceFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_OutdoorDryBulbDifferenceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_OutdoorDryBulbDifferenceFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_OutdoorDryBulbDifferenceFields>;
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
{ PlantEquipmentOperation_OutdoorDryBulbDifferenceFields::Name, "Name", "Name"},
{ PlantEquipmentOperation_OutdoorDryBulbDifferenceFields::ReferenceTemperatureNodeName, "ReferenceTemperatureNodeName", "Reference Temperature Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_OutdoorDryBulbDifferenceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_OutdoorDryBulbDifferenceFields> OptionalPlantEquipmentOperation_OutdoorDryBulbDifferenceFields ;
#endif

/** \class PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields
 *  \brief Enumeration of PlantEquipmentOperation:OutdoorDryBulbDifference's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields, )
#else
class PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields: public ::EnumBase<PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields> {
 public: 
  enum domain 
  {
DryBulbTemperatureDifferenceRangeLowerLimit, DryBulbTemperatureDifferenceRangeUpperLimit, RangeEquipmentListName,   };
  PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields()
   : EnumBase<PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields>(DryBulbTemperatureDifferenceRangeLowerLimit) {} 
  PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields>(t_name) {} 
  PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields>;
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
{ PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields::DryBulbTemperatureDifferenceRangeLowerLimit, "DryBulbTemperatureDifferenceRangeLowerLimit", "Dry-Bulb Temperature Difference Range Lower Limit"},
{ PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields::DryBulbTemperatureDifferenceRangeUpperLimit, "DryBulbTemperatureDifferenceRangeUpperLimit", "Dry-Bulb Temperature Difference Range Upper Limit"},
{ PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields::RangeEquipmentListName, "RangeEquipmentListName", "Range Equipment List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields> OptionalPlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORDRYBULBDIFFERENCE_FIELDENUMS_HXX
