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

#ifndef UTILITIES_IDD_SHADING_SITE_DETAILED_FIELDENUMS_HXX
#define UTILITIES_IDD_SHADING_SITE_DETAILED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Shading_Site_DetailedFields
 *  \brief Enumeration of Shading:Site:Detailed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Shading_Site_DetailedFields, )
#else
class Shading_Site_DetailedFields: public ::EnumBase<Shading_Site_DetailedFields> {
 public: 
  enum domain 
  {
Name, TransmittanceScheduleName, NumberofVertices,   };
  Shading_Site_DetailedFields()
   : EnumBase<Shading_Site_DetailedFields>(Name) {} 
  Shading_Site_DetailedFields(const std::string &t_name) 
   : EnumBase<Shading_Site_DetailedFields>(t_name) {} 
  Shading_Site_DetailedFields(int t_value) 
   : EnumBase<Shading_Site_DetailedFields>(t_value) {} 
  static std::string enumName() 
  { return "Shading_Site_DetailedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Shading_Site_DetailedFields>::value()); }
   private:
    friend class EnumBase<Shading_Site_DetailedFields>;
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
{ Shading_Site_DetailedFields::Name, "Name", "Name"},
{ Shading_Site_DetailedFields::TransmittanceScheduleName, "TransmittanceScheduleName", "Transmittance Schedule Name"},
{ Shading_Site_DetailedFields::NumberofVertices, "NumberofVertices", "Number of Vertices"},
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
  inline std::ostream &operator<<(std::ostream &os, const Shading_Site_DetailedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Shading_Site_DetailedFields> OptionalShading_Site_DetailedFields ;
#endif

/** \class Shading_Site_DetailedExtensibleFields
 *  \brief Enumeration of Shading:Site:Detailed's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Shading_Site_DetailedExtensibleFields, )
#else
class Shading_Site_DetailedExtensibleFields: public ::EnumBase<Shading_Site_DetailedExtensibleFields> {
 public: 
  enum domain 
  {
VertexXcoordinate, VertexYcoordinate, VertexZcoordinate,   };
  Shading_Site_DetailedExtensibleFields()
   : EnumBase<Shading_Site_DetailedExtensibleFields>(VertexXcoordinate) {} 
  Shading_Site_DetailedExtensibleFields(const std::string &t_name) 
   : EnumBase<Shading_Site_DetailedExtensibleFields>(t_name) {} 
  Shading_Site_DetailedExtensibleFields(int t_value) 
   : EnumBase<Shading_Site_DetailedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Shading_Site_DetailedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Shading_Site_DetailedExtensibleFields>::value()); }
   private:
    friend class EnumBase<Shading_Site_DetailedExtensibleFields>;
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
{ Shading_Site_DetailedExtensibleFields::VertexXcoordinate, "VertexXcoordinate", "Vertex X-coordinate"},
{ Shading_Site_DetailedExtensibleFields::VertexYcoordinate, "VertexYcoordinate", "Vertex Y-coordinate"},
{ Shading_Site_DetailedExtensibleFields::VertexZcoordinate, "VertexZcoordinate", "Vertex Z-coordinate"},
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
  inline std::ostream &operator<<(std::ostream &os, const Shading_Site_DetailedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Shading_Site_DetailedExtensibleFields> OptionalShading_Site_DetailedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SHADING_SITE_DETAILED_FIELDENUMS_HXX
