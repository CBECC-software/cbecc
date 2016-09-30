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

#ifndef UTILITIES_IDD_OS_WINDOWMATERIAL_GLAZINGGROUP_THERMOCHROMIC_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WINDOWMATERIAL_GLAZINGGROUP_THERMOCHROMIC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WindowMaterial_GlazingGroup_ThermochromicFields
 *  \brief Enumeration of OS:WindowMaterial:GlazingGroup:Thermochromic's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WindowMaterial_GlazingGroup_ThermochromicFields, )
#else
class OS_WindowMaterial_GlazingGroup_ThermochromicFields: public ::EnumBase<OS_WindowMaterial_GlazingGroup_ThermochromicFields> {
 public: 
  enum domain 
  {
Handle, Name,   };
  OS_WindowMaterial_GlazingGroup_ThermochromicFields()
   : EnumBase<OS_WindowMaterial_GlazingGroup_ThermochromicFields>(Handle) {} 
  OS_WindowMaterial_GlazingGroup_ThermochromicFields(const std::string &t_name) 
   : EnumBase<OS_WindowMaterial_GlazingGroup_ThermochromicFields>(t_name) {} 
  OS_WindowMaterial_GlazingGroup_ThermochromicFields(int t_value) 
   : EnumBase<OS_WindowMaterial_GlazingGroup_ThermochromicFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WindowMaterial_GlazingGroup_ThermochromicFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WindowMaterial_GlazingGroup_ThermochromicFields>::value()); }
   private:
    friend class EnumBase<OS_WindowMaterial_GlazingGroup_ThermochromicFields>;
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
{ OS_WindowMaterial_GlazingGroup_ThermochromicFields::Handle, "Handle", "Handle"},
{ OS_WindowMaterial_GlazingGroup_ThermochromicFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WindowMaterial_GlazingGroup_ThermochromicFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WindowMaterial_GlazingGroup_ThermochromicFields> OptionalOS_WindowMaterial_GlazingGroup_ThermochromicFields ;
#endif

/** \class OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields
 *  \brief Enumeration of OS:WindowMaterial:GlazingGroup:Thermochromic's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields, )
#else
class OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields: public ::EnumBase<OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields> {
 public: 
  enum domain 
  {
OpticalDataTemperature, WindowMaterialGlazingName,   };
  OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields()
   : EnumBase<OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields>(OpticalDataTemperature) {} 
  OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields>(t_name) {} 
  OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields(int t_value) 
   : EnumBase<OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields>;
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
{ OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields::OpticalDataTemperature, "OpticalDataTemperature", "Optical Data Temperature"},
{ OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields::WindowMaterialGlazingName, "WindowMaterialGlazingName", "Window Material Glazing Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields> OptionalOS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WINDOWMATERIAL_GLAZINGGROUP_THERMOCHROMIC_FIELDENUMS_HXX
