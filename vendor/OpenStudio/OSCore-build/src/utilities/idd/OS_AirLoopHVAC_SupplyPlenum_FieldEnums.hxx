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

#ifndef UTILITIES_IDD_OS_AIRLOOPHVAC_SUPPLYPLENUM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRLOOPHVAC_SUPPLYPLENUM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirLoopHVAC_SupplyPlenumFields
 *  \brief Enumeration of OS:AirLoopHVAC:SupplyPlenum's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirLoopHVAC_SupplyPlenumFields, )
#else
class OS_AirLoopHVAC_SupplyPlenumFields: public ::EnumBase<OS_AirLoopHVAC_SupplyPlenumFields> {
 public: 
  enum domain 
  {
Handle, Name, ThermalZone, InletNode,   };
  OS_AirLoopHVAC_SupplyPlenumFields()
   : EnumBase<OS_AirLoopHVAC_SupplyPlenumFields>(Handle) {} 
  OS_AirLoopHVAC_SupplyPlenumFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVAC_SupplyPlenumFields>(t_name) {} 
  OS_AirLoopHVAC_SupplyPlenumFields(int t_value) 
   : EnumBase<OS_AirLoopHVAC_SupplyPlenumFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVAC_SupplyPlenumFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVAC_SupplyPlenumFields>::value()); }
   private:
    friend class EnumBase<OS_AirLoopHVAC_SupplyPlenumFields>;
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
{ OS_AirLoopHVAC_SupplyPlenumFields::Handle, "Handle", "Handle"},
{ OS_AirLoopHVAC_SupplyPlenumFields::Name, "Name", "Name"},
{ OS_AirLoopHVAC_SupplyPlenumFields::ThermalZone, "ThermalZone", "Thermal Zone"},
{ OS_AirLoopHVAC_SupplyPlenumFields::InletNode, "InletNode", "Inlet Node"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVAC_SupplyPlenumFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVAC_SupplyPlenumFields> OptionalOS_AirLoopHVAC_SupplyPlenumFields ;
#endif

/** \class OS_AirLoopHVAC_SupplyPlenumExtensibleFields
 *  \brief Enumeration of OS:AirLoopHVAC:SupplyPlenum's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_AirLoopHVAC_SupplyPlenumExtensibleFields, )
#else
class OS_AirLoopHVAC_SupplyPlenumExtensibleFields: public ::EnumBase<OS_AirLoopHVAC_SupplyPlenumExtensibleFields> {
 public: 
  enum domain 
  {
OutletNode,   };
  OS_AirLoopHVAC_SupplyPlenumExtensibleFields()
   : EnumBase<OS_AirLoopHVAC_SupplyPlenumExtensibleFields>(OutletNode) {} 
  OS_AirLoopHVAC_SupplyPlenumExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVAC_SupplyPlenumExtensibleFields>(t_name) {} 
  OS_AirLoopHVAC_SupplyPlenumExtensibleFields(int t_value) 
   : EnumBase<OS_AirLoopHVAC_SupplyPlenumExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVAC_SupplyPlenumExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVAC_SupplyPlenumExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_AirLoopHVAC_SupplyPlenumExtensibleFields>;
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
{ OS_AirLoopHVAC_SupplyPlenumExtensibleFields::OutletNode, "OutletNode", "Outlet Node"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVAC_SupplyPlenumExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVAC_SupplyPlenumExtensibleFields> OptionalOS_AirLoopHVAC_SupplyPlenumExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRLOOPHVAC_SUPPLYPLENUM_FIELDENUMS_HXX
