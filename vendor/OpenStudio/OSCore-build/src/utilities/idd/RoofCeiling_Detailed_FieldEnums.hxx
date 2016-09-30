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

#ifndef UTILITIES_IDD_ROOFCEILING_DETAILED_FIELDENUMS_HXX
#define UTILITIES_IDD_ROOFCEILING_DETAILED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class RoofCeiling_DetailedFields
 *  \brief Enumeration of RoofCeiling:Detailed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(RoofCeiling_DetailedFields, )
#else
class RoofCeiling_DetailedFields: public ::EnumBase<RoofCeiling_DetailedFields> {
 public: 
  enum domain 
  {
Name, ConstructionName, ZoneName, OutsideBoundaryCondition, OutsideBoundaryConditionObject, SunExposure, WindExposure, ViewFactortoGround, NumberofVertices,   };
  RoofCeiling_DetailedFields()
   : EnumBase<RoofCeiling_DetailedFields>(Name) {} 
  RoofCeiling_DetailedFields(const std::string &t_name) 
   : EnumBase<RoofCeiling_DetailedFields>(t_name) {} 
  RoofCeiling_DetailedFields(int t_value) 
   : EnumBase<RoofCeiling_DetailedFields>(t_value) {} 
  static std::string enumName() 
  { return "RoofCeiling_DetailedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoofCeiling_DetailedFields>::value()); }
   private:
    friend class EnumBase<RoofCeiling_DetailedFields>;
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
{ RoofCeiling_DetailedFields::Name, "Name", "Name"},
{ RoofCeiling_DetailedFields::ConstructionName, "ConstructionName", "Construction Name"},
{ RoofCeiling_DetailedFields::ZoneName, "ZoneName", "Zone Name"},
{ RoofCeiling_DetailedFields::OutsideBoundaryCondition, "OutsideBoundaryCondition", "Outside Boundary Condition"},
{ RoofCeiling_DetailedFields::OutsideBoundaryConditionObject, "OutsideBoundaryConditionObject", "Outside Boundary Condition Object"},
{ RoofCeiling_DetailedFields::SunExposure, "SunExposure", "Sun Exposure"},
{ RoofCeiling_DetailedFields::WindExposure, "WindExposure", "Wind Exposure"},
{ RoofCeiling_DetailedFields::ViewFactortoGround, "ViewFactortoGround", "View Factor to Ground"},
{ RoofCeiling_DetailedFields::NumberofVertices, "NumberofVertices", "Number of Vertices"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoofCeiling_DetailedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoofCeiling_DetailedFields> OptionalRoofCeiling_DetailedFields ;
#endif

/** \class RoofCeiling_DetailedExtensibleFields
 *  \brief Enumeration of RoofCeiling:Detailed's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(RoofCeiling_DetailedExtensibleFields, )
#else
class RoofCeiling_DetailedExtensibleFields: public ::EnumBase<RoofCeiling_DetailedExtensibleFields> {
 public: 
  enum domain 
  {
VertexXcoordinate, VertexYcoordinate, VertexZcoordinate,   };
  RoofCeiling_DetailedExtensibleFields()
   : EnumBase<RoofCeiling_DetailedExtensibleFields>(VertexXcoordinate) {} 
  RoofCeiling_DetailedExtensibleFields(const std::string &t_name) 
   : EnumBase<RoofCeiling_DetailedExtensibleFields>(t_name) {} 
  RoofCeiling_DetailedExtensibleFields(int t_value) 
   : EnumBase<RoofCeiling_DetailedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "RoofCeiling_DetailedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoofCeiling_DetailedExtensibleFields>::value()); }
   private:
    friend class EnumBase<RoofCeiling_DetailedExtensibleFields>;
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
{ RoofCeiling_DetailedExtensibleFields::VertexXcoordinate, "VertexXcoordinate", "Vertex X-coordinate"},
{ RoofCeiling_DetailedExtensibleFields::VertexYcoordinate, "VertexYcoordinate", "Vertex Y-coordinate"},
{ RoofCeiling_DetailedExtensibleFields::VertexZcoordinate, "VertexZcoordinate", "Vertex Z-coordinate"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoofCeiling_DetailedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoofCeiling_DetailedExtensibleFields> OptionalRoofCeiling_DetailedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ROOFCEILING_DETAILED_FIELDENUMS_HXX
