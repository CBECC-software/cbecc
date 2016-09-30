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

#ifndef UTILITIES_IDD_SURFACEPROPERTY_HEATTRANSFERALGORITHM_SURFACELIST_FIELDENUMS_HXX
#define UTILITIES_IDD_SURFACEPROPERTY_HEATTRANSFERALGORITHM_SURFACELIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields
 *  \brief Enumeration of SurfaceProperty:HeatTransferAlgorithm:SurfaceList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields, )
#else
class SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields: public ::EnumBase<SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields> {
 public: 
  enum domain 
  {
Name, Algorithm,   };
  SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields()
   : EnumBase<SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields>(Name) {} 
  SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields(const std::string &t_name) 
   : EnumBase<SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields>(t_name) {} 
  SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields(int t_value) 
   : EnumBase<SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields>::value()); }
   private:
    friend class EnumBase<SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields>;
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
{ SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields::Name, "Name", "Name"},
{ SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields::Algorithm, "Algorithm", "Algorithm"},
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
  inline std::ostream &operator<<(std::ostream &os, const SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields> OptionalSurfaceProperty_HeatTransferAlgorithm_SurfaceListFields ;
#endif

/** \class SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields
 *  \brief Enumeration of SurfaceProperty:HeatTransferAlgorithm:SurfaceList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields, )
#else
class SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields: public ::EnumBase<SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceName,   };
  SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields()
   : EnumBase<SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields>(SurfaceName) {} 
  SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields(const std::string &t_name) 
   : EnumBase<SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields>(t_name) {} 
  SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields(int t_value) 
   : EnumBase<SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields>::value()); }
   private:
    friend class EnumBase<SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields>;
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
{ SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields> OptionalSurfaceProperty_HeatTransferAlgorithm_SurfaceListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SURFACEPROPERTY_HEATTRANSFERALGORITHM_SURFACELIST_FIELDENUMS_HXX
