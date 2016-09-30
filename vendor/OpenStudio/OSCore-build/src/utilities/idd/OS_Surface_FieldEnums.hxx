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

#ifndef UTILITIES_IDD_OS_SURFACE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SURFACE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SurfaceFields
 *  \brief Enumeration of OS:Surface's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SurfaceFields, )
#else
class OS_SurfaceFields: public ::EnumBase<OS_SurfaceFields> {
 public: 
  enum domain 
  {
Handle, Name, SurfaceType, ConstructionName, SpaceName, OutsideBoundaryCondition, OutsideBoundaryConditionObject, SunExposure, WindExposure, ViewFactortoGround, NumberofVertices,   };
  OS_SurfaceFields()
   : EnumBase<OS_SurfaceFields>(Handle) {} 
  OS_SurfaceFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceFields>(t_name) {} 
  OS_SurfaceFields(int t_value) 
   : EnumBase<OS_SurfaceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceFields>::value()); }
   private:
    friend class EnumBase<OS_SurfaceFields>;
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
{ OS_SurfaceFields::Handle, "Handle", "Handle"},
{ OS_SurfaceFields::Name, "Name", "Name"},
{ OS_SurfaceFields::SurfaceType, "SurfaceType", "Surface Type"},
{ OS_SurfaceFields::ConstructionName, "ConstructionName", "Construction Name"},
{ OS_SurfaceFields::SpaceName, "SpaceName", "Space Name"},
{ OS_SurfaceFields::OutsideBoundaryCondition, "OutsideBoundaryCondition", "Outside Boundary Condition"},
{ OS_SurfaceFields::OutsideBoundaryConditionObject, "OutsideBoundaryConditionObject", "Outside Boundary Condition Object"},
{ OS_SurfaceFields::SunExposure, "SunExposure", "Sun Exposure"},
{ OS_SurfaceFields::WindExposure, "WindExposure", "Wind Exposure"},
{ OS_SurfaceFields::ViewFactortoGround, "ViewFactortoGround", "View Factor to Ground"},
{ OS_SurfaceFields::NumberofVertices, "NumberofVertices", "Number of Vertices"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceFields> OptionalOS_SurfaceFields ;
#endif

/** \class OS_SurfaceExtensibleFields
 *  \brief Enumeration of OS:Surface's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_SurfaceExtensibleFields, )
#else
class OS_SurfaceExtensibleFields: public ::EnumBase<OS_SurfaceExtensibleFields> {
 public: 
  enum domain 
  {
VertexXcoordinate, VertexYcoordinate, VertexZcoordinate,   };
  OS_SurfaceExtensibleFields()
   : EnumBase<OS_SurfaceExtensibleFields>(VertexXcoordinate) {} 
  OS_SurfaceExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceExtensibleFields>(t_name) {} 
  OS_SurfaceExtensibleFields(int t_value) 
   : EnumBase<OS_SurfaceExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_SurfaceExtensibleFields>;
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
{ OS_SurfaceExtensibleFields::VertexXcoordinate, "VertexXcoordinate", "Vertex X-coordinate"},
{ OS_SurfaceExtensibleFields::VertexYcoordinate, "VertexYcoordinate", "Vertex Y-coordinate"},
{ OS_SurfaceExtensibleFields::VertexZcoordinate, "VertexZcoordinate", "Vertex Z-coordinate"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceExtensibleFields> OptionalOS_SurfaceExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SURFACE_FIELDENUMS_HXX
