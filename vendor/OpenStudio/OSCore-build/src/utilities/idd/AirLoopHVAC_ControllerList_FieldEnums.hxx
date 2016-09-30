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

#ifndef UTILITIES_IDD_AIRLOOPHVAC_CONTROLLERLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_CONTROLLERLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_ControllerListFields
 *  \brief Enumeration of AirLoopHVAC:ControllerList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_ControllerListFields, )
#else
class AirLoopHVAC_ControllerListFields: public ::EnumBase<AirLoopHVAC_ControllerListFields> {
 public: 
  enum domain 
  {
Name,   };
  AirLoopHVAC_ControllerListFields()
   : EnumBase<AirLoopHVAC_ControllerListFields>(Name) {} 
  AirLoopHVAC_ControllerListFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_ControllerListFields>(t_name) {} 
  AirLoopHVAC_ControllerListFields(int t_value) 
   : EnumBase<AirLoopHVAC_ControllerListFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_ControllerListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_ControllerListFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_ControllerListFields>;
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
{ AirLoopHVAC_ControllerListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_ControllerListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_ControllerListFields> OptionalAirLoopHVAC_ControllerListFields ;
#endif

/** \class AirLoopHVAC_ControllerListExtensibleFields
 *  \brief Enumeration of AirLoopHVAC:ControllerList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AirLoopHVAC_ControllerListExtensibleFields, )
#else
class AirLoopHVAC_ControllerListExtensibleFields: public ::EnumBase<AirLoopHVAC_ControllerListExtensibleFields> {
 public: 
  enum domain 
  {
ControllerObjectType, ControllerName,   };
  AirLoopHVAC_ControllerListExtensibleFields()
   : EnumBase<AirLoopHVAC_ControllerListExtensibleFields>(ControllerObjectType) {} 
  AirLoopHVAC_ControllerListExtensibleFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_ControllerListExtensibleFields>(t_name) {} 
  AirLoopHVAC_ControllerListExtensibleFields(int t_value) 
   : EnumBase<AirLoopHVAC_ControllerListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_ControllerListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_ControllerListExtensibleFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_ControllerListExtensibleFields>;
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
{ AirLoopHVAC_ControllerListExtensibleFields::ControllerObjectType, "ControllerObjectType", "Controller Object Type"},
{ AirLoopHVAC_ControllerListExtensibleFields::ControllerName, "ControllerName", "Controller Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_ControllerListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_ControllerListExtensibleFields> OptionalAirLoopHVAC_ControllerListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_CONTROLLERLIST_FIELDENUMS_HXX
