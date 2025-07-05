/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_FLOOR_DETAILED_FIELDENUMS_HXX
#define UTILITIES_IDD_FLOOR_DETAILED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Floor_DetailedFields
 *  \brief Enumeration of Floor:Detailed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Floor_DetailedFields, )
#else
class Floor_DetailedFields: public ::EnumBase<Floor_DetailedFields> {
 public: 
  enum domain 
  {
Name, ConstructionName, ZoneName, SpaceName, OutsideBoundaryCondition, OutsideBoundaryConditionObject, SunExposure, WindExposure, ViewFactortoGround, NumberofVertices,   };
  Floor_DetailedFields()
   : EnumBase<Floor_DetailedFields>(Name) {} 
  Floor_DetailedFields(const std::string &t_name) 
   : EnumBase<Floor_DetailedFields>(t_name) {} 
  Floor_DetailedFields(int t_value) 
   : EnumBase<Floor_DetailedFields>(t_value) {} 
  static std::string enumName() 
  { return "Floor_DetailedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Floor_DetailedFields>::value()); }
   private:
    friend class EnumBase<Floor_DetailedFields>;
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
{ Floor_DetailedFields::Name, "Name", "Name"},
{ Floor_DetailedFields::ConstructionName, "ConstructionName", "Construction Name"},
{ Floor_DetailedFields::ZoneName, "ZoneName", "Zone Name"},
{ Floor_DetailedFields::SpaceName, "SpaceName", "Space Name"},
{ Floor_DetailedFields::OutsideBoundaryCondition, "OutsideBoundaryCondition", "Outside Boundary Condition"},
{ Floor_DetailedFields::OutsideBoundaryConditionObject, "OutsideBoundaryConditionObject", "Outside Boundary Condition Object"},
{ Floor_DetailedFields::SunExposure, "SunExposure", "Sun Exposure"},
{ Floor_DetailedFields::WindExposure, "WindExposure", "Wind Exposure"},
{ Floor_DetailedFields::ViewFactortoGround, "ViewFactortoGround", "View Factor to Ground"},
{ Floor_DetailedFields::NumberofVertices, "NumberofVertices", "Number of Vertices"},
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
  inline std::ostream &operator<<(std::ostream &os, const Floor_DetailedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Floor_DetailedFields> OptionalFloor_DetailedFields ;
#endif

/** \class Floor_DetailedExtensibleFields
 *  \brief Enumeration of Floor:Detailed's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Floor_DetailedExtensibleFields, )
#else
class Floor_DetailedExtensibleFields: public ::EnumBase<Floor_DetailedExtensibleFields> {
 public: 
  enum domain 
  {
VertexXcoordinate, VertexYcoordinate, VertexZcoordinate,   };
  Floor_DetailedExtensibleFields()
   : EnumBase<Floor_DetailedExtensibleFields>(VertexXcoordinate) {} 
  Floor_DetailedExtensibleFields(const std::string &t_name) 
   : EnumBase<Floor_DetailedExtensibleFields>(t_name) {} 
  Floor_DetailedExtensibleFields(int t_value) 
   : EnumBase<Floor_DetailedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Floor_DetailedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Floor_DetailedExtensibleFields>::value()); }
   private:
    friend class EnumBase<Floor_DetailedExtensibleFields>;
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
{ Floor_DetailedExtensibleFields::VertexXcoordinate, "VertexXcoordinate", "Vertex X-coordinate"},
{ Floor_DetailedExtensibleFields::VertexYcoordinate, "VertexYcoordinate", "Vertex Y-coordinate"},
{ Floor_DetailedExtensibleFields::VertexZcoordinate, "VertexZcoordinate", "Vertex Z-coordinate"},
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
  inline std::ostream &operator<<(std::ostream &os, const Floor_DetailedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Floor_DetailedExtensibleFields> OptionalFloor_DetailedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FLOOR_DETAILED_FIELDENUMS_HXX
