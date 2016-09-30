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

#ifndef UTILITIES_IDD_ROOMAIR_NODE_FIELDENUMS_HXX
#define UTILITIES_IDD_ROOMAIR_NODE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class RoomAir_NodeFields
 *  \brief Enumeration of RoomAir:Node's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(RoomAir_NodeFields, )
#else
class RoomAir_NodeFields: public ::EnumBase<RoomAir_NodeFields> {
 public: 
  enum domain 
  {
Name, NodeType, ZoneName, HeightofNodalControlVolumeCenter,   };
  RoomAir_NodeFields()
   : EnumBase<RoomAir_NodeFields>(Name) {} 
  RoomAir_NodeFields(const std::string &t_name) 
   : EnumBase<RoomAir_NodeFields>(t_name) {} 
  RoomAir_NodeFields(int t_value) 
   : EnumBase<RoomAir_NodeFields>(t_value) {} 
  static std::string enumName() 
  { return "RoomAir_NodeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoomAir_NodeFields>::value()); }
   private:
    friend class EnumBase<RoomAir_NodeFields>;
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
{ RoomAir_NodeFields::Name, "Name", "Name"},
{ RoomAir_NodeFields::NodeType, "NodeType", "Node Type"},
{ RoomAir_NodeFields::ZoneName, "ZoneName", "Zone Name"},
{ RoomAir_NodeFields::HeightofNodalControlVolumeCenter, "HeightofNodalControlVolumeCenter", "Height of Nodal Control Volume Center"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoomAir_NodeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoomAir_NodeFields> OptionalRoomAir_NodeFields ;
#endif

/** \class RoomAir_NodeExtensibleFields
 *  \brief Enumeration of RoomAir:Node's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(RoomAir_NodeExtensibleFields, )
#else
class RoomAir_NodeExtensibleFields: public ::EnumBase<RoomAir_NodeExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceName,   };
  RoomAir_NodeExtensibleFields()
   : EnumBase<RoomAir_NodeExtensibleFields>(SurfaceName) {} 
  RoomAir_NodeExtensibleFields(const std::string &t_name) 
   : EnumBase<RoomAir_NodeExtensibleFields>(t_name) {} 
  RoomAir_NodeExtensibleFields(int t_value) 
   : EnumBase<RoomAir_NodeExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "RoomAir_NodeExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoomAir_NodeExtensibleFields>::value()); }
   private:
    friend class EnumBase<RoomAir_NodeExtensibleFields>;
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
{ RoomAir_NodeExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoomAir_NodeExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoomAir_NodeExtensibleFields> OptionalRoomAir_NodeExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ROOMAIR_NODE_FIELDENUMS_HXX
