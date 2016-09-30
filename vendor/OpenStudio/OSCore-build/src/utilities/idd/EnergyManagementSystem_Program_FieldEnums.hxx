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

#ifndef UTILITIES_IDD_ENERGYMANAGEMENTSYSTEM_PROGRAM_FIELDENUMS_HXX
#define UTILITIES_IDD_ENERGYMANAGEMENTSYSTEM_PROGRAM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class EnergyManagementSystem_ProgramFields
 *  \brief Enumeration of EnergyManagementSystem:Program's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(EnergyManagementSystem_ProgramFields, )
#else
class EnergyManagementSystem_ProgramFields: public ::EnumBase<EnergyManagementSystem_ProgramFields> {
 public: 
  enum domain 
  {
Name,   };
  EnergyManagementSystem_ProgramFields()
   : EnumBase<EnergyManagementSystem_ProgramFields>(Name) {} 
  EnergyManagementSystem_ProgramFields(const std::string &t_name) 
   : EnumBase<EnergyManagementSystem_ProgramFields>(t_name) {} 
  EnergyManagementSystem_ProgramFields(int t_value) 
   : EnumBase<EnergyManagementSystem_ProgramFields>(t_value) {} 
  static std::string enumName() 
  { return "EnergyManagementSystem_ProgramFields"; }
  domain value() const { return static_cast<domain>(EnumBase<EnergyManagementSystem_ProgramFields>::value()); }
   private:
    friend class EnumBase<EnergyManagementSystem_ProgramFields>;
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
{ EnergyManagementSystem_ProgramFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const EnergyManagementSystem_ProgramFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<EnergyManagementSystem_ProgramFields> OptionalEnergyManagementSystem_ProgramFields ;
#endif

/** \class EnergyManagementSystem_ProgramExtensibleFields
 *  \brief Enumeration of EnergyManagementSystem:Program's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(EnergyManagementSystem_ProgramExtensibleFields, )
#else
class EnergyManagementSystem_ProgramExtensibleFields: public ::EnumBase<EnergyManagementSystem_ProgramExtensibleFields> {
 public: 
  enum domain 
  {
ProgramLine,   };
  EnergyManagementSystem_ProgramExtensibleFields()
   : EnumBase<EnergyManagementSystem_ProgramExtensibleFields>(ProgramLine) {} 
  EnergyManagementSystem_ProgramExtensibleFields(const std::string &t_name) 
   : EnumBase<EnergyManagementSystem_ProgramExtensibleFields>(t_name) {} 
  EnergyManagementSystem_ProgramExtensibleFields(int t_value) 
   : EnumBase<EnergyManagementSystem_ProgramExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "EnergyManagementSystem_ProgramExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<EnergyManagementSystem_ProgramExtensibleFields>::value()); }
   private:
    friend class EnumBase<EnergyManagementSystem_ProgramExtensibleFields>;
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
{ EnergyManagementSystem_ProgramExtensibleFields::ProgramLine, "ProgramLine", "Program Line"},
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
  inline std::ostream &operator<<(std::ostream &os, const EnergyManagementSystem_ProgramExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<EnergyManagementSystem_ProgramExtensibleFields> OptionalEnergyManagementSystem_ProgramExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ENERGYMANAGEMENTSYSTEM_PROGRAM_FIELDENUMS_HXX
