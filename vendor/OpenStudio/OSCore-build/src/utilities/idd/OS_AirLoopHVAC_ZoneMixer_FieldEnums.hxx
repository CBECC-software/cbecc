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

#ifndef UTILITIES_IDD_OS_AIRLOOPHVAC_ZONEMIXER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRLOOPHVAC_ZONEMIXER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirLoopHVAC_ZoneMixerFields
 *  \brief Enumeration of OS:AirLoopHVAC:ZoneMixer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirLoopHVAC_ZoneMixerFields, )
#else
class OS_AirLoopHVAC_ZoneMixerFields: public ::EnumBase<OS_AirLoopHVAC_ZoneMixerFields> {
 public: 
  enum domain 
  {
Handle, Name, OutletNodeName,   };
  OS_AirLoopHVAC_ZoneMixerFields()
   : EnumBase<OS_AirLoopHVAC_ZoneMixerFields>(Handle) {} 
  OS_AirLoopHVAC_ZoneMixerFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVAC_ZoneMixerFields>(t_name) {} 
  OS_AirLoopHVAC_ZoneMixerFields(int t_value) 
   : EnumBase<OS_AirLoopHVAC_ZoneMixerFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVAC_ZoneMixerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVAC_ZoneMixerFields>::value()); }
   private:
    friend class EnumBase<OS_AirLoopHVAC_ZoneMixerFields>;
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
{ OS_AirLoopHVAC_ZoneMixerFields::Handle, "Handle", "Handle"},
{ OS_AirLoopHVAC_ZoneMixerFields::Name, "Name", "Name"},
{ OS_AirLoopHVAC_ZoneMixerFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVAC_ZoneMixerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVAC_ZoneMixerFields> OptionalOS_AirLoopHVAC_ZoneMixerFields ;
#endif

/** \class OS_AirLoopHVAC_ZoneMixerExtensibleFields
 *  \brief Enumeration of OS:AirLoopHVAC:ZoneMixer's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_AirLoopHVAC_ZoneMixerExtensibleFields, )
#else
class OS_AirLoopHVAC_ZoneMixerExtensibleFields: public ::EnumBase<OS_AirLoopHVAC_ZoneMixerExtensibleFields> {
 public: 
  enum domain 
  {
InletNodeName,   };
  OS_AirLoopHVAC_ZoneMixerExtensibleFields()
   : EnumBase<OS_AirLoopHVAC_ZoneMixerExtensibleFields>(InletNodeName) {} 
  OS_AirLoopHVAC_ZoneMixerExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVAC_ZoneMixerExtensibleFields>(t_name) {} 
  OS_AirLoopHVAC_ZoneMixerExtensibleFields(int t_value) 
   : EnumBase<OS_AirLoopHVAC_ZoneMixerExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVAC_ZoneMixerExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVAC_ZoneMixerExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_AirLoopHVAC_ZoneMixerExtensibleFields>;
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
{ OS_AirLoopHVAC_ZoneMixerExtensibleFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVAC_ZoneMixerExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVAC_ZoneMixerExtensibleFields> OptionalOS_AirLoopHVAC_ZoneMixerExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRLOOPHVAC_ZONEMIXER_FIELDENUMS_HXX
