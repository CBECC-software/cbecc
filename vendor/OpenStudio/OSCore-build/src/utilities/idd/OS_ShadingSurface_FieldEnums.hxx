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

#ifndef UTILITIES_IDD_OS_SHADINGSURFACE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SHADINGSURFACE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ShadingSurfaceFields
 *  \brief Enumeration of OS:ShadingSurface's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ShadingSurfaceFields, )
#else
class OS_ShadingSurfaceFields: public ::EnumBase<OS_ShadingSurfaceFields> {
 public: 
  enum domain 
  {
Handle, Name, ConstructionName, ShadingSurfaceGroupName, TransmittanceScheduleName, NumberofVertices,   };
  OS_ShadingSurfaceFields()
   : EnumBase<OS_ShadingSurfaceFields>(Handle) {} 
  OS_ShadingSurfaceFields(const std::string &t_name) 
   : EnumBase<OS_ShadingSurfaceFields>(t_name) {} 
  OS_ShadingSurfaceFields(int t_value) 
   : EnumBase<OS_ShadingSurfaceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ShadingSurfaceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ShadingSurfaceFields>::value()); }
   private:
    friend class EnumBase<OS_ShadingSurfaceFields>;
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
{ OS_ShadingSurfaceFields::Handle, "Handle", "Handle"},
{ OS_ShadingSurfaceFields::Name, "Name", "Name"},
{ OS_ShadingSurfaceFields::ConstructionName, "ConstructionName", "Construction Name"},
{ OS_ShadingSurfaceFields::ShadingSurfaceGroupName, "ShadingSurfaceGroupName", "Shading Surface Group Name"},
{ OS_ShadingSurfaceFields::TransmittanceScheduleName, "TransmittanceScheduleName", "Transmittance Schedule Name"},
{ OS_ShadingSurfaceFields::NumberofVertices, "NumberofVertices", "Number of Vertices"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ShadingSurfaceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ShadingSurfaceFields> OptionalOS_ShadingSurfaceFields ;
#endif

/** \class OS_ShadingSurfaceExtensibleFields
 *  \brief Enumeration of OS:ShadingSurface's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_ShadingSurfaceExtensibleFields, )
#else
class OS_ShadingSurfaceExtensibleFields: public ::EnumBase<OS_ShadingSurfaceExtensibleFields> {
 public: 
  enum domain 
  {
VertexXcoordinate, VertexYcoordinate, VertexZcoordinate,   };
  OS_ShadingSurfaceExtensibleFields()
   : EnumBase<OS_ShadingSurfaceExtensibleFields>(VertexXcoordinate) {} 
  OS_ShadingSurfaceExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_ShadingSurfaceExtensibleFields>(t_name) {} 
  OS_ShadingSurfaceExtensibleFields(int t_value) 
   : EnumBase<OS_ShadingSurfaceExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ShadingSurfaceExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ShadingSurfaceExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_ShadingSurfaceExtensibleFields>;
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
{ OS_ShadingSurfaceExtensibleFields::VertexXcoordinate, "VertexXcoordinate", "Vertex X-coordinate"},
{ OS_ShadingSurfaceExtensibleFields::VertexYcoordinate, "VertexYcoordinate", "Vertex Y-coordinate"},
{ OS_ShadingSurfaceExtensibleFields::VertexZcoordinate, "VertexZcoordinate", "Vertex Z-coordinate"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ShadingSurfaceExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ShadingSurfaceExtensibleFields> OptionalOS_ShadingSurfaceExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SHADINGSURFACE_FIELDENUMS_HXX
