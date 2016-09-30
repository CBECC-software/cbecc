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

#ifndef UTILITIES_IDD_OS_CONSTRUCTION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CONSTRUCTION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ConstructionFields
 *  \brief Enumeration of OS:Construction's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ConstructionFields, )
#else
class OS_ConstructionFields: public ::EnumBase<OS_ConstructionFields> {
 public: 
  enum domain 
  {
Handle, Name, SurfaceRenderingName,   };
  OS_ConstructionFields()
   : EnumBase<OS_ConstructionFields>(Handle) {} 
  OS_ConstructionFields(const std::string &t_name) 
   : EnumBase<OS_ConstructionFields>(t_name) {} 
  OS_ConstructionFields(int t_value) 
   : EnumBase<OS_ConstructionFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ConstructionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ConstructionFields>::value()); }
   private:
    friend class EnumBase<OS_ConstructionFields>;
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
{ OS_ConstructionFields::Handle, "Handle", "Handle"},
{ OS_ConstructionFields::Name, "Name", "Name"},
{ OS_ConstructionFields::SurfaceRenderingName, "SurfaceRenderingName", "Surface Rendering Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ConstructionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ConstructionFields> OptionalOS_ConstructionFields ;
#endif

/** \class OS_ConstructionExtensibleFields
 *  \brief Enumeration of OS:Construction's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_ConstructionExtensibleFields, )
#else
class OS_ConstructionExtensibleFields: public ::EnumBase<OS_ConstructionExtensibleFields> {
 public: 
  enum domain 
  {
Layer,   };
  OS_ConstructionExtensibleFields()
   : EnumBase<OS_ConstructionExtensibleFields>(Layer) {} 
  OS_ConstructionExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_ConstructionExtensibleFields>(t_name) {} 
  OS_ConstructionExtensibleFields(int t_value) 
   : EnumBase<OS_ConstructionExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ConstructionExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ConstructionExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_ConstructionExtensibleFields>;
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
{ OS_ConstructionExtensibleFields::Layer, "Layer", "Layer"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ConstructionExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ConstructionExtensibleFields> OptionalOS_ConstructionExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CONSTRUCTION_FIELDENUMS_HXX
