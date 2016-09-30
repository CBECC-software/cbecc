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

#ifndef UTILITIES_IDD_OS_LIGHTINGSIMULATIONZONE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_LIGHTINGSIMULATIONZONE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_LightingSimulationZoneFields
 *  \brief Enumeration of OS:LightingSimulationZone's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_LightingSimulationZoneFields, )
#else
class OS_LightingSimulationZoneFields: public ::EnumBase<OS_LightingSimulationZoneFields> {
 public: 
  enum domain 
  {
Handle, Name, GroupRenderingName,   };
  OS_LightingSimulationZoneFields()
   : EnumBase<OS_LightingSimulationZoneFields>(Handle) {} 
  OS_LightingSimulationZoneFields(const std::string &t_name) 
   : EnumBase<OS_LightingSimulationZoneFields>(t_name) {} 
  OS_LightingSimulationZoneFields(int t_value) 
   : EnumBase<OS_LightingSimulationZoneFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_LightingSimulationZoneFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_LightingSimulationZoneFields>::value()); }
   private:
    friend class EnumBase<OS_LightingSimulationZoneFields>;
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
{ OS_LightingSimulationZoneFields::Handle, "Handle", "Handle"},
{ OS_LightingSimulationZoneFields::Name, "Name", "Name"},
{ OS_LightingSimulationZoneFields::GroupRenderingName, "GroupRenderingName", "Group Rendering Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_LightingSimulationZoneFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_LightingSimulationZoneFields> OptionalOS_LightingSimulationZoneFields ;
#endif

/** \class OS_LightingSimulationZoneExtensibleFields
 *  \brief Enumeration of OS:LightingSimulationZone's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_LightingSimulationZoneExtensibleFields, )
#else
class OS_LightingSimulationZoneExtensibleFields: public ::EnumBase<OS_LightingSimulationZoneExtensibleFields> {
 public: 
  enum domain 
  {
PlanarSurfaceGroupName,   };
  OS_LightingSimulationZoneExtensibleFields()
   : EnumBase<OS_LightingSimulationZoneExtensibleFields>(PlanarSurfaceGroupName) {} 
  OS_LightingSimulationZoneExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_LightingSimulationZoneExtensibleFields>(t_name) {} 
  OS_LightingSimulationZoneExtensibleFields(int t_value) 
   : EnumBase<OS_LightingSimulationZoneExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_LightingSimulationZoneExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_LightingSimulationZoneExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_LightingSimulationZoneExtensibleFields>;
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
{ OS_LightingSimulationZoneExtensibleFields::PlanarSurfaceGroupName, "PlanarSurfaceGroupName", "Planar Surface Group Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_LightingSimulationZoneExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_LightingSimulationZoneExtensibleFields> OptionalOS_LightingSimulationZoneExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_LIGHTINGSIMULATIONZONE_FIELDENUMS_HXX
