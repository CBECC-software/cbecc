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

#ifndef UTILITIES_IDD_FENESTRATIONSURFACE_DETAILED_FIELDENUMS_HXX
#define UTILITIES_IDD_FENESTRATIONSURFACE_DETAILED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FenestrationSurface_DetailedFields
 *  \brief Enumeration of FenestrationSurface:Detailed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FenestrationSurface_DetailedFields, )
#else
class FenestrationSurface_DetailedFields: public ::EnumBase<FenestrationSurface_DetailedFields> {
 public: 
  enum domain 
  {
Name, SurfaceType, ConstructionName, BuildingSurfaceName, OutsideBoundaryConditionObject, ViewFactortoGround, ShadingControlName, FrameandDividerName, Multiplier, NumberofVertices,   };
  FenestrationSurface_DetailedFields()
   : EnumBase<FenestrationSurface_DetailedFields>(Name) {} 
  FenestrationSurface_DetailedFields(const std::string &t_name) 
   : EnumBase<FenestrationSurface_DetailedFields>(t_name) {} 
  FenestrationSurface_DetailedFields(int t_value) 
   : EnumBase<FenestrationSurface_DetailedFields>(t_value) {} 
  static std::string enumName() 
  { return "FenestrationSurface_DetailedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FenestrationSurface_DetailedFields>::value()); }
   private:
    friend class EnumBase<FenestrationSurface_DetailedFields>;
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
{ FenestrationSurface_DetailedFields::Name, "Name", "Name"},
{ FenestrationSurface_DetailedFields::SurfaceType, "SurfaceType", "Surface Type"},
{ FenestrationSurface_DetailedFields::ConstructionName, "ConstructionName", "Construction Name"},
{ FenestrationSurface_DetailedFields::BuildingSurfaceName, "BuildingSurfaceName", "Building Surface Name"},
{ FenestrationSurface_DetailedFields::OutsideBoundaryConditionObject, "OutsideBoundaryConditionObject", "Outside Boundary Condition Object"},
{ FenestrationSurface_DetailedFields::ViewFactortoGround, "ViewFactortoGround", "View Factor to Ground"},
{ FenestrationSurface_DetailedFields::ShadingControlName, "ShadingControlName", "Shading Control Name"},
{ FenestrationSurface_DetailedFields::FrameandDividerName, "FrameandDividerName", "Frame and Divider Name"},
{ FenestrationSurface_DetailedFields::Multiplier, "Multiplier", "Multiplier"},
{ FenestrationSurface_DetailedFields::NumberofVertices, "NumberofVertices", "Number of Vertices"},
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
  inline std::ostream &operator<<(std::ostream &os, const FenestrationSurface_DetailedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FenestrationSurface_DetailedFields> OptionalFenestrationSurface_DetailedFields ;
#endif

/** \class FenestrationSurface_DetailedExtensibleFields
 *  \brief Enumeration of FenestrationSurface:Detailed's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(FenestrationSurface_DetailedExtensibleFields, )
#else
class FenestrationSurface_DetailedExtensibleFields: public ::EnumBase<FenestrationSurface_DetailedExtensibleFields> {
 public: 
  enum domain 
  {
VertexXcoordinate, VertexYcoordinate, VertexZcoordinate,   };
  FenestrationSurface_DetailedExtensibleFields()
   : EnumBase<FenestrationSurface_DetailedExtensibleFields>(VertexXcoordinate) {} 
  FenestrationSurface_DetailedExtensibleFields(const std::string &t_name) 
   : EnumBase<FenestrationSurface_DetailedExtensibleFields>(t_name) {} 
  FenestrationSurface_DetailedExtensibleFields(int t_value) 
   : EnumBase<FenestrationSurface_DetailedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "FenestrationSurface_DetailedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FenestrationSurface_DetailedExtensibleFields>::value()); }
   private:
    friend class EnumBase<FenestrationSurface_DetailedExtensibleFields>;
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
{ FenestrationSurface_DetailedExtensibleFields::VertexXcoordinate, "VertexXcoordinate", "Vertex X-coordinate"},
{ FenestrationSurface_DetailedExtensibleFields::VertexYcoordinate, "VertexYcoordinate", "Vertex Y-coordinate"},
{ FenestrationSurface_DetailedExtensibleFields::VertexZcoordinate, "VertexZcoordinate", "Vertex Z-coordinate"},
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
  inline std::ostream &operator<<(std::ostream &os, const FenestrationSurface_DetailedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FenestrationSurface_DetailedExtensibleFields> OptionalFenestrationSurface_DetailedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FENESTRATIONSURFACE_DETAILED_FIELDENUMS_HXX
