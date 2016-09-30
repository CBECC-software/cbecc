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

#ifndef UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORWETBULBDIFFERENCE_FIELDENUMS_HXX
#define UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORWETBULBDIFFERENCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PlantEquipmentOperation_OutdoorWetBulbDifferenceFields
 *  \brief Enumeration of PlantEquipmentOperation:OutdoorWetBulbDifference's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PlantEquipmentOperation_OutdoorWetBulbDifferenceFields, )
#else
class PlantEquipmentOperation_OutdoorWetBulbDifferenceFields: public ::EnumBase<PlantEquipmentOperation_OutdoorWetBulbDifferenceFields> {
 public: 
  enum domain 
  {
Name, ReferenceTemperatureNodeName,   };
  PlantEquipmentOperation_OutdoorWetBulbDifferenceFields()
   : EnumBase<PlantEquipmentOperation_OutdoorWetBulbDifferenceFields>(Name) {} 
  PlantEquipmentOperation_OutdoorWetBulbDifferenceFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_OutdoorWetBulbDifferenceFields>(t_name) {} 
  PlantEquipmentOperation_OutdoorWetBulbDifferenceFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_OutdoorWetBulbDifferenceFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_OutdoorWetBulbDifferenceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_OutdoorWetBulbDifferenceFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_OutdoorWetBulbDifferenceFields>;
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
{ PlantEquipmentOperation_OutdoorWetBulbDifferenceFields::Name, "Name", "Name"},
{ PlantEquipmentOperation_OutdoorWetBulbDifferenceFields::ReferenceTemperatureNodeName, "ReferenceTemperatureNodeName", "Reference Temperature Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_OutdoorWetBulbDifferenceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_OutdoorWetBulbDifferenceFields> OptionalPlantEquipmentOperation_OutdoorWetBulbDifferenceFields ;
#endif

/** \class PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields
 *  \brief Enumeration of PlantEquipmentOperation:OutdoorWetBulbDifference's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields, )
#else
class PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields: public ::EnumBase<PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields> {
 public: 
  enum domain 
  {
WetBulbTemperatureDifferenceRangeLowerLimit, WetBulbTemperatureDifferenceRangeUpperLimit, RangeEquipmentListName,   };
  PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields()
   : EnumBase<PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields>(WetBulbTemperatureDifferenceRangeLowerLimit) {} 
  PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields>(t_name) {} 
  PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields>;
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
{ PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields::WetBulbTemperatureDifferenceRangeLowerLimit, "WetBulbTemperatureDifferenceRangeLowerLimit", "Wet-Bulb Temperature Difference Range Lower Limit"},
{ PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields::WetBulbTemperatureDifferenceRangeUpperLimit, "WetBulbTemperatureDifferenceRangeUpperLimit", "Wet-Bulb Temperature Difference Range Upper Limit"},
{ PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields::RangeEquipmentListName, "RangeEquipmentListName", "Range Equipment List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields> OptionalPlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORWETBULBDIFFERENCE_FIELDENUMS_HXX
