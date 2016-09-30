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

#ifndef UTILITIES_IDD_OS_AIRLOOPHVAC_RETURNPLENUM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRLOOPHVAC_RETURNPLENUM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirLoopHVAC_ReturnPlenumFields
 *  \brief Enumeration of OS:AirLoopHVAC:ReturnPlenum's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirLoopHVAC_ReturnPlenumFields, )
#else
class OS_AirLoopHVAC_ReturnPlenumFields: public ::EnumBase<OS_AirLoopHVAC_ReturnPlenumFields> {
 public: 
  enum domain 
  {
Handle, Name, ThermalZone, OutletNode, InducedAirOutletPortList,   };
  OS_AirLoopHVAC_ReturnPlenumFields()
   : EnumBase<OS_AirLoopHVAC_ReturnPlenumFields>(Handle) {} 
  OS_AirLoopHVAC_ReturnPlenumFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVAC_ReturnPlenumFields>(t_name) {} 
  OS_AirLoopHVAC_ReturnPlenumFields(int t_value) 
   : EnumBase<OS_AirLoopHVAC_ReturnPlenumFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVAC_ReturnPlenumFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVAC_ReturnPlenumFields>::value()); }
   private:
    friend class EnumBase<OS_AirLoopHVAC_ReturnPlenumFields>;
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
{ OS_AirLoopHVAC_ReturnPlenumFields::Handle, "Handle", "Handle"},
{ OS_AirLoopHVAC_ReturnPlenumFields::Name, "Name", "Name"},
{ OS_AirLoopHVAC_ReturnPlenumFields::ThermalZone, "ThermalZone", "ThermalZone"},
{ OS_AirLoopHVAC_ReturnPlenumFields::OutletNode, "OutletNode", "Outlet Node"},
{ OS_AirLoopHVAC_ReturnPlenumFields::InducedAirOutletPortList, "InducedAirOutletPortList", "Induced Air Outlet Port List"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVAC_ReturnPlenumFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVAC_ReturnPlenumFields> OptionalOS_AirLoopHVAC_ReturnPlenumFields ;
#endif

/** \class OS_AirLoopHVAC_ReturnPlenumExtensibleFields
 *  \brief Enumeration of OS:AirLoopHVAC:ReturnPlenum's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_AirLoopHVAC_ReturnPlenumExtensibleFields, )
#else
class OS_AirLoopHVAC_ReturnPlenumExtensibleFields: public ::EnumBase<OS_AirLoopHVAC_ReturnPlenumExtensibleFields> {
 public: 
  enum domain 
  {
InletNode,   };
  OS_AirLoopHVAC_ReturnPlenumExtensibleFields()
   : EnumBase<OS_AirLoopHVAC_ReturnPlenumExtensibleFields>(InletNode) {} 
  OS_AirLoopHVAC_ReturnPlenumExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVAC_ReturnPlenumExtensibleFields>(t_name) {} 
  OS_AirLoopHVAC_ReturnPlenumExtensibleFields(int t_value) 
   : EnumBase<OS_AirLoopHVAC_ReturnPlenumExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVAC_ReturnPlenumExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVAC_ReturnPlenumExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_AirLoopHVAC_ReturnPlenumExtensibleFields>;
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
{ OS_AirLoopHVAC_ReturnPlenumExtensibleFields::InletNode, "InletNode", "Inlet Node"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVAC_ReturnPlenumExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVAC_ReturnPlenumExtensibleFields> OptionalOS_AirLoopHVAC_ReturnPlenumExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRLOOPHVAC_RETURNPLENUM_FIELDENUMS_HXX
