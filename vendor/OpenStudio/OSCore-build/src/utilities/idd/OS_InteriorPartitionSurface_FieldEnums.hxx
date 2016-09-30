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

#ifndef UTILITIES_IDD_OS_INTERIORPARTITIONSURFACE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_INTERIORPARTITIONSURFACE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_InteriorPartitionSurfaceFields
 *  \brief Enumeration of OS:InteriorPartitionSurface's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_InteriorPartitionSurfaceFields, )
#else
class OS_InteriorPartitionSurfaceFields: public ::EnumBase<OS_InteriorPartitionSurfaceFields> {
 public: 
  enum domain 
  {
Handle, Name, ConstructionName, InteriorPartitionSurfaceGroupName, ConverttoInternalMass, SurfaceArea, NumberofVertices,   };
  OS_InteriorPartitionSurfaceFields()
   : EnumBase<OS_InteriorPartitionSurfaceFields>(Handle) {} 
  OS_InteriorPartitionSurfaceFields(const std::string &t_name) 
   : EnumBase<OS_InteriorPartitionSurfaceFields>(t_name) {} 
  OS_InteriorPartitionSurfaceFields(int t_value) 
   : EnumBase<OS_InteriorPartitionSurfaceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_InteriorPartitionSurfaceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_InteriorPartitionSurfaceFields>::value()); }
   private:
    friend class EnumBase<OS_InteriorPartitionSurfaceFields>;
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
{ OS_InteriorPartitionSurfaceFields::Handle, "Handle", "Handle"},
{ OS_InteriorPartitionSurfaceFields::Name, "Name", "Name"},
{ OS_InteriorPartitionSurfaceFields::ConstructionName, "ConstructionName", "Construction Name"},
{ OS_InteriorPartitionSurfaceFields::InteriorPartitionSurfaceGroupName, "InteriorPartitionSurfaceGroupName", "Interior Partition Surface Group Name"},
{ OS_InteriorPartitionSurfaceFields::ConverttoInternalMass, "ConverttoInternalMass", "Convert to Internal Mass"},
{ OS_InteriorPartitionSurfaceFields::SurfaceArea, "SurfaceArea", "Surface Area"},
{ OS_InteriorPartitionSurfaceFields::NumberofVertices, "NumberofVertices", "Number of Vertices"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_InteriorPartitionSurfaceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_InteriorPartitionSurfaceFields> OptionalOS_InteriorPartitionSurfaceFields ;
#endif

/** \class OS_InteriorPartitionSurfaceExtensibleFields
 *  \brief Enumeration of OS:InteriorPartitionSurface's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_InteriorPartitionSurfaceExtensibleFields, )
#else
class OS_InteriorPartitionSurfaceExtensibleFields: public ::EnumBase<OS_InteriorPartitionSurfaceExtensibleFields> {
 public: 
  enum domain 
  {
VertexXcoordinate, VertexYcoordinate, VertexZcoordinate,   };
  OS_InteriorPartitionSurfaceExtensibleFields()
   : EnumBase<OS_InteriorPartitionSurfaceExtensibleFields>(VertexXcoordinate) {} 
  OS_InteriorPartitionSurfaceExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_InteriorPartitionSurfaceExtensibleFields>(t_name) {} 
  OS_InteriorPartitionSurfaceExtensibleFields(int t_value) 
   : EnumBase<OS_InteriorPartitionSurfaceExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_InteriorPartitionSurfaceExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_InteriorPartitionSurfaceExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_InteriorPartitionSurfaceExtensibleFields>;
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
{ OS_InteriorPartitionSurfaceExtensibleFields::VertexXcoordinate, "VertexXcoordinate", "Vertex X-coordinate"},
{ OS_InteriorPartitionSurfaceExtensibleFields::VertexYcoordinate, "VertexYcoordinate", "Vertex Y-coordinate"},
{ OS_InteriorPartitionSurfaceExtensibleFields::VertexZcoordinate, "VertexZcoordinate", "Vertex Z-coordinate"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_InteriorPartitionSurfaceExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_InteriorPartitionSurfaceExtensibleFields> OptionalOS_InteriorPartitionSurfaceExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_INTERIORPARTITIONSURFACE_FIELDENUMS_HXX
