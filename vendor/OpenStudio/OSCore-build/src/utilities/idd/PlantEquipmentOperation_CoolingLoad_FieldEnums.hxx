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

#ifndef UTILITIES_IDD_PLANTEQUIPMENTOPERATION_COOLINGLOAD_FIELDENUMS_HXX
#define UTILITIES_IDD_PLANTEQUIPMENTOPERATION_COOLINGLOAD_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PlantEquipmentOperation_CoolingLoadFields
 *  \brief Enumeration of PlantEquipmentOperation:CoolingLoad's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PlantEquipmentOperation_CoolingLoadFields, )
#else
class PlantEquipmentOperation_CoolingLoadFields: public ::EnumBase<PlantEquipmentOperation_CoolingLoadFields> {
 public: 
  enum domain 
  {
Name,   };
  PlantEquipmentOperation_CoolingLoadFields()
   : EnumBase<PlantEquipmentOperation_CoolingLoadFields>(Name) {} 
  PlantEquipmentOperation_CoolingLoadFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_CoolingLoadFields>(t_name) {} 
  PlantEquipmentOperation_CoolingLoadFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_CoolingLoadFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_CoolingLoadFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_CoolingLoadFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_CoolingLoadFields>;
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
{ PlantEquipmentOperation_CoolingLoadFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_CoolingLoadFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_CoolingLoadFields> OptionalPlantEquipmentOperation_CoolingLoadFields ;
#endif

/** \class PlantEquipmentOperation_CoolingLoadExtensibleFields
 *  \brief Enumeration of PlantEquipmentOperation:CoolingLoad's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PlantEquipmentOperation_CoolingLoadExtensibleFields, )
#else
class PlantEquipmentOperation_CoolingLoadExtensibleFields: public ::EnumBase<PlantEquipmentOperation_CoolingLoadExtensibleFields> {
 public: 
  enum domain 
  {
LoadRangeLowerLimit, LoadRangeUpperLimit, RangeEquipmentListName,   };
  PlantEquipmentOperation_CoolingLoadExtensibleFields()
   : EnumBase<PlantEquipmentOperation_CoolingLoadExtensibleFields>(LoadRangeLowerLimit) {} 
  PlantEquipmentOperation_CoolingLoadExtensibleFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_CoolingLoadExtensibleFields>(t_name) {} 
  PlantEquipmentOperation_CoolingLoadExtensibleFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_CoolingLoadExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_CoolingLoadExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_CoolingLoadExtensibleFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_CoolingLoadExtensibleFields>;
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
{ PlantEquipmentOperation_CoolingLoadExtensibleFields::LoadRangeLowerLimit, "LoadRangeLowerLimit", "Load Range Lower Limit"},
{ PlantEquipmentOperation_CoolingLoadExtensibleFields::LoadRangeUpperLimit, "LoadRangeUpperLimit", "Load Range Upper Limit"},
{ PlantEquipmentOperation_CoolingLoadExtensibleFields::RangeEquipmentListName, "RangeEquipmentListName", "Range Equipment List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_CoolingLoadExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_CoolingLoadExtensibleFields> OptionalPlantEquipmentOperation_CoolingLoadExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PLANTEQUIPMENTOPERATION_COOLINGLOAD_FIELDENUMS_HXX
