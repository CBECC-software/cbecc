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

#ifndef UTILITIES_IDD_OS_SUBSURFACE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SUBSURFACE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SubSurfaceFields
 *  \brief Enumeration of OS:SubSurface's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SubSurfaceFields, )
#else
class OS_SubSurfaceFields: public ::EnumBase<OS_SubSurfaceFields> {
 public: 
  enum domain 
  {
Handle, Name, SubSurfaceType, ConstructionName, SurfaceName, OutsideBoundaryConditionObject, ViewFactortoGround, ShadingControlName, FrameandDividerName, Multiplier, NumberofVertices,   };
  OS_SubSurfaceFields()
   : EnumBase<OS_SubSurfaceFields>(Handle) {} 
  OS_SubSurfaceFields(const std::string &t_name) 
   : EnumBase<OS_SubSurfaceFields>(t_name) {} 
  OS_SubSurfaceFields(int t_value) 
   : EnumBase<OS_SubSurfaceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SubSurfaceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SubSurfaceFields>::value()); }
   private:
    friend class EnumBase<OS_SubSurfaceFields>;
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
{ OS_SubSurfaceFields::Handle, "Handle", "Handle"},
{ OS_SubSurfaceFields::Name, "Name", "Name"},
{ OS_SubSurfaceFields::SubSurfaceType, "SubSurfaceType", "Sub Surface Type"},
{ OS_SubSurfaceFields::ConstructionName, "ConstructionName", "Construction Name"},
{ OS_SubSurfaceFields::SurfaceName, "SurfaceName", "Surface Name"},
{ OS_SubSurfaceFields::OutsideBoundaryConditionObject, "OutsideBoundaryConditionObject", "Outside Boundary Condition Object"},
{ OS_SubSurfaceFields::ViewFactortoGround, "ViewFactortoGround", "View Factor to Ground"},
{ OS_SubSurfaceFields::ShadingControlName, "ShadingControlName", "Shading Control Name"},
{ OS_SubSurfaceFields::FrameandDividerName, "FrameandDividerName", "Frame and Divider Name"},
{ OS_SubSurfaceFields::Multiplier, "Multiplier", "Multiplier"},
{ OS_SubSurfaceFields::NumberofVertices, "NumberofVertices", "Number of Vertices"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SubSurfaceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SubSurfaceFields> OptionalOS_SubSurfaceFields ;
#endif

/** \class OS_SubSurfaceExtensibleFields
 *  \brief Enumeration of OS:SubSurface's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_SubSurfaceExtensibleFields, )
#else
class OS_SubSurfaceExtensibleFields: public ::EnumBase<OS_SubSurfaceExtensibleFields> {
 public: 
  enum domain 
  {
VertexXcoordinate, VertexYcoordinate, VertexZcoordinate,   };
  OS_SubSurfaceExtensibleFields()
   : EnumBase<OS_SubSurfaceExtensibleFields>(VertexXcoordinate) {} 
  OS_SubSurfaceExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_SubSurfaceExtensibleFields>(t_name) {} 
  OS_SubSurfaceExtensibleFields(int t_value) 
   : EnumBase<OS_SubSurfaceExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SubSurfaceExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SubSurfaceExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_SubSurfaceExtensibleFields>;
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
{ OS_SubSurfaceExtensibleFields::VertexXcoordinate, "VertexXcoordinate", "Vertex X-coordinate"},
{ OS_SubSurfaceExtensibleFields::VertexYcoordinate, "VertexYcoordinate", "Vertex Y-coordinate"},
{ OS_SubSurfaceExtensibleFields::VertexZcoordinate, "VertexZcoordinate", "Vertex Z-coordinate"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SubSurfaceExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SubSurfaceExtensibleFields> OptionalOS_SubSurfaceExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SUBSURFACE_FIELDENUMS_HXX
