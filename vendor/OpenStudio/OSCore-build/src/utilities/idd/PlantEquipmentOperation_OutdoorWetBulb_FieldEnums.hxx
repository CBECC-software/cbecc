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

#ifndef UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORWETBULB_FIELDENUMS_HXX
#define UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORWETBULB_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PlantEquipmentOperation_OutdoorWetBulbFields
 *  \brief Enumeration of PlantEquipmentOperation:OutdoorWetBulb's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PlantEquipmentOperation_OutdoorWetBulbFields, )
#else
class PlantEquipmentOperation_OutdoorWetBulbFields: public ::EnumBase<PlantEquipmentOperation_OutdoorWetBulbFields> {
 public: 
  enum domain 
  {
Name,   };
  PlantEquipmentOperation_OutdoorWetBulbFields()
   : EnumBase<PlantEquipmentOperation_OutdoorWetBulbFields>(Name) {} 
  PlantEquipmentOperation_OutdoorWetBulbFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_OutdoorWetBulbFields>(t_name) {} 
  PlantEquipmentOperation_OutdoorWetBulbFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_OutdoorWetBulbFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_OutdoorWetBulbFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_OutdoorWetBulbFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_OutdoorWetBulbFields>;
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
{ PlantEquipmentOperation_OutdoorWetBulbFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_OutdoorWetBulbFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_OutdoorWetBulbFields> OptionalPlantEquipmentOperation_OutdoorWetBulbFields ;
#endif

/** \class PlantEquipmentOperation_OutdoorWetBulbExtensibleFields
 *  \brief Enumeration of PlantEquipmentOperation:OutdoorWetBulb's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PlantEquipmentOperation_OutdoorWetBulbExtensibleFields, )
#else
class PlantEquipmentOperation_OutdoorWetBulbExtensibleFields: public ::EnumBase<PlantEquipmentOperation_OutdoorWetBulbExtensibleFields> {
 public: 
  enum domain 
  {
WetBulbTemperatureRangeLowerLimit, WetBulbTemperatureRangeUpperLimit, RangeEquipmentListName,   };
  PlantEquipmentOperation_OutdoorWetBulbExtensibleFields()
   : EnumBase<PlantEquipmentOperation_OutdoorWetBulbExtensibleFields>(WetBulbTemperatureRangeLowerLimit) {} 
  PlantEquipmentOperation_OutdoorWetBulbExtensibleFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_OutdoorWetBulbExtensibleFields>(t_name) {} 
  PlantEquipmentOperation_OutdoorWetBulbExtensibleFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_OutdoorWetBulbExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_OutdoorWetBulbExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_OutdoorWetBulbExtensibleFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_OutdoorWetBulbExtensibleFields>;
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
{ PlantEquipmentOperation_OutdoorWetBulbExtensibleFields::WetBulbTemperatureRangeLowerLimit, "WetBulbTemperatureRangeLowerLimit", "Wet-Bulb Temperature Range Lower Limit"},
{ PlantEquipmentOperation_OutdoorWetBulbExtensibleFields::WetBulbTemperatureRangeUpperLimit, "WetBulbTemperatureRangeUpperLimit", "Wet-Bulb Temperature Range Upper Limit"},
{ PlantEquipmentOperation_OutdoorWetBulbExtensibleFields::RangeEquipmentListName, "RangeEquipmentListName", "Range Equipment List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_OutdoorWetBulbExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_OutdoorWetBulbExtensibleFields> OptionalPlantEquipmentOperation_OutdoorWetBulbExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORWETBULB_FIELDENUMS_HXX
