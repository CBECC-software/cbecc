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

#ifndef UTILITIES_IDD_ZONEHVAC_VENTILATEDSLAB_SLABGROUP_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_VENTILATEDSLAB_SLABGROUP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_VentilatedSlab_SlabGroupFields
 *  \brief Enumeration of ZoneHVAC:VentilatedSlab:SlabGroup's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_VentilatedSlab_SlabGroupFields, )
#else
class ZoneHVAC_VentilatedSlab_SlabGroupFields: public ::EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupFields> {
 public: 
  enum domain 
  {
Name,   };
  ZoneHVAC_VentilatedSlab_SlabGroupFields()
   : EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupFields>(Name) {} 
  ZoneHVAC_VentilatedSlab_SlabGroupFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupFields>(t_name) {} 
  ZoneHVAC_VentilatedSlab_SlabGroupFields(int t_value) 
   : EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_VentilatedSlab_SlabGroupFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupFields>;
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
{ ZoneHVAC_VentilatedSlab_SlabGroupFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_VentilatedSlab_SlabGroupFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_VentilatedSlab_SlabGroupFields> OptionalZoneHVAC_VentilatedSlab_SlabGroupFields ;
#endif

/** \class ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields
 *  \brief Enumeration of ZoneHVAC:VentilatedSlab:SlabGroup's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields, )
#else
class ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields: public ::EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields> {
 public: 
  enum domain 
  {
ZoneName, SurfaceName, CoreDiameterforSurface, CoreLengthforSurface, CoreNumbersforSurface, SlabInletNodeNameforSurface, SlabOutletNodeNameforSurface,   };
  ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields()
   : EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields>(ZoneName) {} 
  ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields>(t_name) {} 
  ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields(int t_value) 
   : EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields>;
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
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::CoreDiameterforSurface, "CoreDiameterforSurface", "Core Diameter for Surface"},
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::CoreLengthforSurface, "CoreLengthforSurface", "Core Length for Surface"},
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::CoreNumbersforSurface, "CoreNumbersforSurface", "Core Numbers for Surface"},
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::SlabInletNodeNameforSurface, "SlabInletNodeNameforSurface", "Slab Inlet Node Name for Surface"},
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::SlabOutletNodeNameforSurface, "SlabOutletNodeNameforSurface", "Slab Outlet Node Name for Surface"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields> OptionalZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_VENTILATEDSLAB_SLABGROUP_FIELDENUMS_HXX
