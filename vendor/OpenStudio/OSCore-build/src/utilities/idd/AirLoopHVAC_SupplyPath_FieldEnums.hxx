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

#ifndef UTILITIES_IDD_AIRLOOPHVAC_SUPPLYPATH_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_SUPPLYPATH_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_SupplyPathFields
 *  \brief Enumeration of AirLoopHVAC:SupplyPath's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_SupplyPathFields, )
#else
class AirLoopHVAC_SupplyPathFields: public ::EnumBase<AirLoopHVAC_SupplyPathFields> {
 public: 
  enum domain 
  {
Name, SupplyAirPathInletNodeName,   };
  AirLoopHVAC_SupplyPathFields()
   : EnumBase<AirLoopHVAC_SupplyPathFields>(Name) {} 
  AirLoopHVAC_SupplyPathFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_SupplyPathFields>(t_name) {} 
  AirLoopHVAC_SupplyPathFields(int t_value) 
   : EnumBase<AirLoopHVAC_SupplyPathFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_SupplyPathFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_SupplyPathFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_SupplyPathFields>;
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
{ AirLoopHVAC_SupplyPathFields::Name, "Name", "Name"},
{ AirLoopHVAC_SupplyPathFields::SupplyAirPathInletNodeName, "SupplyAirPathInletNodeName", "Supply Air Path Inlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_SupplyPathFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_SupplyPathFields> OptionalAirLoopHVAC_SupplyPathFields ;
#endif

/** \class AirLoopHVAC_SupplyPathExtensibleFields
 *  \brief Enumeration of AirLoopHVAC:SupplyPath's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AirLoopHVAC_SupplyPathExtensibleFields, )
#else
class AirLoopHVAC_SupplyPathExtensibleFields: public ::EnumBase<AirLoopHVAC_SupplyPathExtensibleFields> {
 public: 
  enum domain 
  {
ComponentObjectType, ComponentName,   };
  AirLoopHVAC_SupplyPathExtensibleFields()
   : EnumBase<AirLoopHVAC_SupplyPathExtensibleFields>(ComponentObjectType) {} 
  AirLoopHVAC_SupplyPathExtensibleFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_SupplyPathExtensibleFields>(t_name) {} 
  AirLoopHVAC_SupplyPathExtensibleFields(int t_value) 
   : EnumBase<AirLoopHVAC_SupplyPathExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_SupplyPathExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_SupplyPathExtensibleFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_SupplyPathExtensibleFields>;
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
{ AirLoopHVAC_SupplyPathExtensibleFields::ComponentObjectType, "ComponentObjectType", "Component Object Type"},
{ AirLoopHVAC_SupplyPathExtensibleFields::ComponentName, "ComponentName", "Component Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_SupplyPathExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_SupplyPathExtensibleFields> OptionalAirLoopHVAC_SupplyPathExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_SUPPLYPATH_FIELDENUMS_HXX
