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

#ifndef UTILITIES_IDD_ENERGYMANAGEMENTSYSTEM_PROGRAMCALLINGMANAGER_FIELDENUMS_HXX
#define UTILITIES_IDD_ENERGYMANAGEMENTSYSTEM_PROGRAMCALLINGMANAGER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class EnergyManagementSystem_ProgramCallingManagerFields
 *  \brief Enumeration of EnergyManagementSystem:ProgramCallingManager's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(EnergyManagementSystem_ProgramCallingManagerFields, )
#else
class EnergyManagementSystem_ProgramCallingManagerFields: public ::EnumBase<EnergyManagementSystem_ProgramCallingManagerFields> {
 public: 
  enum domain 
  {
Name, EnergyPlusModelCallingPoint,   };
  EnergyManagementSystem_ProgramCallingManagerFields()
   : EnumBase<EnergyManagementSystem_ProgramCallingManagerFields>(Name) {} 
  EnergyManagementSystem_ProgramCallingManagerFields(const std::string &t_name) 
   : EnumBase<EnergyManagementSystem_ProgramCallingManagerFields>(t_name) {} 
  EnergyManagementSystem_ProgramCallingManagerFields(int t_value) 
   : EnumBase<EnergyManagementSystem_ProgramCallingManagerFields>(t_value) {} 
  static std::string enumName() 
  { return "EnergyManagementSystem_ProgramCallingManagerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<EnergyManagementSystem_ProgramCallingManagerFields>::value()); }
   private:
    friend class EnumBase<EnergyManagementSystem_ProgramCallingManagerFields>;
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
{ EnergyManagementSystem_ProgramCallingManagerFields::Name, "Name", "Name"},
{ EnergyManagementSystem_ProgramCallingManagerFields::EnergyPlusModelCallingPoint, "EnergyPlusModelCallingPoint", "EnergyPlus Model Calling Point"},
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
  inline std::ostream &operator<<(std::ostream &os, const EnergyManagementSystem_ProgramCallingManagerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<EnergyManagementSystem_ProgramCallingManagerFields> OptionalEnergyManagementSystem_ProgramCallingManagerFields ;
#endif

/** \class EnergyManagementSystem_ProgramCallingManagerExtensibleFields
 *  \brief Enumeration of EnergyManagementSystem:ProgramCallingManager's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(EnergyManagementSystem_ProgramCallingManagerExtensibleFields, )
#else
class EnergyManagementSystem_ProgramCallingManagerExtensibleFields: public ::EnumBase<EnergyManagementSystem_ProgramCallingManagerExtensibleFields> {
 public: 
  enum domain 
  {
ProgramName,   };
  EnergyManagementSystem_ProgramCallingManagerExtensibleFields()
   : EnumBase<EnergyManagementSystem_ProgramCallingManagerExtensibleFields>(ProgramName) {} 
  EnergyManagementSystem_ProgramCallingManagerExtensibleFields(const std::string &t_name) 
   : EnumBase<EnergyManagementSystem_ProgramCallingManagerExtensibleFields>(t_name) {} 
  EnergyManagementSystem_ProgramCallingManagerExtensibleFields(int t_value) 
   : EnumBase<EnergyManagementSystem_ProgramCallingManagerExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "EnergyManagementSystem_ProgramCallingManagerExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<EnergyManagementSystem_ProgramCallingManagerExtensibleFields>::value()); }
   private:
    friend class EnumBase<EnergyManagementSystem_ProgramCallingManagerExtensibleFields>;
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
{ EnergyManagementSystem_ProgramCallingManagerExtensibleFields::ProgramName, "ProgramName", "Program Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const EnergyManagementSystem_ProgramCallingManagerExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<EnergyManagementSystem_ProgramCallingManagerExtensibleFields> OptionalEnergyManagementSystem_ProgramCallingManagerExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ENERGYMANAGEMENTSYSTEM_PROGRAMCALLINGMANAGER_FIELDENUMS_HXX
