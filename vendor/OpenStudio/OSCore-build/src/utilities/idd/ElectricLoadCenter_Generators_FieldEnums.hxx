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

#ifndef UTILITIES_IDD_ELECTRICLOADCENTER_GENERATORS_FIELDENUMS_HXX
#define UTILITIES_IDD_ELECTRICLOADCENTER_GENERATORS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ElectricLoadCenter_GeneratorsFields
 *  \brief Enumeration of ElectricLoadCenter:Generators's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ElectricLoadCenter_GeneratorsFields, )
#else
class ElectricLoadCenter_GeneratorsFields: public ::EnumBase<ElectricLoadCenter_GeneratorsFields> {
 public: 
  enum domain 
  {
Name,   };
  ElectricLoadCenter_GeneratorsFields()
   : EnumBase<ElectricLoadCenter_GeneratorsFields>(Name) {} 
  ElectricLoadCenter_GeneratorsFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_GeneratorsFields>(t_name) {} 
  ElectricLoadCenter_GeneratorsFields(int t_value) 
   : EnumBase<ElectricLoadCenter_GeneratorsFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_GeneratorsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_GeneratorsFields>::value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_GeneratorsFields>;
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
{ ElectricLoadCenter_GeneratorsFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_GeneratorsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_GeneratorsFields> OptionalElectricLoadCenter_GeneratorsFields ;
#endif

/** \class ElectricLoadCenter_GeneratorsExtensibleFields
 *  \brief Enumeration of ElectricLoadCenter:Generators's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ElectricLoadCenter_GeneratorsExtensibleFields, )
#else
class ElectricLoadCenter_GeneratorsExtensibleFields: public ::EnumBase<ElectricLoadCenter_GeneratorsExtensibleFields> {
 public: 
  enum domain 
  {
GeneratorName, GeneratorObjectType, GeneratorRatedElectricPowerOutput, GeneratorAvailabilityScheduleName, GeneratorRatedThermaltoElectricalPowerRatio,   };
  ElectricLoadCenter_GeneratorsExtensibleFields()
   : EnumBase<ElectricLoadCenter_GeneratorsExtensibleFields>(GeneratorName) {} 
  ElectricLoadCenter_GeneratorsExtensibleFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_GeneratorsExtensibleFields>(t_name) {} 
  ElectricLoadCenter_GeneratorsExtensibleFields(int t_value) 
   : EnumBase<ElectricLoadCenter_GeneratorsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_GeneratorsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_GeneratorsExtensibleFields>::value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_GeneratorsExtensibleFields>;
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
{ ElectricLoadCenter_GeneratorsExtensibleFields::GeneratorName, "GeneratorName", "Generator Name"},
{ ElectricLoadCenter_GeneratorsExtensibleFields::GeneratorObjectType, "GeneratorObjectType", "Generator Object Type"},
{ ElectricLoadCenter_GeneratorsExtensibleFields::GeneratorRatedElectricPowerOutput, "GeneratorRatedElectricPowerOutput", "Generator Rated Electric Power Output"},
{ ElectricLoadCenter_GeneratorsExtensibleFields::GeneratorAvailabilityScheduleName, "GeneratorAvailabilityScheduleName", "Generator Availability Schedule Name"},
{ ElectricLoadCenter_GeneratorsExtensibleFields::GeneratorRatedThermaltoElectricalPowerRatio, "GeneratorRatedThermaltoElectricalPowerRatio", "Generator Rated Thermal to Electrical Power Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_GeneratorsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_GeneratorsExtensibleFields> OptionalElectricLoadCenter_GeneratorsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ELECTRICLOADCENTER_GENERATORS_FIELDENUMS_HXX
