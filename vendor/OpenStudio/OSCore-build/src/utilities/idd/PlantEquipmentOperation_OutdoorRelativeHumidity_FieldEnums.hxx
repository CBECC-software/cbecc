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

#ifndef UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORRELATIVEHUMIDITY_FIELDENUMS_HXX
#define UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORRELATIVEHUMIDITY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PlantEquipmentOperation_OutdoorRelativeHumidityFields
 *  \brief Enumeration of PlantEquipmentOperation:OutdoorRelativeHumidity's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PlantEquipmentOperation_OutdoorRelativeHumidityFields, )
#else
class PlantEquipmentOperation_OutdoorRelativeHumidityFields: public ::EnumBase<PlantEquipmentOperation_OutdoorRelativeHumidityFields> {
 public: 
  enum domain 
  {
Name,   };
  PlantEquipmentOperation_OutdoorRelativeHumidityFields()
   : EnumBase<PlantEquipmentOperation_OutdoorRelativeHumidityFields>(Name) {} 
  PlantEquipmentOperation_OutdoorRelativeHumidityFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_OutdoorRelativeHumidityFields>(t_name) {} 
  PlantEquipmentOperation_OutdoorRelativeHumidityFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_OutdoorRelativeHumidityFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_OutdoorRelativeHumidityFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_OutdoorRelativeHumidityFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_OutdoorRelativeHumidityFields>;
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
{ PlantEquipmentOperation_OutdoorRelativeHumidityFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_OutdoorRelativeHumidityFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_OutdoorRelativeHumidityFields> OptionalPlantEquipmentOperation_OutdoorRelativeHumidityFields ;
#endif

/** \class PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields
 *  \brief Enumeration of PlantEquipmentOperation:OutdoorRelativeHumidity's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields, )
#else
class PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields: public ::EnumBase<PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields> {
 public: 
  enum domain 
  {
RelativeHumidityRangeLowerLimit, RelativeHumidityRangeUpperLimit, RangeEquipmentListName,   };
  PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields()
   : EnumBase<PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields>(RelativeHumidityRangeLowerLimit) {} 
  PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields>(t_name) {} 
  PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields>;
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
{ PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields::RelativeHumidityRangeLowerLimit, "RelativeHumidityRangeLowerLimit", "Relative Humidity Range Lower Limit"},
{ PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields::RelativeHumidityRangeUpperLimit, "RelativeHumidityRangeUpperLimit", "Relative Humidity Range Upper Limit"},
{ PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields::RangeEquipmentListName, "RangeEquipmentListName", "Range Equipment List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields> OptionalPlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORRELATIVEHUMIDITY_FIELDENUMS_HXX
