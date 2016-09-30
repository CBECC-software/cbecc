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

#ifndef UTILITIES_IDD_ZONEPROPERTY_USERVIEWFACTORS_BYSURFACENAME_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEPROPERTY_USERVIEWFACTORS_BYSURFACENAME_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneProperty_UserViewFactors_bySurfaceNameFields
 *  \brief Enumeration of ZoneProperty:UserViewFactors:bySurfaceName's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneProperty_UserViewFactors_bySurfaceNameFields, )
#else
class ZoneProperty_UserViewFactors_bySurfaceNameFields: public ::EnumBase<ZoneProperty_UserViewFactors_bySurfaceNameFields> {
 public: 
  enum domain 
  {
ZoneName,   };
  ZoneProperty_UserViewFactors_bySurfaceNameFields()
   : EnumBase<ZoneProperty_UserViewFactors_bySurfaceNameFields>(ZoneName) {} 
  ZoneProperty_UserViewFactors_bySurfaceNameFields(const std::string &t_name) 
   : EnumBase<ZoneProperty_UserViewFactors_bySurfaceNameFields>(t_name) {} 
  ZoneProperty_UserViewFactors_bySurfaceNameFields(int t_value) 
   : EnumBase<ZoneProperty_UserViewFactors_bySurfaceNameFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneProperty_UserViewFactors_bySurfaceNameFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneProperty_UserViewFactors_bySurfaceNameFields>::value()); }
   private:
    friend class EnumBase<ZoneProperty_UserViewFactors_bySurfaceNameFields>;
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
{ ZoneProperty_UserViewFactors_bySurfaceNameFields::ZoneName, "ZoneName", "Zone Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneProperty_UserViewFactors_bySurfaceNameFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneProperty_UserViewFactors_bySurfaceNameFields> OptionalZoneProperty_UserViewFactors_bySurfaceNameFields ;
#endif

/** \class ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields
 *  \brief Enumeration of ZoneProperty:UserViewFactors:bySurfaceName's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields, )
#else
class ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields: public ::EnumBase<ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields> {
 public: 
  enum domain 
  {
FromSurface, ToSurface, ViewFactor,   };
  ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields()
   : EnumBase<ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields>(FromSurface) {} 
  ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields>(t_name) {} 
  ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields(int t_value) 
   : EnumBase<ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields>::value()); }
   private:
    friend class EnumBase<ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields>;
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
{ ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields::FromSurface, "FromSurface", "From Surface"},
{ ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields::ToSurface, "ToSurface", "To Surface"},
{ ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields::ViewFactor, "ViewFactor", "View Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields> OptionalZoneProperty_UserViewFactors_bySurfaceNameExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEPROPERTY_USERVIEWFACTORS_BYSURFACENAME_FIELDENUMS_HXX
