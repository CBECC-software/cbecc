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

#ifndef UTILITIES_IDD_AIRLOOPHVAC_RETURNPATH_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_RETURNPATH_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_ReturnPathFields
 *  \brief Enumeration of AirLoopHVAC:ReturnPath's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_ReturnPathFields, )
#else
class AirLoopHVAC_ReturnPathFields: public ::EnumBase<AirLoopHVAC_ReturnPathFields> {
 public: 
  enum domain 
  {
Name, ReturnAirPathOutletNodeName,   };
  AirLoopHVAC_ReturnPathFields()
   : EnumBase<AirLoopHVAC_ReturnPathFields>(Name) {} 
  AirLoopHVAC_ReturnPathFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_ReturnPathFields>(t_name) {} 
  AirLoopHVAC_ReturnPathFields(int t_value) 
   : EnumBase<AirLoopHVAC_ReturnPathFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_ReturnPathFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_ReturnPathFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_ReturnPathFields>;
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
{ AirLoopHVAC_ReturnPathFields::Name, "Name", "Name"},
{ AirLoopHVAC_ReturnPathFields::ReturnAirPathOutletNodeName, "ReturnAirPathOutletNodeName", "Return Air Path Outlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_ReturnPathFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_ReturnPathFields> OptionalAirLoopHVAC_ReturnPathFields ;
#endif

/** \class AirLoopHVAC_ReturnPathExtensibleFields
 *  \brief Enumeration of AirLoopHVAC:ReturnPath's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AirLoopHVAC_ReturnPathExtensibleFields, )
#else
class AirLoopHVAC_ReturnPathExtensibleFields: public ::EnumBase<AirLoopHVAC_ReturnPathExtensibleFields> {
 public: 
  enum domain 
  {
ComponentObjectType, ComponentName,   };
  AirLoopHVAC_ReturnPathExtensibleFields()
   : EnumBase<AirLoopHVAC_ReturnPathExtensibleFields>(ComponentObjectType) {} 
  AirLoopHVAC_ReturnPathExtensibleFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_ReturnPathExtensibleFields>(t_name) {} 
  AirLoopHVAC_ReturnPathExtensibleFields(int t_value) 
   : EnumBase<AirLoopHVAC_ReturnPathExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_ReturnPathExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_ReturnPathExtensibleFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_ReturnPathExtensibleFields>;
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
{ AirLoopHVAC_ReturnPathExtensibleFields::ComponentObjectType, "ComponentObjectType", "Component Object Type"},
{ AirLoopHVAC_ReturnPathExtensibleFields::ComponentName, "ComponentName", "Component Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_ReturnPathExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_ReturnPathExtensibleFields> OptionalAirLoopHVAC_ReturnPathExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_RETURNPATH_FIELDENUMS_HXX
