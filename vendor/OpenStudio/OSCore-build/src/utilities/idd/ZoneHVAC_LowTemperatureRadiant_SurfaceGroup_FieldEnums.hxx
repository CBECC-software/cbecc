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

#ifndef UTILITIES_IDD_ZONEHVAC_LOWTEMPERATURERADIANT_SURFACEGROUP_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_LOWTEMPERATURERADIANT_SURFACEGROUP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields
 *  \brief Enumeration of ZoneHVAC:LowTemperatureRadiant:SurfaceGroup's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields, )
#else
class ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields: public ::EnumBase<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields> {
 public: 
  enum domain 
  {
Name,   };
  ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields()
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields>(Name) {} 
  ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields>(t_name) {} 
  ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields(int t_value) 
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields>;
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
{ ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields> OptionalZoneHVAC_LowTemperatureRadiant_SurfaceGroupFields ;
#endif

/** \class ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields
 *  \brief Enumeration of ZoneHVAC:LowTemperatureRadiant:SurfaceGroup's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields, )
#else
class ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields: public ::EnumBase<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceName, FlowFractionforSurface,   };
  ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields()
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields>(SurfaceName) {} 
  ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields>(t_name) {} 
  ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields(int t_value) 
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields>;
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
{ ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
{ ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields::FlowFractionforSurface, "FlowFractionforSurface", "Flow Fraction for Surface"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields> OptionalZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_LOWTEMPERATURERADIANT_SURFACEGROUP_FIELDENUMS_HXX
