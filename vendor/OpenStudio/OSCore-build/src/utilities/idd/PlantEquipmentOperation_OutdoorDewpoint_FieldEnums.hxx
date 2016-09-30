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

#ifndef UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORDEWPOINT_FIELDENUMS_HXX
#define UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORDEWPOINT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PlantEquipmentOperation_OutdoorDewpointFields
 *  \brief Enumeration of PlantEquipmentOperation:OutdoorDewpoint's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PlantEquipmentOperation_OutdoorDewpointFields, )
#else
class PlantEquipmentOperation_OutdoorDewpointFields: public ::EnumBase<PlantEquipmentOperation_OutdoorDewpointFields> {
 public: 
  enum domain 
  {
Name,   };
  PlantEquipmentOperation_OutdoorDewpointFields()
   : EnumBase<PlantEquipmentOperation_OutdoorDewpointFields>(Name) {} 
  PlantEquipmentOperation_OutdoorDewpointFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_OutdoorDewpointFields>(t_name) {} 
  PlantEquipmentOperation_OutdoorDewpointFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_OutdoorDewpointFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_OutdoorDewpointFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_OutdoorDewpointFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_OutdoorDewpointFields>;
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
{ PlantEquipmentOperation_OutdoorDewpointFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_OutdoorDewpointFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_OutdoorDewpointFields> OptionalPlantEquipmentOperation_OutdoorDewpointFields ;
#endif

/** \class PlantEquipmentOperation_OutdoorDewpointExtensibleFields
 *  \brief Enumeration of PlantEquipmentOperation:OutdoorDewpoint's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PlantEquipmentOperation_OutdoorDewpointExtensibleFields, )
#else
class PlantEquipmentOperation_OutdoorDewpointExtensibleFields: public ::EnumBase<PlantEquipmentOperation_OutdoorDewpointExtensibleFields> {
 public: 
  enum domain 
  {
DewpointTemperatureRangeLowerLimit, DewpointTemperatureRangeUpperLimit, RangeEquipmentListName,   };
  PlantEquipmentOperation_OutdoorDewpointExtensibleFields()
   : EnumBase<PlantEquipmentOperation_OutdoorDewpointExtensibleFields>(DewpointTemperatureRangeLowerLimit) {} 
  PlantEquipmentOperation_OutdoorDewpointExtensibleFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_OutdoorDewpointExtensibleFields>(t_name) {} 
  PlantEquipmentOperation_OutdoorDewpointExtensibleFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_OutdoorDewpointExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_OutdoorDewpointExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_OutdoorDewpointExtensibleFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_OutdoorDewpointExtensibleFields>;
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
{ PlantEquipmentOperation_OutdoorDewpointExtensibleFields::DewpointTemperatureRangeLowerLimit, "DewpointTemperatureRangeLowerLimit", "Dewpoint Temperature Range Lower Limit"},
{ PlantEquipmentOperation_OutdoorDewpointExtensibleFields::DewpointTemperatureRangeUpperLimit, "DewpointTemperatureRangeUpperLimit", "Dewpoint Temperature Range Upper Limit"},
{ PlantEquipmentOperation_OutdoorDewpointExtensibleFields::RangeEquipmentListName, "RangeEquipmentListName", "Range Equipment List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_OutdoorDewpointExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_OutdoorDewpointExtensibleFields> OptionalPlantEquipmentOperation_OutdoorDewpointExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PLANTEQUIPMENTOPERATION_OUTDOORDEWPOINT_FIELDENUMS_HXX
